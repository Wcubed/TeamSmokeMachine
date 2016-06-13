// Direction variables.
const bool IN = 0;
const bool OUT = 1;

// State variables.
const bool ON = true;
const bool OFF = false;


// Number of boxes.
const int BOXAMOUNT = 5;


// Fan controll pin numbers.
const int fanPins[BOXAMOUNT][2] = {
  {1, 2},
  {3, 4},
  {5, 6},
  {7, 8},
  {9, 10}
};

// Valve controll pin numbers.
const int valvePins[BOXAMOUNT][2] = {
  {1, 2},
  {3, 4},
  {5, 6},
  {7, 8},
  {9, 10}
};

