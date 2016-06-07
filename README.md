# contiki_01_ds18b20
contiki 温度探头ds18b20
硬件平台
---------
1.芯片使用cc2538

2.开发板淘宝，资料百度云

运行
--------------------
wget https://github.com/contiki-os/contiki/archive/3.0.tar.gz

mv 3.0.tar.gz contiki_3.0.tar.gz

tar -zxvf contiki_3.0.tar.gz

cd contiki-3.0

mkdir myproject（注意这个文件夹名字可以改，但必须放到contiki的根目录下，我们的工程脚本以这个为基础）

cd myproject

git clone https://github.com/wumingyu12/contiki_01_ds18b20

cd contiki_01_ds18b20

chmod -x *.sh (给所有脚本添加权限)

使用
--------------
./add.sh 添加必要的库到contiki中

make all TARGET=cc2538dk

下载到开发板
-----------------------
1.开发板中同时按下select和reset键，不同与正常reset三色灯不会闪

2.用usb转ttl连接

3.sudo chmod 777 /dev/ttyUSB0

4. ./download.sh (下载到开发板)

5. 使用putty察看串口输出，如果要保存配置文件注意要用sudo

恢复原样
------------
./clean.sh

make clean
