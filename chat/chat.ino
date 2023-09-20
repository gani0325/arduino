#include <SoftwareSerial.h>
#include <string.h>

SoftwareSerial mySerial (3, 4); // rx : 받고 tx : 보내고

void setup() {
    mySerial.begin(9600);
    Serial.begin(9600);
}

String str;

void loop() {
    if (mySerial.available() > 0) { // 수신된 데이터 존재 여부 확인
        
        char data = mySerial.read(); // 바이트 단위로 읽기
        str.concat(data);
        delay(10);

        if (mySerial.available() == 0) {
            Serial.println(str); // 문자 출력
            str = "";
        }
    }

    if (Serial.available() > 0) { // 수신된 데이터 존재 여부 확인
        char data = Serial.read(); // 바이트 단위로 읽기

        mySerial.write(data); // 문자 출력
    }
}