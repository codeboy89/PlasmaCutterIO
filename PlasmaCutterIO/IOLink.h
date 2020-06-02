#pragma once
#include "Defines.h"
#include <Arduino.h>
#include "Settings.h"
class IOLink {

	private:
	static IOLink *instance;
	Settings *settings;
	// State Variables 
	bool torchFireCommand = false; 

	bool ledAlarmOutputState = false;
	bool acOKActive = false;
	bool overTempActive = false;
	bool gasOKActive = false;
	bool dcOKActive = false;

	// Analog Variables
	double pilotArcVoltageRaw = 0.0;
	double mainArcVoltageRaw = 0.0;

	// Analog Variables
	double pilotArcVoltage = 0.0;
	double mainArcVoltage = 0.0;
	double mapD(double x, double in_min, double in_max, double out_min, double out_max);
	IOLink();
	~IOLink();
	void readAnalogInputs();
	public:
	static IOLink *getInstance();
	void toggleAlarmLed();
	void readInputs();
	void setTorchFire(bool command);
	bool isAcOK();
	bool isOverTemp();
	bool isGasOk();
	bool isDcOk();
	bool isTorchFiring();
	double getPilotArcVoltageRaw();
	double getMainArcVoltageRaw();
	double getPilotArcVoltage();
	double getMainArcVoltage();
};

