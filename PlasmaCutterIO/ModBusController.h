#pragma once
#include <Modbus_Slave.h>
#include "RegisterDefines.h"
#include <Arduino.h>
#include <CRC16.h>
#include "Settings.h"
#include "IOLink.h"
#include "ControlLogic.h"
class ModBusController {
	public:
	static ModBusController *getInstance();
	unsigned char process(unsigned char *data, unsigned char index, unsigned int timeRegister);
	unsigned short *getCoilRegister();
	private:
	static ModBusController *instance;
	Settings *settings;
	IOLink *ioLink;
	ControlLogic *controlLogic;
	ModBusSlave *modbus;

	unsigned short coilRegister[NUMBER_OF_REGISTERS];
	ModBusController();
	~ModBusController();
	void updateState();

};

