// This #include statement was automatically added by the Particle IDE.

// This #include statement was automatically added by the Particle IDE.

#include "Particle.h"

#include "I2CSlaveMasterRK.h"

#include <BH1750.h>


// This #include statement was automatically added by the Particle IDE.

// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT.h>


#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22		// DHT 22 (AM2302)


DHT dht(DHTPIN, DHTTYPE);
I2CSlaveMaster device(Wire, 0x10);
BH1750 sensor(0x23, Wire);

const unsigned long CHECK_PERIOD_MS = 1000;
unsigned long lastCheck = 0;


uint32_t counter = 0;
void setup() {
	Serial.begin(9600);
	device.begin();
	dht.begin();
	sensor.begin();
	sensor.set_sensor_mode(BH1750::forced_mode_high_res2);
}

void loop() {
    
    float h = dht.getHumidity();
// Read temperature as Celsius
	float t = dht.getTempCelcius();
// Read temperature as Farenheit
	float f = dht.getTempFarenheit();
  
// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(t) || isnan(f)) {
		Serial.println("Failed to read from DHT sensor!");
		return;
	}
	
	Serial.print("Humid: "); 
	Serial.print(h);
	Serial.print("% - ");
	Serial.print("Temp: "); 
	Serial.print(t);
	Serial.print("*C ");


	uint32_t reg1;
	
	if (!device.readRegister(1, reg1)) {
		Serial.println("read register 1 failed");
		return;
	}

	Serial.printlnf("slave 1 = %u", reg1);

	if(h < 80)
	{
	    device.writeRegister(0, 1);
	}
		
	else
	{
	    device.writeRegister(0, 0);
	}
	
	if(t > 27 || t < 23)
	{
	    device.writeRegister(1, 1);
	}
	
	else
	{
	    device.writeRegister(1, 0);
	}
	
	 sensor.make_forced_measurement();
	  
	if(sensor.get_light_level() < 400)
	{
	   device.writeRegister(2, 1);
	}
	
	else
	{
	    device.writeRegister(2, 0);
	}
	
	delay(2000);
}
