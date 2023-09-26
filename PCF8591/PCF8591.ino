#include "MyPCF8591LiB.h"
#include "Wire.h"

#define PCF8591 (0x90 >> 1)


void setup()
{
    Wire.begin();
    Serial.begin(9600);
}

void loop()
{
    Wire.beginTransmission(PCF8591);
    uint8_t cmd = 0x47;
    blinkPCF8594(cmd, PCF8591);

    delay(1000);
}