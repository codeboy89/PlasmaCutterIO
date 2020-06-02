#include "ControlLogic.h"
ControlLogic *ControlLogic::instance = nullptr;
ControlLogic::ControlLogic() {
	this->ioLink = IOLink::getInstance();
}

ControlLogic::~ControlLogic() {
}

ControlLogic *ControlLogic::getInstance() {
	if(instance == nullptr) {
		instance = new ControlLogic();
	}
	return instance;
}

void ControlLogic::process() {
	this->ioLink->readInputs();
	// check for alarms
	if(!ioLink->isGasOk() || ioLink->isOverTemp() || !ioLink->isAcOK()) {
		alarmStatus = true;
	} else {
		if(alarmStatus) {
			alarmStatus = false;
			arcStartReties = 0;
		}
	}

	if(!alarmStatus && !arcFailedAlarm) {

		// Shutdown if DC ok is lost
		if(torchOutput && !ioLink->isDcOk() && !arcStarting) {
			torchOutput = false;
		}

		// Shutdown if Over Temp
		if(ioLink->isOverTemp()) {
			torchOutput = false;
			arcStarting = false;
			arcStartInterlock = true;
			arcStarted = false;
		}

		// Try to fire torch, start timer
		if(!torchOutput && torchFire && !alarmStatus && !arcStartInterlock && !ioLink->isDcOk() && !arcFailedAlarm) {
			torchOutput = true;
			arcStarting = true;
			arcStartTime = millis();
		}

		if(arcStartReties >= ARC_START_RETRY_LIMIT) {
			arcFailedAlarm = true;
		}

		// check if arc is starting and DC ok is active
		if(arcStarting) {
			if(ioLink->isDcOk()) {
				arcStartReties = 0;
				arcStarted = true;
				arcStarting = false;
				arcStartInterlock = false;
			} else {
				unsigned long nowTime = millis();
				if((nowTime - arcStartTime) >= ARC_START_TIMEOUT) {
					torchOutput = false;
					arcStartInterlock = true;
					arcStartInterlockStartTime = millis();
					arcStarting = false;
					arcStarted = false;
					//alarmStatus = true;
					arcStartReties++;
				}
			}
		}

		// check if interlock timeout is achived
		if(arcStartInterlock && !arcStarted) {
			unsigned long nowTime = millis();
			if((nowTime - arcStartInterlockStartTime) >= ARC_START_intERLOCK_TIMEOUT) {
				arcStartInterlock = false;
				torchOutput = torchFire;
				arcStarting = true;
				arcStartTime = millis();
				alarmStatus = false;
			}
		}
		if(arcStarted) {
			torchOutput = torchFire;
		}
	} else {
		torchOutput = false;
	}
	this->ioLink->setTorchFire(this->torchOutput);

}

bool ControlLogic::isAlarm() {
	return this->alarmStatus;
}

bool ControlLogic::isArcFailedAlarm() {
	return this->arcFailedAlarm;
}

bool ControlLogic::getTorchOuputCommand() {
	return this->torchOutput;
}

bool ControlLogic::getTorchFireCommand() {
	return this->torchFire;
}

bool ControlLogic::isArcStarted() {
	return this->arcStarted;
}

bool ControlLogic::isArcStarting() {
	return this->arcStarting;
}

bool ControlLogic::isArcStartInterlock() {
	return this->arcStartInterlock;
}

unsigned long ControlLogic::getArcStartTime() {
	return this->arcStartTime;
}

unsigned long ControlLogic::getArcStartInterlockStartTime() {
	return this->arcStartInterlockStartTime;
}

int ControlLogic::getArcStartReties() {
	return this->arcStartReties;
}

void ControlLogic::setTorchFireCommand(bool torchFireCommand) {
	this->torchFire = torchFireCommand;
}
