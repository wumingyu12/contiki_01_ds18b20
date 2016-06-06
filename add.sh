#!/bin/sh
cp ./src/cc2538_dev/ds18b20.c ../../platform/cc2538dk/dev/ds18b20.c
cp ./src/cc2538_dev/ds18b20.h ../../platform/cc2538dk/dev/ds18b20.h
echo "成功复制ds18b20驱动到cc2538/dev"

if 
	#如果已经存在这一句了就不用加，否则就加上
	grep -n "CONTIKI_TARGET_SOURCEFILES += ds18b20.c" ../../platform/cc2538dk/Makefile.cc2538dk
then
	echo "已经存在CONTIKI_TARGET_SOURCEFILES += ds18b20.c在Makefile.cc2538dk"
else
	#行前加一行
	sed -i '/CONTIKI_SOURCEFILES += $(CONTIKI_TARGET_SOURCEFILES)/i\CONTIKI_TARGET_SOURCEFILES += ds18b20.c' \
	../../platform/cc2538dk/Makefile.cc2538dk
	echo "添加CONTIKI_TARGET_SOURCEFILES += ds18b20.c到Makefile.cc2538dk"
fi

