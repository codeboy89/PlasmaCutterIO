#include "Settings.h"
Settings *Settings::instance = nullptr;

Settings::Settings() {
}

Settings::~Settings() {
}

Settings *Settings::getInstance() {
	if(instance == nullptr) {
		instance = new Settings();
	}
	return instance;
}

void Settings::storeSettings() {
}

void Settings::setArcStartRetryLimit(int limit) {
	this->arcStartRetryLimit = limit;
}

void Settings::setArcStartTimeout(unsigned long timeout) {
	this->arcStartTimeout = timeout;
}

void Settings::setArcStartInterlockTimeout(unsigned long timeout) {
	this->arcStartInterlockTimeout = timeout;
}

void Settings::setDigitalInPinAcOk(uint8_t pin) {
	this->digitalInPinAcOk = pin;
}

void Settings::setDigitalInPinOverTemp(uint8_t pin) {
	this->digitalInPinOverTemp = pin;
}

void Settings::setDigitalInPinGasOk(uint8_t pin) {
	this->digitalInPinGasOk = pin;
}

void Settings::setDigitalInPinDcOk(uint8_t pin) {
	this->digitalInPinDcOk = pin;
}

void Settings::setDigitalOutPinTorchFire(uint8_t pin) {
	this->digitalOutPinTorchFire = pin;
}

void Settings::setAnalogInPinPilotArcVoltage(uint8_t pin) {
	this->analogInPinPilotArcVoltage = pin;
}

void Settings::setAnalogInPinMainArcVoltage(uint8_t pin) {
	this->analogInPinMainArcVoltage = pin;
}

void Settings::setAnalogIn_0_rawLow(double rawLow) {
	this->analogIn_0_rawLow = rawLow;
}

void Settings::setAnalogIn_0_rawHigh(double rawHigh) {
	this->analogIn_0_rawHigh = rawHigh;
}

void Settings::setAnalogIn_0_scaleLow(double scaleLow) {
	this->analogIn_0_scaleLow = scaleLow;
}

void Settings::setAnalogIn_0_scaleHigh(double scaleHigh) {
	this->analogIn_0_scaleHigh = scaleHigh;
}

void Settings::setAnalogIn_0_factor(double factor) {
	this->analogIn_0_factor = factor;
}

void Settings::setAnalogIn_1_rawLow(double rawLow) {
	this->analogIn_1_rawLow = rawLow;
}

void Settings::setAnalogIn_1_rawHigh(double rawHigh) {
	this->analogIn_1_rawHigh = rawHigh;
}

void Settings::setAnalogIn_1_scaleLow(double scaleLow) {
	this->analogIn_1_scaleLow = scaleLow;
}

void Settings::setAnalogIn_1_scaleHigh(double scaleHigh) {
	this->analogIn_1_scaleHigh = scaleHigh;
}

void Settings::setAnalogIn_1_factor(double factor) {
	this->analogIn_1_factor = factor;
}

int Settings::getArcStartRetryLimit() {
	return this->arcStartRetryLimit;
}

unsigned long Settings::getArcStartTimeout() {
	return this->arcStartTimeout;
}

unsigned long Settings::getArcStartInterlockTimeout() {
	return this->arcStartInterlockTimeout;
}

uint8_t Settings::getDigitalInPinAcOk() {
	return this->digitalInPinAcOk;
}

uint8_t Settings::getDigitalInPinOverTemp() {
	return this->digitalInPinOverTemp;
}

uint8_t Settings::getDigitalInPinGasOk() {
	return this->digitalInPinGasOk;
}

uint8_t Settings::getDigitalInPinDcOk() {
	return this->digitalInPinDcOk;
}

uint8_t Settings::getDigitalOutPinTorchFire() {
	return this->digitalOutPinTorchFire;
}

uint8_t Settings::getAnalogInPinPilotArcVoltage() {
	return this->analogInPinPilotArcVoltage;
}

uint8_t Settings::getAnalogInPinMainArcVoltage() {
	return this->analogInPinMainArcVoltage;
}

double Settings::getAnalogIn_0_rawLow() {
	return this->analogIn_0_rawLow;
}

double Settings::getAnalogIn_0_rawHigh() {
	return this->analogIn_0_rawHigh;
}

double Settings::getAnalogIn_0_scaleLow() {
	return this->analogIn_0_scaleLow;
}

double Settings::getAnalogIn_0_scaleHigh() {
	return this->analogIn_0_scaleHigh;
}

double Settings::getAnalogIn_0_factor() {
	return this->analogIn_0_factor;
}

double Settings::getAnalogIn_1_rawLow() {
	return this->analogIn_1_rawLow;
}

double Settings::getAnalogIn_1_rawHigh() {
	return this->analogIn_1_rawHigh;
}

double Settings::getAnalogIn_1_scaleLow() {
	return this->analogIn_1_scaleLow;
}

double Settings::getAnalogIn_1_scaleHigh() {
	return this->analogIn_1_scaleHigh;
}

double Settings::getAnalogIn_1_factor() {
	return this->analogIn_1_factor;
}
