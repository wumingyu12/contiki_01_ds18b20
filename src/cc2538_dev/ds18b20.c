#include "contiki.h"
#include "dev/leds.h"
#include "dev/gpio.h"
#include "dev/ds18b20.h"


#define DEBUG 0


#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else /* DEBUG */
/* We overwrite (read as annihilate) all output functions here */
#define PRINTF(...)
#endif /* DEBUG */

/*

#define SET_IN		P1DIR &= ~0x04;clock_delay_usec(1)	
#define SET_OUT		P1DIR |= 0x04;clock_delay_usec(1)
#define CL_DQ		P1 &= ~0x04;clock_delay_usec(1)	
#define SET_DQ		P1 |=  0x04;clock_delay_usec(1)
#define DATA_IN()	(P1 & 0x04)

#define SET_P13_OUT	P1DIR |= 0x08
#define SET_P13_H	P1 |=0x08
#define SET_P13_L	P1 &=~0x08

*/

/* Port 1, Pin 2 */
/*
#define DS_PORT		GPIO_B_NUM

#define SET_IN		GPIO_SET_INPUT(GPIO_PORT_TO_BASE(DS_PORT), GPIO_PIN_MASK(4));clock_delay_usec(1)
#define SET_OUT		GPIO_SET_OUTPUT(GPIO_PORT_TO_BASE(DS_PORT), GPIO_PIN_MASK(4));clock_delay_usec(1)
#define CL_DQ		GPIO_CLR_PIN(GPIO_PORT_TO_BASE(DS_PORT),GPIO_PIN_MASK(4));clock_delay_usec(1)
#define SET_DQ		GPIO_SET_PIN(GPIO_PORT_TO_BASE(DS_PORT),GPIO_PIN_MASK(4));clock_delay_usec(1)
#define DATA_IN()	(GPIO_READ_PIN(GPIO_PORT_TO_BASE(DS_PORT),GPIO_PIN_MASK(4)))

#define SET_P13_OUT	GPIO_SET_OUTPUT(GPIO_PORT_TO_BASE(DS_PORT), GPIO_PIN_MASK(8))
#define SET_P13_H	GPIO_SET_PIN(GPIO_PORT_TO_BASE(DS_PORT), GPIO_PIN_MASK(8))
#define SET_P13_L	GPIO_CLR_PIN(GPIO_PORT_TO_BASE(DS_PORT), GPIO_PIN_MASK(8))
*/
static uint8_t temh, teml;
static uint8_t flag;
static uint8_t ds18b20_cunzai;
static uint8_t id[8];




/*---------------------------------------------------------------------------*/


void	Delay_nus(unsigned int s)
{
	clock_delay_usec(s);
}

uint8_t Read_1bit()
{
	uint8_t k;
	k = DATA_IN();
	return k;
}	

void init_1820(void) 
{
  SET_OUT;
  SET_DQ;
  Delay_nus(7);
  CL_DQ; 
  Delay_nus(530);
  
  SET_DQ;
  SET_IN;
  Delay_nus(44);
  if( Read_1bit() == 0)
    ds18b20_cunzai = 1;
      else
        ds18b20_cunzai = 0;
  Delay_nus(150);
  SET_OUT; 
  SET_DQ;
}

void write_1820(uint8_t x)  
{  
  uint8_t m;    
  SET_OUT;
  for(m=0;m<8;m++)  
  {  
     CL_DQ;
     Delay_nus(1);
     if(x&(1<<m)){    
     SET_DQ; }
     else{  
     CL_DQ; } 
     Delay_nus(40); 
     SET_DQ;  
  }
  SET_DQ;  
} 


uint8_t read_1820(void)  
{   
  uint8_t temp,k,n;    
  temp=0;  
  for(n=0;n<8;n++)  
  {  
    CL_DQ; 
    Delay_nus(1); 
    SET_DQ;       
    SET_IN;  
    k=Read_1bit(); 
    if(k)  
    temp|=(1<<n);  
    else  
    temp&=~(1<<n);  
    Delay_nus(70);
    SET_OUT;
  
  }  
  return (temp);  
}  
void get_id()
{     
  unsigned char ii=0;
  init_1820();        //resert
  write_1820(0x33); 
  
  for(ii=0;ii<8;ii++)
  {
    id[ii]=read_1820();
  }
}


 
void read_data( void )
{
  uint8_t a,b,c;

  PRINTF("read data function start:\n");
  init_1820();  //复位18b20  
  write_1820(0xcc);   // 发出转换命令 搜索器件 
  write_1820(0x44);     //启动  
  Delay_nus(2000);
  init_1820();  
  write_1820(0xcc);
  write_1820(0xbe); 
       
  teml=read_1820();  //读数据  
  temh=read_1820();  

 PRINTF("teml: %d\n",teml);
 PRINTF("temh: %d\n",temh);

  if(temh&0x80)//判断正负
  {
    flag=1;
    c=0;
    c=c|temh;
    c=c&0x00ff;
    c=c<<8;
    a=c;

    a=c|teml;

    a=(a^0xffff);//异或
    a=a+1;  //取反加1
    teml=a&0x0f;
    temh=a>>4;
  }
  else
  {
    flag=0;   //为正
    a=temh<<4;
    a+=(teml&0xf0)>>4; //得到高位的值
    b=teml&0x0f;
    temh=a;
    teml=b&0x00ff;
  }
}

/******************************************************************************
 * @fn          myApp_ReadTemperature
 *
 * @brief       Reports temperature sensor reading
 *
 * @param
 *
 * @return
 ******************************************************************************/
void ds18b20_read( uint8_t * pChBuf )
{
   
  uint16_t num, tmp;
 
  read_data(); 
  num=teml*625; 
  PRINTF("raw temp value:%d \n",num);
  if(flag==1)  
  {
   	pChBuf[0]='-';
  }
  else pChBuf[0]='+';   
  if(temh/100==0){
     	pChBuf[1]=' ';
	}
  else {
   	pChBuf[1]=temh/100+0x30; 
	}
  if((temh/10%10==0)&&(temh/100==0))
   	pChBuf[2]=' ';
  else  pChBuf[2]=temh/10%10+0x30;

    pChBuf[3]=temh%10+0x30;
    pChBuf[4]='.';
    pChBuf[5]=num/1000+0x30;
    pChBuf[6]='C';
    pChBuf[7]='\0';
    tmp=(temh/10)*10 + temh%10;

  if(tmp>20){
	leds_on(LEDS_RED);
  }else{
	leds_off(LEDS_RED);
  }

  PRINTF("my tmp: %d \n",tmp);


  
}

