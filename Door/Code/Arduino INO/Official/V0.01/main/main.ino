#include "main.h"
#include <Wire.h>
#include "AD_D_PiloteI2C.h"

uint32_t i = 0;

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(TRUE);
  piloteI2C1_initialise();
}

void loop() {
  delay(500);

  //Write message to the slave
  uint8_t error = piloteI2C1_appelAuChip(I2C_ADR_NFC,TRUE);

  Serial.printf("endTransmission: %u\n", error);
  //Read 16 bytes from the slave
  uint8_t bytesReceived = piloteI2C1_lisUnEntier(I2C_ADR_NFC);
  Serial.printf("requestFrom: %u\n", bytesReceived);
  if((bool)bytesReceived){ //If received more than zero bytes
    uint8_t temp[bytesReceived];
    I2C1.readBytes(temp, bytesReceived);
    log_print_buf(temp, bytesReceived);
  }
}
