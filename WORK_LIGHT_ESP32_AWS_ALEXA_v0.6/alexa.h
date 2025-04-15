// POZIOM SETUP
#ifndef ALEXA_H
#define ALEXA_H
alexa.createServer(true);
  alexa.setPort(80);
  alexa.enable(true);
  // Dodaj uzarzenia
  alexa.addDevice(ALX_DEV1_NAME);
  alexa.addDevice(ALX_DEV2_NAME);

  alexa.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
  Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
  // LIGHTS
  if (strcmp(device_name, ALX_DEV1_NAME)==0) {
      currAlexaState = state ? 1 : 0;
      currAlexaVal = value;

      if (currAlexaVal > 0)
      { leds(1, 4, 50, value); leds(0, 8, 240, (value > 1) ? value/2 : 0); }
      else if (currAlexaVal == 0)
      { leds(1, 5, 70, 0); leds(0, 8, 240, 0); }
      if (currAlexaState==0)
      { leds(1, 5, 70, 0); leds(0, 8, 240, 0); }
  }
  // SERVO
  if (strcmp(device_name, ALX_DEV2_NAME)==0) {
      currAlexaStateEngine = state ? 1 : 0;
      currAlexaValEngine = value;
      byte calcAngle = static_cast<byte>(ser.getUpperLimit() - (ser.getUpperLimit()/255.*value));
      if (value > 0) // ON
      { ser.serMove(calcAngle); }
      else // OFF (VERTICAL)
      { ser.serMove(ser.getUpperLimit()); }
      if (currAlexaStateEngine==0)
      { ser.serMove(ser.getUpperLimit()); }
  }
  
  });
  

#endif
