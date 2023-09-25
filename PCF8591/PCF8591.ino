#include "Wire.h"
#define PCF8591 (0x90 >> 1)     // 8bit 에서 7bit 로 변경 (1001 | 0000 -> 0100 | 1000 => 48)
byte adcvalue0, adcvalue1, adcvalue2, adcvalue3;

void setup()
{
    Wire.begin();
    Serial.begin(9600);
}

// I2C 통신을 위한 클럭 주파수를 수정
// I2C 주변 장치에는 최소 작동 클럭 주파수가 없지만 일반적으로 100KHz가 기준

void loop()
{
    Wire.beginTransmission(PCF8591);
    Wire.write(0x04);       // 먕량아
    Wire.endTransmission();
    Wire.requestFrom(PCF8591, 5);   // 주소, quantity

    // auto 라서 첫 번째는 무의미해서 한번 더 받음
    adcvalue0=Wire.read();
    adcvalue0=Wire.read();
    adcvalue1=Wire.read();
    adcvalue2=Wire.read();
    adcvalue3=Wire.read();

    Serial.print(adcvalue0);
    Serial.print(" ,");
    Serial.print(adcvalue1);
    Serial.print(" ,");
    Serial.print(adcvalue2);
    Serial.print(" ,");
    Serial.print(adcvalue3);
    Serial.println();

    delay(1000);
}