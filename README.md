# contiki_01_ds18b20
contiki 温度探头ds18b20

运行
--------------------
* 1.下载3.0的contiki，并重命名
wget https://github.com/contiki-os/contiki/archive/3.0.tar.gz
mv 3.0.tar.gz contiki_3.0.tar.gz
* 2.解压contiki
tar -zxvf contiki_3.0.tar.gz
* 3.进入
cd contiki-3。0
* 4.新建我们用来放工程的文件夹myproject（注意这个文件夹名字可以改，但必须放到contiki的根目录下，我们的工程脚本以这个为基础）
mkdir myproject
cd myproject
* 5.下载我们的工程
git clone https://github.com/wumingyu12/contiki_01_ds18b20
