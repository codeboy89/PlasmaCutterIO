#pragma once
#include "IOLink.h"
class ControlLogic {
	private:
	static ControlLogic *instance;
	IOLink *ioLink;
	// State Variables
	bool statusLedState = false;
	bool alarmStatus = false;
	bool arcFailedAlarm = false;
	bool torchOutput = false;
	bool torchFire = true;
	bool arcStarted = false;
	bool arcStarting = false;
	bool arcStartInterlock = false;

	// Timer Variables
	unsigned long arcStartTime = 0;
	unsigned long arcStartInterlockStartTime = 0;

	// Counter Variables
	int arcStartReties = 0;


	ControlLogic();
	~ControlLogic();
	public:
	static ControlLogic *getInstance();
	void process();
	bool isAlarm();
	bool isArcFailedAlarm();
	bool getTorchOuputCommand();
	bool getTorchFireCommand();
	bool isArcStarted();
	bool isArcStarting();
	bool isArcStartInterlock();
	unsigned long getArcStartTime();
	unsigned long getArcStartInterlockStartTime();
	int getArcStartReties();
	void setTorchFireCommand(bool torchFireCommand);
};

