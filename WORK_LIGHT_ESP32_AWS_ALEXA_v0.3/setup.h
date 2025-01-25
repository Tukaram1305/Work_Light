#ifndef SETUP_H
#define SETUP_H

Serial.begin(115200);
Serial.println("Reset i startuje!");

  pinMode(32, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);
  
  #include "aws.h"
  wifiSetup(); // WIFI SETUP

  // SERVO CONFIG
  servo1.setPeriodHertz(50);
  servo1.write(ser.getUpperLimit());
  servo1.attach(servoPin, 500, 3000);
  //servo1.write(0);
  
  #include "alexa.h"
  
  /// AWS & ElegantOTA
  AsyncElegantOTA.begin(&server); // DOSTEP -> http://192.168.1.81:81/update
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server.begin();
  
#endif
