#include <RemoteComm.h>
#include <MobilePlatformTypes.h>
#include <PinMap.h>
#include <AccelStepper.h>
#include <MultiStepper.h>


RemoteComm robotComm(COMM_STATE_PIN, COMM_BUTTON_PIN, COMM_LED_PIN, COMM_BAUD_RATE);

void setup() {

    robotComm.waitForConnection();

}

void loop() {

  char charArray[] = "a bunch of characters\n";
  robotComm.sendReadings(charArray);

}
