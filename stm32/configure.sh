#!/bin/sh

# http://www.codesourcery.com/sgpp/lite/arm/portal/release1802
TOOLCHAIN_DIR=/opt/arm-2011.03

# http://www.st.com/internet/com/SOFTWARE_RESOURCES/SW_COMPONENT/FIRMWARE/stm32f10x_stdperiph_lib.zip
STM32_LIB_DIR=/opt/STM32F10x_StdPeriph_Lib_V3.5.0

P=""
param_add() {
    P="$P -D${1}=${2}"
}

param_add CMAKE_TOOLCHAIN_FILE      ../cmake-support/gcc_stm32.cmake
param_add CMAKE_BUILD_TYPE          Debug
#param_add STM32_StdPeriphLib_DIR    $STM32_LIB_DIR
param_add TOOLCHAIN_PREFIX          $TOOLCHAIN_DIR
# http://easyelectronics.ru/arm-uchebnyj-kurs-iar-ewarm-sozdanie-proekta-chast-2-cmsis-i-standard-peripherals-library.html
param_add STM32_CHIP_TYPE           LD_VL
param_add CMAKE_MODULE_PATH         `pwd`/cmake-support

echo $P
rm -fr ./target
mkdir -p ./target
cd ./target
cmake $P ..
