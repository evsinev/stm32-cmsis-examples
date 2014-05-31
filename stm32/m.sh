#!/bin/bash

set -eux

cd target && make stm32-servo-arm.bin

st-flash write  stm32-servo-arm.bin 0x08000000

exit 0

#../util/stlink-download reset
#../util/stlink-download status
#../util/stlink-download erase=all
#../util/stlink-download debug program=stm32-dimmer-control.bin 
#../util/stlink-download reset
#../util/stlink-download run
#../util/stlink-download status

