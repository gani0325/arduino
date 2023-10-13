#include <string.h>
int switchPin[] = {2, 3, 4, 5, 6, 7, 8, 9};
void setup()
{
    Serial.begin(9600);
    int count = sizeof(switchPin) / sizeof(switchPin[0]);
    for (size_t i = 0; i < count; i++)
    {
        pinMode(switchPin[i], INPUT_PULLUP);
    }
}

void loop()
{

    int count = sizeof(switchPin) / sizeof(switchPin[0]);
    byte switchBit = 0;
    for (size_t i = 0; i < count; i++)
    {
        switchBit |= (digitalRead(switchPin[i]) << i);
    }

    //  Serial.print(map(analogRead(A0), 0, 1023, 0, 100));
    //  Serial.print(" : ");
    //  Serial.println(map(analogRead(A1), 0, 1023, 0, 100));

     Serial.println(switchBit, BIN);
     int anaX = analogRead(A0);
     int anaY= analogRead(A1);
    // Serial.print(ana1);
    // Serial.print(" : ");
    // Serial.println(ana2);
    String sendData;
    sendData+=anaX;sendData+=",";
    sendData+=anaY;sendData+=",";
    sendData+=switchBit;
    Serial.println(sendData);
    delay(100);
}