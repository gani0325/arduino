#include <DallasTemperature.h>
int temper = 2;

void setup()
{
    pinMode(temper, OUTPUT);
    Serial.begin(9600);
}

int Initialization()
{
    int existence;

    noInterrupts();
    // master reset pulse
    pinMode(temper, OUTPUT);
    digitalWrite(temper, LOW);

    delayMicroseconds(500);

    // ready to operate
    pinMode(temper, INPUT);
    delayMicroseconds(60);

    existence = digitalRead(temper);

    if (existence == 0)
    {
        interrupts();
        // reset true
        return 0;
    }
    else
    {
        interrupts();
        // reset false
        return 1;
    }
}

// ROM Command Read
uint8_t ReadByte() {
    uint8_t     data = 0;
    int         i;
 
    for (i=0; i<8; i++)
    {
        data |= MasterRead() << i;
    }
    return data;
}

uint8_t MasterRead()
{
    byte data = 0x00;

    for (int i = 0; i < 8; i++)
    {

        pinMode(temper, OUTPUT);
        digitalWrite(temper, LOW);
        delayMicroseconds(3);

        pinMode(temper, INPUT);
        digitalWrite(temper, HIGH);
        delayMicroseconds(10);

        temper |= 1;
        temper &= ~1;

        digitalRead(temper);
        
        data |= temper << i;

        
        interrupts();
        delayMicroseconds(50);
    }
    return data;
}

// ROM Command Write
void MasterWrite(unsigned char data)
{
    for (int i = 0; i < 8; i++)
    {   
        // write 1
        if (data & 1)
        {
            noInterrupts();

            pinMode(temper, OUTPUT);
            digitalWrite(temper, LOW);
            delayMicroseconds(10);

            digitalWrite(temper, HIGH);
            interrupts();
            delayMicroseconds(55);
        }
        // write 0
        else
        {
            noInterrupts();

            pinMode(temper, OUTPUT);
            digitalWrite(temper, LOW);
            delayMicroseconds(65);

            digitalWrite(temper, HIGH);

            interrupts();
            delayMicroseconds(5);
        }
        data >> 1;
    }
}


void loop()
{
    int i;
    char result;

    // Step 1. Initialization
    i = Initialization();

    // reset 이 true 이면
    if (i == 0)
    {
        // Step 2. ROM Command (followed by any required data exchange)
        MasterWrite(0x33);
    
        // int data = MasterRead();
        // // Step 3. DS18B20 Function Command (followed by any required data exchange)
        // FuncCommand(0x33); // '0x33'

        for (int i = 0; i < 8; i++) {
            byte result = MasterRead();
            Serial.print(result, HEX);
        }
        Serial.println();
    }
}
