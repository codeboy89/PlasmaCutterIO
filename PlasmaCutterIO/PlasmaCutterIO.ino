#include <Arduino.h>
#include "IOLink.h"
#include "ControlLogic.h"
#include "ModBusController.h"
#include "Settings.h"
#include "Defines.h"
#include "RegisterDefines.h"


IOLink *iolink = IOLink::getInstance();
ControlLogic *controlLogic = ControlLogic::getInstance();
ModBusController *modbusController = ModBusController::getInstance();
Settings *settings = Settings::getInstance();
ModBusSlave ModBus(SLAVE_ID, modbusController->getCoilRegister(), NUMBER_OF_REGISTERS);  // Initialize a new ModBus Slave, Again, you must have my Arduino ModBusSlave Library 

unsigned long lastTime = 0;
unsigned long time = 0;
unsigned long longBreakTime;                                            //Time for 3.5 characters to be RX
unsigned long longKillTime = (long) ((long) KILL_TIME * (long) 1000);      //Time ellapsed between RX that causes system Kill
unsigned long keepAlive = 0;                                           // Keep Alive Counter Variable

unsigned char data[256];                                         // All received data ends up in here, also used as output buffer 
unsigned short index = 0;
unsigned long prevScanTime = 0;
int loopCount = 0;

void setup() {
	longBreakTime = (long) ((long) 28000000.0 / (long) SERIAL_BUAD);
	if(SERIAL_BUAD > 19200) {
		longBreakTime = 1750;                                // 1.75 msec
	}
	Serial.begin(SERIAL_BUAD);
	time = micros();                                       // Preload Time variable with current System microsec
	prevScanTime = millis();
}

void loop() {
	lastTime = time;                             // Set Last_Time to Current Time
	time = micros();
	if(time < lastTime)                          // Counter has rolled over, should take 70 Min
	{
		lastTime = 0;                              // Introduces a small clitch in timing by not accounting for how bad the roll over was.  Happens every 70 Min
													// Result is Delta will be smaller than it should be, Kill and Character Spacing will be usec longer than they should  
	}
	keepAlive += time - lastTime;               // Increment Keep Alive counter

	if(keepAlive >= longKillTime) {               // Communications not Received in Kill_Time, Execute Lost Comm Emerency Procedure
		if(KILL_TIME != 0) {                         // If Kill_Time is 0, then disable Lost Comm Check
			keepAlive = longKillTime;                // Avoid Keep_Alive rollover
			//ModBus.Error = 0xff;                      // Set error code to Lost Comm
			//Register[Error_Register] = ModBus.Error;  // Set Error Register
			//Kill_IO();                                // Kill what should be killed
			//digitalWrite(13, 1);                       // Indicate Error with Solid LED
		}
	} else {                       // Update Analog Pins
		//if(ModBus.Error != 0) {                      // Flash Error LED is ModBus Error != 0
		//	digitalWrite(13, bitRead(Time, 11));        // Toggle LED
		//} else                                        // If no Error
		//{
		//	digitalWrite(13, 0);                       // Turn off LED
		//}
	}

	if(Serial.available() > 0)                   // If Data Avilable
	{
		data[index] = (unsigned char) Serial.read(); // Read Next Char 
		keepAlive = 0;                             // Reset Keep Alive counter     
		lastTime = micros();                       // Update Last_Time to current Time
		index++;                                    // Move Index Counter Forward
	}
	if(index > 0) {
		if(keepAlive >= longBreakTime)             // Transmission Complete, 3.5 char spacing observered
		{
			unsigned int timeRegister = (unsigned int) (millis() / 125.0);  // Converts to 1/8sec and load into Register 
			//ModBus.Process_Data(Data, Index);          // Process Data
			if(modbusController->process(data, index, timeRegister) == 0)                     // If no Errors, then... 
			{
				keepAlive = 0;                         // Reset Keep Alive 
				lastTime = micros();                   // Set Last_Time to current time
			}
			index = 0;                                // Reset Index to 0, no bytes to read
		}
	}
	unsigned long currentScanTime = millis();
	if((currentScanTime - prevScanTime) >= 25) {
		prevScanTime = currentScanTime;
		loopCount+= 25;
	}

	if((loopCount % 25) == 0) {
		controlLogic->process();
	}

	//if((loopCount % 100) == 0) {
	//	if(controlLogic->isAlarm()) {
	//		//iolink->toggleAlarmLed();
	//	}
	//}

	//if((loopCount % 250) == 0) {
	//	if(controlLogic->isArcFailedAlarm()) {
	//		//iolink->toggleAlarmLed();
	//	}
	//}

	//if((loopCount % 1000) == 0) {
	//	//statusReport();
	//}
	//loopCount += 1;
	////delay(1);
	if(loopCount >= 1000) {
		loopCount = 0;
	}
}

void statusReport() {
	if(SERIAL_DEBUGGING) {

		Serial.write(27);       // ESC command
		Serial.print("[2J");    // clear screen command
		Serial.write(27);
		Serial.print("[H");     // cursor to home command
		Serial.print("Alarm Status                              "); Serial.println(controlLogic->isAlarm());
		Serial.print("Arc Faild Alarm                           "); Serial.println(controlLogic->isArcFailedAlarm());
		Serial.print("Torch Fire Command                        "); Serial.println(controlLogic->getTorchFireCommand());
		Serial.print("AC OK                                     "); Serial.println(iolink->isAcOK());
		Serial.print("Over Temp                                 "); Serial.println(iolink->isOverTemp());
		Serial.print("Gas OK                                    "); Serial.println(iolink->isGasOk());
		Serial.print("DC OK                                     "); Serial.println(iolink->isDcOk());
		Serial.print("Pilot Arc Voltage                         "); Serial.println(iolink->getPilotArcVoltage());
		Serial.print("Main Arc Voltage                          "); Serial.println(iolink->getMainArcVoltage());
		Serial.print("Torch Output                              "); Serial.println(iolink->isTorchFiring());
		Serial.print("Arc Start Retry Limit                     "); Serial.println(settings->getArcStartRetryLimit());
		Serial.print("Arc Start Timeout                         "); Serial.println(settings->getArcStartTimeout());
		Serial.print("Arc Start Interlock Timeout               "); Serial.println(settings->getArcStartInterlockTimeout());
		Serial.print("Arc Start Time                            "); Serial.println(controlLogic->getArcStartTime());
		Serial.print("Arc Start Interlock Start Time            "); Serial.println(controlLogic->getArcStartInterlockStartTime());
		Serial.print("Arc Start tries                           "); Serial.println(controlLogic->getArcStartReties());
		Serial.print("Arc Started                               "); Serial.println(controlLogic->isArcStarted());
		Serial.print("Arc Starting                              "); Serial.println(controlLogic->isArcStarting());
		Serial.print("Arc Start Interlock                       "); Serial.println(controlLogic->isArcStartInterlock());
		Serial.print("LoopCount                                 "); Serial.println(loopCount);
		Serial.print("Millis                                    "); Serial.println(millis());
	}
}