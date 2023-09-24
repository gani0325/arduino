// Pin connected to the DS18B20 sensor
const int ds18b20Pin = 2; // Replace with your actual pin number

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    goto MEAS;
    Serial.print("Serial Number: ");

    // Reset the 1-Wire bus
    if (!resetSensor())
    {
        Serial.println("No DS18B20 detected.");
        delay(1000);
        return;
    }

    // Send command to read ROM
    sendCommand(0x33); // Read ROM command

    // Read the 64-bit ROM code
    for (int i = 0; i < 8; i++)
    {
        byte byteRead = readByte();
        Serial.print(byteRead, HEX);
        if (i < 7)
            Serial.print('-'); // Print a dash between bytes
    }


MEAS:
    if (!resetSensor())
    {
        Serial.println("No DS18B20 detected.");
        delay(1000);
        return;
    }
    sendCommand(0xCC);
    sendCommand(0x44); // STARTCONVO
    delay(950);

    if (!resetSensor())
    {
        Serial.println("No DS18B20 detected.");
        delay(1000);
        return;
    }
    sendCommand(0xCC);
    sendCommand(0xBE);




// Read the 64-bit ROM code
    for (int i = 0; i < 9; i++)
    {
        byte byteRead = readByte();
        Serial.print(byteRead, HEX);
        if (i < 7)
            Serial.print('-'); // Print a dash between bytes
    }
    Serial.println();

/*
    int16_t temperatureData = readTemperature();

    float temperatureCelsius = temperatureData / 16.0;

    Serial.print(temperatureCelsius);
    Serial.println(" °C");
**/
}

bool resetSensor()
{
    // Pull the data line low for a reset pulse

    digitalWrite(ds18b20Pin, LOW);
    pinMode(ds18b20Pin, OUTPUT);

    delayMicroseconds(480); // Hold for 480us
    pinMode(ds18b20Pin, INPUT);
    delayMicroseconds(100); // Wait for DS18B20 to respond

    // Check if the DS18B20 pulled the line low (presence pulse)
    if (digitalRead(ds18b20Pin) == LOW)
    {
        delayMicroseconds(380); // Wait for presence pulse to end
        // Serial.println("Reset OK\n");
        return true;
    }
    else
    {
        // Serial.println("Reset NG\n");
        return false; // No DS18B20 detected
    }
}

void skip()
{
}
void sendCommand(byte cmd)
{
    for (int i = 0; i < 8; i++)
    {
        delayMicroseconds(10); // Write 0 bit
        if (bitRead(cmd, i))
        {
            noInterrupts();
            digitalWrite(ds18b20Pin, LOW);
            pinMode(ds18b20Pin, OUTPUT);
            delayMicroseconds(10);

            digitalWrite(ds18b20Pin, HIGH);
            interrupts();
            delayMicroseconds(55);
        }
        else
        {
            noInterrupts();
            digitalWrite(ds18b20Pin, LOW);
            pinMode(ds18b20Pin, OUTPUT);
            delayMicroseconds(65);
            digitalWrite(ds18b20Pin, HIGH);
            interrupts();
            delayMicroseconds(5);
        }
        // delayMicroseconds(1);       // Recovery time between bits
        // pinMode(ds18b20Pin, INPUT); // Release the data line
    }
}

byte readByte()
{
    byte byteRead = 0;
    for (int i = 0; i < 8; i++)
    {

        noInterrupts();
        pinMode(ds18b20Pin, OUTPUT);
        digitalWrite(ds18b20Pin, LOW);
        delayMicroseconds(3);

        pinMode(ds18b20Pin, INPUT);
        delayMicroseconds(10);
        byteRead |= (digitalRead(ds18b20Pin) << i);
        interrupts();
        delayMicroseconds(53);
    }
    return byteRead;
}

int16_t readTemperature()
{
    // Read two bytes of temperature data
    byte lowByte = readByte();
    byte highByte = readByte();

    // Combine the two bytes into a 16-bit integer
    int16_t temperatureData = (highByte << 8) | lowByte;

    return temperatureData;
}