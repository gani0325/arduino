#include "MyPCF8591LiB.h"
#include "Wire.h"
#include "PCF8591.h"

PCF8591 dev(0x48);

#define address (0x90 >> 1) // 8bit 에서 7bit 로 변경 (1001 | 0000 -> 0100 | 1000 => 48)
extern byte adcvalue;

void setup()
{
    Wire.begin();
    Serial.begin(9600);
}

void loop()
{
    Wire.beginTransmission(address);

    uint8_t channel = 0;    // channel {4, 3, 3, 2 };
    uint8_t control = 0;    // mode
    uint8_t mode = 0;
    

    switch (mode)
    {
    case 0:
        control &= 0b01000100; //  clear all except flags
        control |= (0 << 4);
        control |= channel;

        blinkPCF8594(control, address);
        break;
    case 1:
        control &= 0b01000100; //  clear all except flags
        control |= (1 << 4);
        control |= channel;
        blinkPCF8594(control, address);
        break;
    case 2:
        control &= 0b01000100; //  clear all except flags
        control |= (2 << 4);
        control |= channel;
        blinkPCF8594(control, address);
        break;
    case 3:
        control &= 0b01000100; //  clear all except flags
        control |= (3 << 4);
        control |= channel;
        blinkPCF8594(control, address);
        break;
    }

    Serial.print(adcvalue);
    Serial.println();
}