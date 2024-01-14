#ifndef REG_H
#define REG_H
#include <REGS.h>
#endif
#include <Arduino.h>
#include <ModbusRtu.h>
#include <MachineControl.h>

Modbus hmi(1,Serial,0);
uint8_t mBusLenght = sizeof(data) / sizeof(int);

void setup() {
  Serial.begin( 9600, SERIAL_8N1 );
  hmi.start();
  analogBegin();
}

void loop() {
  hmi.poll(data, mBusLenght);
  machine_run();
}