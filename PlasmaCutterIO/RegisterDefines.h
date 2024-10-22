#pragma once
#define SLAVE_ID 0x01 //Address of MODBus Slave
#define FREQ 16000000 //Don't Touch unless using a differnt board, Freq of Processor
#define KILL_TIME 2000       //2 Sec (2000msec) keep alive, 0 => OFF

//############  this->coilRegister DEFINES ############# // Each this->coilRegister is 16bit

#define NUMBER_OF_REGISTERS 36

#define ANALOG_IN_0_RAW_REGISTER 0
#define ANALOG_IN_0_SCALED_REGISTER 1
#define ANALOG_IN_0_RAW_LOW_REGISTER 2
#define ANALOG_IN_0_HIGH_REGISTER 3
#define ANALOG_IN_0_SCALE_LOW_REGISTER 4
#define ANALOG_IN_0_SCALE_HIGH_REGISTER 5
#define ANALOG_IN_0_FACTOR_REGISTER 6
#define ANALOG_IN_1_RAW_REGISTER 7
#define ANALOG_IN_1_SCALED_REGISTER 8
#define ANALOG_IN_1_RAW_LOW_REGISTER 9
#define ANALOG_IN_1_HIGH_REGISTER 10
#define ANALOG_IN_1_SCALE_LOW_REGISTER 11
#define ANALOG_IN_1_SCALE_HIGH_REGISTER 12
#define ANALOG_IN_1_FACTOR_REGISTER 13
#define PILOT_ARC_VOLTAGE_REGISTER 14
#define MAIN_ARC_VOLTAGE_REGISTER 15
#define AC_OK_RAW_REGISTER 16
#define OVER_TEMP_RAW_REGISTER 17
#define GAS_OK_RAW_REGISTER 18
#define DC_OK_RAW_REGISTER 19
#define TORCH_FIRE_COMMAND_REGISTER 20
#define TORCH_FIRE_FIRING_REGISTER 21
#define SYSTEM_ALARM_REGISTER 22
#define ARC_FAILED_ALARM_REGISTER 23
#define ARC_STARTED_REGISTER 24
#define ARC_STARTING_REGISTER 25
#define ARC_START_INTERLOCK_REGISTER 26
#define ARC_START_TIME_REGISTER 27
#define ARC_START_INTERLOCK_START_TIME_REGISTER 28
#define ARC_RETRIES_REGISTER 29
#define ARC_START_TIMEOUT_REGISTER 30
#define ARC_INTERLOCK_TIMEOUT_REGISTER 31
#define ARC_RETRY_LIMIT_REGISTER 32
#define TIME_IN_MILLIS 33
#define TIMER_REGISTER 34
#define ERROR_REGISTER 35