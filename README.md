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
