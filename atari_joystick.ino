#include "Joystick.h"

/*
References
https://docs.arduino.cc/built-in-examples/usb/JoystickMouseControl/
https://www.instructables.com/Arduino-LeonardoMicro-as-Game-ControllerJoystick/
https://github.com/MHeironimus/ArduinoJoystickLibrary/tree/version-1.0
*/

#define LEFT A0
#define RIGHT A1
#define UP A2
#define DOWN A3
#define FIRE A10

void setup() {

  // set the pins we are using
  // (change as approptiate to your wiring)
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(FIRE, INPUT_PULLUP);

  // set to indetify as a game controller (joystick library)
  Joystick.begin(true);
}

void loop() {
  
  unsigned long time = 0;
  int8_t last_x_axis = -1;
  int8_t last_y_axis = -1;
  bool last_fire = false;
  int8_t x_axis = -1;
  int8_t y_axis = -1;
  bool fire;

  // endless loop
  while (true) {

    // wait until the clock shifts
    while (time == millis());

    // calc the current x position
    x_axis = (digitalRead(LEFT)==LOW)? -127 : 0;
    x_axis += (digitalRead(RIGHT)==LOW)? 127 : 0;

    // send an update if it has changed
    if (last_x_axis!=x_axis) {
      Joystick.setXAxis(x_axis);
      last_x_axis = x_axis;
    }

    // calc the current y position
    y_axis = (digitalRead(UP)==LOW)? -127 : 0;
    y_axis += (digitalRead(DOWN)==LOW)? 127 : 0;

    // send an update if it has changed
    if (last_y_axis!=y_axis) {
      Joystick.setYAxis(y_axis);
      last_y_axis = y_axis;
    }

    // check the button position
    fire = (digitalRead(FIRE)==LOW);

    // if it was just pressed, send button0=1
    if (!last_fire && fire) {
      Joystick.setButton(0, 1);
      last_fire = fire;
    }

    // if it was just released, send button0=0
    if (last_fire && !fire) {
      Joystick.setButton(0, 0);
      last_fire = fire;
    }

    // get the current clock time
    time=millis();
  }
}
