#include <I2CSlaveRK.h>

I2CSlave device(Wire, 0x10, 10);

unsigned long lastCounterUpdate = 0;
uint32_t counter = 0;

int ledHum = D5;
int ledTemp = D4;
int ledLight = D6;

void setup() {
    pinMode(ledHum, OUTPUT);
    pinMode(ledTemp, OUTPUT);
    pinMode(ledLight, OUTPUT);
	Serial.begin(9600);

	device.begin();
}

void loop() {
    
	if (millis() - lastCounterUpdate >= 1000) {
		// Once per second increment register 0
		lastCounterUpdate = millis();
		
		Serial.printlnf("%u", device.getRegister(0x0));
	}
	
	uint16_t regAddr;
	while(device.getRegisterSet(regAddr)) {
		// regAddr was updated from the I2C master
		Serial.printlnf("master updated %u to %u", regAddr, device.getRegister(regAddr));
	}
	
	if(device.getRegister(0x0) == 0)
	{
	    digitalWrite(ledHum, LOW);
	}
	
	else if(device.getRegister(0x0) == 1)
	{
	    digitalWrite(ledHum, HIGH);
	}
	
	if(device.getRegister(0x01) == 0)
	{
	    digitalWrite(ledTemp, LOW);
	}
	
	else if(device.getRegister(0x01) == 1)
	{
	    digitalWrite(ledTemp, HIGH);
	}
	
	if(device.getRegister(0x02) == 0)
	{
	    digitalWrite(ledLight, LOW);
	}
	
	else if(device.getRegister(0x02) == 1)
	{
	    digitalWrite(ledLight, HIGH);
	}
}