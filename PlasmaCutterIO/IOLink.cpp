#include "IOLink.h"
IOLink *IOLink::instance = nullptr;

double IOLink::mapD(double x, double in_min, double in_max, double out_min, double out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

IOLink::IOLink() {
	this->settings = Settings::getInstance();
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(this->settings->getDigitalOutPinTorchFire(), OUTPUT);
	pinMode(this->settings->getDigitalInPinAcOk(), INPUT_PULLUP);
	pinMode(this->settings->getDigitalInPinOverTemp(), INPUT_PULLUP);
	pinMode(this->settings->getDigitalInPinGasOk(), INPUT_PULLUP);
	pinMode(this->settings->getDigitalInPinDcOk(), INPUT_PULLUP);
}

IOLink::~IOLink() {
}

void IOLink::readAnalogInputs() {
	pilotArcVoltageRaw = analogRead(this->settings->getAnalogInPinPilotArcVoltage());
	mainArcVoltageRaw = analogRead(this->settings->getAnalogInPinMainArcVoltage());
	pilotArcVoltage = mapD(pilotArcVoltageRaw, this->settings->getAnalogIn_0_rawLow(), this->settings->getAnalogIn_0_rawHigh(), this->settings->getAnalogIn_0_scaleLow(), this->settings->getAnalogIn_0_scaleHigh()) * this->settings->getAnalogIn_0_factor();
	mainArcVoltage = mapD(mainArcVoltageRaw, this->settings->getAnalogIn_1_rawLow(), this->settings->getAnalogIn_1_rawHigh(), this->settings->getAnalogIn_1_scaleLow(), this->settings->getAnalogIn_1_scaleHigh()) * this->settings->getAnalogIn_1_factor();
}

IOLink *IOLink::getInstance() {
	if(instance == nullptr) {
		instance = new IOLink();
	}
	return instance;
}

void IOLink::toggleAlarmLed() {
	if(ledAlarmOutputState) {
		ledAlarmOutputState = false;
		//digitalWrite(LED_BUILTIN, LOW);
	} else {
		ledAlarmOutputState = true;
		//digitalWrite(LED_BUILTIN, HIGH);
	}
}

void IOLink::readInputs() {
	readAnalogInputs();
	if(digitalRead(this->settings->getDigitalInPinAcOk()) == LOW) {
		acOKActive = true;
	} else {
		acOKActive = false;
	}

	if(digitalRead(this->settings->getDigitalInPinOverTemp()) == LOW) {
		overTempActive = true;
	} else {
		overTempActive = false;
	}

	if(digitalRead(this->settings->getDigitalInPinGasOk()) == LOW) {
		gasOKActive = true;
	} else {
		gasOKActive = false;
	}

	if(digitalRead(this->settings->getDigitalInPinDcOk()) == LOW) {
		dcOKActive = true;
	} else {
		dcOKActive = false;
	}
}


void IOLink::setTorchFire(bool command) {
	this->torchFireCommand = command;
	if(torchFireCommand) {
		digitalWrite(this->settings->getDigitalOutPinTorchFire(), HIGH);
	} else {
		digitalWrite(this->settings->getDigitalOutPinTorchFire(), LOW);
	}
}

bool IOLink::isAcOK() {
	return this->acOKActive;
}

bool IOLink::isOverTemp() {
	return this->overTempActive;
}

bool IOLink::isGasOk() {
	return this->gasOKActive;
}

bool IOLink::isDcOk() {
	return this->dcOKActive;
}

bool IOLink::isTorchFiring() {
	return this->torchFireCommand;
}

double IOLink::getPilotArcVoltageRaw() {
	return this->pilotArcVoltageRaw;
}

double IOLink::getMainArcVoltageRaw() {
	return this->mainArcVoltageRaw;
}

double IOLink::getPilotArcVoltage() {
	return this->pilotArcVoltage;
}

double IOLink::getMainArcVoltage() {
	return this->mainArcVoltage;
}
