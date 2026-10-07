#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

const int relayPins[8] = {13, 12, 14, 27, 26, 25, 33, 32};

void setup() {
  Serial.begin(115200);
 
  SerialBT.begin("ESP32_Relay_Control");

  for (int i = 0; i < 8; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH); 
  }
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();

    if (command == '1') digitalWrite(relayPins[0], LOW);
    else if (command == 'a') digitalWrite(relayPins[0], HIGH);

    else if (command == '2') digitalWrite(relayPins[1], LOW);
    else if (command == 'b') digitalWrite(relayPins[1], HIGH);

    else if (command == '3') digitalWrite(relayPins[2], LOW);
    else if (command == 'c') digitalWrite(relayPins[2], HIGH);

    else if (command == '4') digitalWrite(relayPins[3], LOW);
    else if (command == 'd') digitalWrite(relayPins[3], HIGH);

    else if (command == '5') digitalWrite(relayPins[4], LOW);
    else if (command == 'e') digitalWrite(relayPins[4], HIGH);

    else if (command == '6') digitalWrite(relayPins[5], LOW);
    else if (command == 'f') digitalWrite(relayPins[5], HIGH);

    else if (command == '7') digitalWrite(relayPins[6], LOW);
    else if (command == 'g') digitalWrite(relayPins[6], HIGH);

    else if (command == '8') digitalWrite(relayPins[7], LOW);
    else if (command == 'h') digitalWrite(relayPins[7], HIGH);

    // All ON
    else if (command == 'x') { 
      for (int i = 0; i < 8; i++) digitalWrite(relayPins[i], LOW);
    }
    // All OFF
    else if (command == 'X') { 
      for (int i = 0; i < 8; i++) digitalWrite(relayPins[i], HIGH);
    }
  }
}
