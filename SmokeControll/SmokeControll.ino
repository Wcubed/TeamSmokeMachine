// Creation date: 2016-06-13
// Controlls the smoke machine, valves and the fans.

#include "constants.h"

void setup() {
  setup_fans();
}


void loop() {
  set_fan(1, IN, ON);
}
