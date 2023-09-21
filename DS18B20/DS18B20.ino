#define ONE_WIRE_BUS 2

// Step 1. Initialization 
// Step 2. ROM Command (followed by any required data exchange) 
// Step 3. DS18B20 Function Command (followed by any required data exchange) 

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

}

void loop(void)
{
  Serial.print("Requesting temperatures...");
  
  Serial.println("DONE");
  Serial.print("Temperature for the device 1 (index 0) is: ");
  Serial.println(sensors.getTempCByIndex(0));
}