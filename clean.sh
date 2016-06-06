#!/bin/sh
rm ../../platform/cc2538dk/dev/ds18b20.c
rm ../../platform/cc2538dk/dev/ds18b20.h
echo "成功删除ds18b20的驱动在cc2538/dev"

if 
	#如果已经存在这一句了就不用加，否则就加上
	grep -n "CONTIKI_TARGET_SOURCEFILES += ds18b20.c" ../../platform/cc2538dk/Makefile.cc2538dk
then
	sed -i '/CONTIKI_TARGET_SOURCEFILES += ds18b20.c/d' ../../platform/cc2538dk/Makefile.cc2538dk
	echo "已经删除CONTIKI_TARGET_SOURCEFILES += ds18b20.c在Makefile.cc2538dk"
else
	#行前加一行
	echo "没有CONTIKI_TARGET_SOURCEFILES += ds18b20.c行在Makefile.cc2538dk中"
fi
