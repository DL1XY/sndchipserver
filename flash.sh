#!/bin/bash

#if [[ "$EUID" -ne 0 ]];
#  then echo "Usage: sudo flash.sh"
#  exit
#fi

TTY_DEVICE=/dev/ttyUSB0


function restart
{
	echo "Restart ${TTY_DEVICE} ..."
	sudo rmmod ch341 
	for i in {10..0}; do echo -ne "Remove ch341 in $i"'\r'; sleep 1; done; echo 
	sudo rmmod usbserial
	for i in {10..0}; do echo -ne "Remove usbserial in $i"'\r'; sleep 1; done; echo 
	sudo modprobe ch341
	for i in {30..0}; do echo -ne "Restart ch341 in $i"'\r'; sleep 1; done; echo 


}

function restartEsp
{
 exit	
}

echo "Erase Flash on ${TTY_DEVICE} ..."
#esptool.py --trace --port /dev/ttyUSB0 --before default_reset --after no_reset erase_flash
esptool.py erase_flash

restart

echo "Write default firmware on ${TTY_DEVICE} ..."
#esptool.py --trace --port /dev/ttyUSB0 --before default_reset --after no_reset write_flash 0x3FC000 ~/Projekte/libs/esp-open-sdk/ESP8266_NONOS_SDK-2.1.0-18-g61248df/bin/esp_init_data_default.bin
esptool.py --trace --port /dev/ttyUSB0 write_flash --flash_mode qio 0xfc000 ~/Projekte/libs/esp-open-sdk/ESP8266_NONOS_SDK-2.1.0-18-g61248df/bin/esp_init_data_default.bin
restart

echo "Write program to ${TTY_DEVICE} ..."
# esptool.py --trace --port /dev/ttyUSB0 --before default_reset --after hard_reset --flash_size 8m write_flash 0x00000 firmware/0x00000.bin 0x10000 firmware/0x10000.bin
esptool.py --trace --port /dev/ttyUSB0 write_flash --flash_mode qio 0x00000 firmware/0x00000.bin 0x10000 firmware/0x10000.bin
restart

echo "ESP8266 is ready !"
exit
