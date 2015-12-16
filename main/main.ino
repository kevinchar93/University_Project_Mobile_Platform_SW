#include <RemoteComm.h>
#include <MobilePlatformTypes.h>
#include <PinMap.h>
#include <AccelStepper.h>
#include <MultiStepper.h>


RemoteComm robotComm(COMM_STATE_PIN, COMM_BUTTON_PIN, COMM_LED_PIN, COMM_BAUD_RATE);

void setup() {

    robotComm.waitForConnection();
    Serial.begin(9600);

}

void loop() {

  if (digitalRead(COMM_BUTTON_PIN) == LOW) {
      Serial.println("button pressed");
      char charArray[] = "123:1,425:2,552:3,234:4,234:5,213:6,213:7,243:8,125:9\n";
      robotComm.sendReadings(charArray);
      Serial.println("data sent");
      delay(2000);
      Serial.println("delay started");
  }

}
