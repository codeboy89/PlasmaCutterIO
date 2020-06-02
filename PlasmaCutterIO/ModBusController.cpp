#include "ModBusController.h"

ModBusController *ModBusController::instance = nullptr;

ModBusController *ModBusController::getInstance() {
	if(instance == nullptr) {
		instance = new ModBusController();
	}
	return instance;
}

unsigned char ModBusController::process(unsigned char *data, unsigned char index, unsigned int timeRegister) {
	updateState();
	this->coilRegister[TIMER_REGISTER] = timeRegister;
	this->modbus->Process_Data(data, index);
	if(this->modbus->Error == 0)                     // If no Errors, then... 
	{
		return this->modbus->Error;
	} else                                      // If there was an error
	{
		this->coilRegister[ERROR_REGISTER] = this->modbus->Error;// Set Error Code
		return this->modbus->Error;
	}
	updateState();
}

ModBusController::ModBusController() {
	this->settings = Settings::getInstance();
	this->ioLink = IOLink::getInstance();
	this->controlLogic = ControlLogic::getInstance();
	updateState();
	this->modbus = new ModBusSlave(SLAVE_ID, this->coilRegister, NUMBER_OF_REGISTERS);

}

ModBusController::~ModBusController() {
}

unsigned short *ModBusController::getCoilRegister() {
	coilRegister;
}

void ModBusController::updateState() {
	this->coilRegister[ERROR_REGISTER] = this->modbus->Error;
	this->coilRegister[ANALOG_IN_0_RAW_REGISTER] = this->ioLink->getPilotArcVoltageRaw();
	this->coilRegister[ANALOG_IN_0_SCALED_REGISTER] = (unsigned short) (this->ioLink->getPilotArcVoltage() * 10);
	this->coilRegister[ANALOG_IN_0_RAW_LOW_REGISTER] = this->settings->getAnalogIn_0_rawLow();
	this->coilRegister[ANALOG_IN_0_HIGH_REGISTER] = this->settings->getAnalogIn_0_rawHigh();
	this->coilRegister[ANALOG_IN_0_SCALE_LOW_REGISTER] = this->settings->getAnalogIn_0_scaleLow();
	this->coilRegister[ANALOG_IN_0_SCALE_HIGH_REGISTER] = this->settings->getAnalogIn_0_scaleHigh();
	this->coilRegister[ANALOG_IN_0_FACTOR_REGISTER] = this->settings->getAnalogIn_0_factor();
	this->coilRegister[ANALOG_IN_1_RAW_REGISTER] = this->ioLink->getMainArcVoltageRaw();
	this->coilRegister[ANALOG_IN_1_SCALED_REGISTER] = (unsigned short) (this->ioLink->getMainArcVoltage() * 10);
	this->coilRegister[ANALOG_IN_1_RAW_LOW_REGISTER] = this->settings->getAnalogIn_1_rawLow();
	this->coilRegister[ANALOG_IN_1_HIGH_REGISTER] = this->settings->getAnalogIn_1_rawHigh();
	this->coilRegister[ANALOG_IN_1_SCALE_LOW_REGISTER] = this->settings->getAnalogIn_1_scaleLow();
	this->coilRegister[ANALOG_IN_1_SCALE_HIGH_REGISTER] = this->settings->getAnalogIn_1_scaleHigh();
	this->coilRegister[ANALOG_IN_1_FACTOR_REGISTER] = this->settings->getAnalogIn_1_factor();
	this->coilRegister[PILOT_ARC_VOLTAGE_REGISTER] = this->ioLink->getPilotArcVoltage();
	this->coilRegister[MAIN_ARC_VOLTAGE_REGISTER] = this->ioLink->getMainArcVoltage();
	this->coilRegister[AC_OK_RAW_REGISTER] = this->ioLink->isAcOK();
	this->coilRegister[OVER_TEMP_RAW_REGISTER] = this->ioLink->isOverTemp();
	this->coilRegister[GAS_OK_RAW_REGISTER] = this->ioLink->isGasOk();
	this->coilRegister[DC_OK_RAW_REGISTER] = this->ioLink->isDcOk();
	this->controlLogic->setTorchFireCommand((bool) this->coilRegister[TORCH_FIRE_COMMAND_REGISTER]);
	this->coilRegister[TORCH_FIRE_FIRING_REGISTER] = this->ioLink->isTorchFiring();
	this->coilRegister[SYSTEM_ALARM_REGISTER] = this->controlLogic->isAlarm();
	this->coilRegister[ARC_FAILED_ALARM_REGISTER] = this->controlLogic->isArcFailedAlarm();
	this->coilRegister[ARC_STARTED_REGISTER] = this->controlLogic->isArcStarted();
	this->coilRegister[ARC_STARTING_REGISTER] = this->controlLogic->isArcStarting();
	this->coilRegister[ARC_START_INTERLOCK_REGISTER] = this->controlLogic->isArcStartInterlock();
	this->coilRegister[ARC_START_TIME_REGISTER] = (unsigned long) this->controlLogic->getArcStartTime();
	this->coilRegister[ARC_START_INTERLOCK_START_TIME_REGISTER] = (unsigned long) this->controlLogic->getArcStartInterlockStartTime();
	this->coilRegister[ARC_RETRIES_REGISTER] = this->controlLogic->getArcStartReties();
	this->coilRegister[ARC_START_TIMEOUT_REGISTER] = this->settings->getArcStartTimeout();
	this->coilRegister[ARC_INTERLOCK_TIMEOUT_REGISTER] = this->settings->getArcStartInterlockTimeout();
	this->coilRegister[ARC_RETRY_LIMIT_REGISTER] = this->settings->getArcStartRetryLimit();
	this->coilRegister[TIME_IN_MILLIS] = (unsigned short) millis();
}

