int led = 13;

void setup() {
    pinMode(led, OUTPUT);
}

void sos_s() {
    for (int i = 0; i < 3; i++) {
        digitalWrite(led, HIGH);
        delay(200);
        digitalWrite(led, LOW);
        delay(200);
    }
}

void sos_o() {
    for (int i = 0; i < 3; i++) {
        digitalWrite(led, HIGH);
        delay(500);
        digitalWrite(led, LOW);
        delay(500);
    }
}

void loop() {
    sos_s();
    sos_o();
    sos_s();
    delay(1000);
}
