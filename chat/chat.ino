#include <SoftwareSerial.h>

SoftwareSerial mySerial (3, 4); // rx : 받고 tx : 보내고

void setup() {
    mySerial.begin(9600);
    Serial.begin(9600);
}

void loop() {
    if (mySerial.available() > 0) { // 수신된 데이터 존재 여부 확인
        byte data = mySerial.read(); // 바이트 단위로 읽기

        Serial.print("gani Echo back : ");
        Serial.write(data); // 문자 출력
        Serial.println();
    }

    if (Serial.available() > 0) { // 수신된 데이터 존재 여부 확인
        byte data = Serial.read(); // 바이트 단위로 읽기

        Serial.print("gani Echo back : ");
        mySerial.write(data); // 문자 출력
        Serial.println();
    }
}