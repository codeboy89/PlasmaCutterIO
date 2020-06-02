#pragma once
#include <Arduino.h>
class Settings {
	private:
	static Settings *instance;

	Settings();
	~Settings();

	int arcStartRetryLimit = 5;
	unsigned long arcStartTimeout = 1500;
	unsigned long arcStartInterlockTimeout = 3000;

	uint8_t digitalInPinAcOk = 7;
	uint8_t digitalInPinOverTemp = 6;
	uint8_t digitalInPinGasOk = 5;
	uint8_t digitalInPinDcOk = 4;

	uint8_t digitalOutPinTorchFire = 8;

	uint8_t analogInPinPilotArcVoltage = A0;
	uint8_t analogInPinMainArcVoltage = A1;

	double analogIn_0_rawLow = 0.0;
	double analogIn_0_rawHigh = 1023.0;
	double analogIn_0_scaleLow = 0.0;
	double analogIn_0_scaleHigh = 5.0;
	double analogIn_0_factor = 50.0;
	double analogIn_1_rawLow = 0.0;
	double analogIn_1_rawHigh = 1023.0;
	double analogIn_1_scaleLow = 0.0;
	double analogIn_1_scaleHigh = 5.0;
	double analogIn_1_factor = 50.0;

	public:
	static Settings *getInstance();
	void storeSettings();
	void setArcStartRetryLimit(int limit);
	void setArcStartTimeout(unsigned long timeout);
	void setArcStartInterlockTimeout(unsigned long timeout);

	void setDigitalInPinAcOk(uint8_t pin);
	void setDigitalInPinOverTemp(uint8_t pin);
	void setDigitalInPinGasOk(uint8_t pin);
	void setDigitalInPinDcOk(uint8_t pin);

	void setDigitalOutPinTorchFire(uint8_t pin);

	void setAnalogInPinPilotArcVoltage(uint8_t pin);
	void setAnalogInPinMainArcVoltage(uint8_t pin);

	void setAnalogIn_0_rawLow(double rawLow);
	void setAnalogIn_0_rawHigh(double rawHigh);
	void setAnalogIn_0_scaleLow(double scaleLow);
	void setAnalogIn_0_scaleHigh(double scaleHigh);
	void setAnalogIn_0_factor(double factor);

	void setAnalogIn_1_rawLow(double rawLow);
	void setAnalogIn_1_rawHigh(double rawHigh);
	void setAnalogIn_1_scaleLow(double scaleLow);
	void setAnalogIn_1_scaleHigh(double scaleHigh);
	void setAnalogIn_1_factor(double factor);


	int getArcStartRetryLimit();
	unsigned long getArcStartTimeout();
	unsigned long getArcStartInterlockTimeout();

	uint8_t getDigitalInPinAcOk();
	uint8_t getDigitalInPinOverTemp();
	uint8_t getDigitalInPinGasOk();
	uint8_t getDigitalInPinDcOk();

	uint8_t getDigitalOutPinTorchFire();

	uint8_t getAnalogInPinPilotArcVoltage();
	uint8_t getAnalogInPinMainArcVoltage();

	double getAnalogIn_0_rawLow();
	double getAnalogIn_0_rawHigh();
	double getAnalogIn_0_scaleLow();
	double getAnalogIn_0_scaleHigh();
	double getAnalogIn_0_factor();

	double getAnalogIn_1_rawLow();
	double getAnalogIn_1_rawHigh();
	double getAnalogIn_1_scaleLow();
	double getAnalogIn_1_scaleHigh();
	double getAnalogIn_1_factor();
};

