// Controls the Arduino using data from a server.
// Author: Wybe Westra
// Creation date: 2016-06-13

import processing.serial.*;

// The serial port.
Serial port;

void setup() {
  // Print available serial ports.
  println(Serial.list());
  
  // Open the serial port.
  port = new Serial(this, Serial.list()[0], 9600);
}


void draw() {
  
}


void mouseClicked() {
  port.write("c\n");
}