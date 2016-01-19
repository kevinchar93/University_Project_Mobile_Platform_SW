























.build_ano/mega/RemoteComm/RemoteComm.o : lib/RemoteComm/RemoteComm.cpp
	@echo [93mRemoteComm/RemoteComm.cpp[0m
	@mkdir -p .build_ano/mega/RemoteComm
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c lib/RemoteComm/RemoteComm.cpp
include .build_ano/mega/RemoteComm/RemoteComm.d



.build_ano/mega/RemoteComm/libRemoteComm.a : .build_ano/mega/RemoteComm/RemoteComm.o
	@echo [92mLinking libRemoteComm.a[0m
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-ar rcs $@ $^












.build_ano/mega/Lidar360/Lidar360.o : lib/Lidar360/Lidar360.cpp
	@echo [93mLidar360/Lidar360.cpp[0m
	@mkdir -p .build_ano/mega/Lidar360
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c lib/Lidar360/Lidar360.cpp
include .build_ano/mega/Lidar360/Lidar360.d



.build_ano/mega/Lidar360/libLidar360.a : .build_ano/mega/Lidar360/Lidar360.o
	@echo [92mLinking libLidar360.a[0m
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-ar rcs $@ $^












.build_ano/mega/AccelStepper/AccelStepper.o : lib/AccelStepper/AccelStepper.cpp
	@echo [93mAccelStepper/AccelStepper.cpp[0m
	@mkdir -p .build_ano/mega/AccelStepper
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c lib/AccelStepper/AccelStepper.cpp
include .build_ano/mega/AccelStepper/AccelStepper.d

.build_ano/mega/AccelStepper/MultiStepper.o : lib/AccelStepper/MultiStepper.cpp
	@echo [93mAccelStepper/MultiStepper.cpp[0m
	@mkdir -p .build_ano/mega/AccelStepper
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c lib/AccelStepper/MultiStepper.cpp
include .build_ano/mega/AccelStepper/MultiStepper.d



.build_ano/mega/AccelStepper/libAccelStepper.a : .build_ano/mega/AccelStepper/AccelStepper.o .build_ano/mega/AccelStepper/MultiStepper.o
	@echo [92mLinking libAccelStepper.a[0m
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-ar rcs $@ $^












.build_ano/mega/I2C/I2C.o : lib/I2C/I2C.cpp
	@echo [93mI2C/I2C.cpp[0m
	@mkdir -p .build_ano/mega/I2C
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c lib/I2C/I2C.cpp
include .build_ano/mega/I2C/I2C.d



.build_ano/mega/I2C/libI2C.a : .build_ano/mega/I2C/I2C.o
	@echo [92mLinking libI2C.a[0m
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-ar rcs $@ $^














.build_ano/mega/Common/libCommon.a : 
	@echo [92mLinking libCommon.a[0m
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-ar rcs $@ $^







.build_ano/mega/arduino/hooks.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/hooks.c
	@echo [93marduino/hooks.c[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-gcc -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino   -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/hooks.c
include .build_ano/mega/arduino/hooks.d

.build_ano/mega/arduino/WInterrupts.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/WInterrupts.c
	@echo [93marduino/WInterrupts.c[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-gcc -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino   -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/WInterrupts.c
include .build_ano/mega/arduino/WInterrupts.d

.build_ano/mega/arduino/wiring.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/wiring.c
	@echo [93marduino/wiring.c[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-gcc -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino   -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/wiring.c
include .build_ano/mega/arduino/wiring.d

.build_ano/mega/arduino/wiring_analog.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/wiring_analog.c
	@echo [93marduino/wiring_analog.c[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-gcc -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino   -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/wiring_analog.c
include .build_ano/mega/arduino/wiring_analog.d

.build_ano/mega/arduino/wiring_digital.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/wiring_digital.c
	@echo [93marduino/wiring_digital.c[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-gcc -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino   -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/wiring_digital.c
include .build_ano/mega/arduino/wiring_digital.d

.build_ano/mega/arduino/wiring_pulse.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/wiring_pulse.c
	@echo [93marduino/wiring_pulse.c[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-gcc -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino   -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/wiring_pulse.c
include .build_ano/mega/arduino/wiring_pulse.d

.build_ano/mega/arduino/wiring_shift.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/wiring_shift.c
	@echo [93marduino/wiring_shift.c[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-gcc -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino   -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/wiring_shift.c
include .build_ano/mega/arduino/wiring_shift.d






.build_ano/mega/arduino/abi.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/abi.cpp
	@echo [93marduino/abi.cpp[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/abi.cpp
include .build_ano/mega/arduino/abi.d

.build_ano/mega/arduino/CDC.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/CDC.cpp
	@echo [93marduino/CDC.cpp[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/CDC.cpp
include .build_ano/mega/arduino/CDC.d

.build_ano/mega/arduino/HardwareSerial.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/HardwareSerial.cpp
	@echo [93marduino/HardwareSerial.cpp[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/HardwareSerial.cpp
include .build_ano/mega/arduino/HardwareSerial.d

.build_ano/mega/arduino/HardwareSerial0.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/HardwareSerial0.cpp
	@echo [93marduino/HardwareSerial0.cpp[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/HardwareSerial0.cpp
include .build_ano/mega/arduino/HardwareSerial0.d

.build_ano/mega/arduino/HardwareSerial1.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/HardwareSerial1.cpp
	@echo [93marduino/HardwareSerial1.cpp[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/HardwareSerial1.cpp
include .build_ano/mega/arduino/HardwareSerial1.d

.build_ano/mega/arduino/HardwareSerial2.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/HardwareSerial2.cpp
	@echo [93marduino/HardwareSerial2.cpp[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/HardwareSerial2.cpp
include .build_ano/mega/arduino/HardwareSerial2.d

.build_ano/mega/arduino/HardwareSerial3.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/HardwareSerial3.cpp
	@echo [93marduino/HardwareSerial3.cpp[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/HardwareSerial3.cpp
include .build_ano/mega/arduino/HardwareSerial3.d

.build_ano/mega/arduino/IPAddress.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/IPAddress.cpp
	@echo [93marduino/IPAddress.cpp[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/IPAddress.cpp
include .build_ano/mega/arduino/IPAddress.d

.build_ano/mega/arduino/main.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/main.cpp
	@echo [93marduino/main.cpp[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/main.cpp
include .build_ano/mega/arduino/main.d

.build_ano/mega/arduino/new.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/new.cpp
	@echo [93marduino/new.cpp[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/new.cpp
include .build_ano/mega/arduino/new.d

.build_ano/mega/arduino/PluggableUSB.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/PluggableUSB.cpp
	@echo [93marduino/PluggableUSB.cpp[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/PluggableUSB.cpp
include .build_ano/mega/arduino/PluggableUSB.d

.build_ano/mega/arduino/Print.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/Print.cpp
	@echo [93marduino/Print.cpp[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/Print.cpp
include .build_ano/mega/arduino/Print.d

.build_ano/mega/arduino/Stream.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/Stream.cpp
	@echo [93marduino/Stream.cpp[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/Stream.cpp
include .build_ano/mega/arduino/Stream.d

.build_ano/mega/arduino/Tone.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/Tone.cpp
	@echo [93marduino/Tone.cpp[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/Tone.cpp
include .build_ano/mega/arduino/Tone.d

.build_ano/mega/arduino/USBCore.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/USBCore.cpp
	@echo [93marduino/USBCore.cpp[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/USBCore.cpp
include .build_ano/mega/arduino/USBCore.d

.build_ano/mega/arduino/WMath.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/WMath.cpp
	@echo [93marduino/WMath.cpp[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/WMath.cpp
include .build_ano/mega/arduino/WMath.d

.build_ano/mega/arduino/WString.o : /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/WString.cpp
	@echo [93marduino/WString.cpp[0m
	@mkdir -p .build_ano/mega/arduino
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions  -o $@ -c /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/WString.cpp
include .build_ano/mega/arduino/WString.d



.build_ano/mega/arduino/libarduino.a : .build_ano/mega/arduino/hooks.o .build_ano/mega/arduino/WInterrupts.o .build_ano/mega/arduino/wiring.o .build_ano/mega/arduino/wiring_analog.o .build_ano/mega/arduino/wiring_digital.o .build_ano/mega/arduino/wiring_pulse.o .build_ano/mega/arduino/wiring_shift.o .build_ano/mega/arduino/abi.o .build_ano/mega/arduino/CDC.o .build_ano/mega/arduino/HardwareSerial.o .build_ano/mega/arduino/HardwareSerial0.o .build_ano/mega/arduino/HardwareSerial1.o .build_ano/mega/arduino/HardwareSerial2.o .build_ano/mega/arduino/HardwareSerial3.o .build_ano/mega/arduino/IPAddress.o .build_ano/mega/arduino/main.o .build_ano/mega/arduino/new.o .build_ano/mega/arduino/PluggableUSB.o .build_ano/mega/arduino/Print.o .build_ano/mega/arduino/Stream.o .build_ano/mega/arduino/Tone.o .build_ano/mega/arduino/USBCore.o .build_ano/mega/arduino/WMath.o .build_ano/mega/arduino/WString.o
	@echo [92mLinking libarduino.a[0m
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-ar rcs $@ $^















.build_ano/mega/src/main_mob_platform.o : .build_ano/mega/src/main_mob_platform.cpp
	@echo [93msrc/main_mob_platform.cpp[0m
	@mkdir -p .build_ano/mega/src
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=167 -DARDUINO_ARCH_AVR -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/mega -Ilib/RemoteComm -Ilib/Lidar360 -Ilib/AccelStepper -Ilib/AccelStepper/doc -Ilib/I2C -Ilib/Common -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -fno-exceptions -iquote src  -o $@ -c .build_ano/mega/src/main_mob_platform.cpp
include .build_ano/mega/src/main_mob_platform.d







.build_ano/mega/firmware.elf : .build_ano/mega/src/main_mob_platform.o .build_ano/mega/RemoteComm/libRemoteComm.a .build_ano/mega/Lidar360/libLidar360.a .build_ano/mega/AccelStepper/libAccelStepper.a .build_ano/mega/I2C/libI2C.a .build_ano/mega/Common/libCommon.a .build_ano/mega/arduino/libarduino.a
	@echo [92mLinking firmware.elf[0m
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-gcc -mmcu=atmega2560 -Wl,-Os -Wl,--gc-sections -o $@ $^ -lm


.build_ano/mega/firmware.hex : .build_ano/mega/firmware.elf
	@echo [92mConverting to firmware.hex[0m
	@/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom $^ $@

include .build_ano/mega/src/dependencies.d .build_ano/mega/RemoteComm/dependencies.d .build_ano/mega/Lidar360/dependencies.d .build_ano/mega/AccelStepper/dependencies.d .build_ano/mega/arduino/dependencies.d .build_ano/mega/Common/dependencies.d .build_ano/mega/I2C/dependencies.d

all : .build_ano/mega/firmware.hex
	@true

