// POZIOM SETUP
#ifndef ALEXA_H
#define ALEXA_H
alexa.createServer(true); // not needed, this is the default value
  alexa.setPort(80); // This is required for gen3 devices
  alexa.enable(true);
  // Add virtual devices
  alexa.addDevice(ALX_DEV1_NAME);
  
  alexa.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
    
  Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
  if (strcmp(device_name, ALX_DEV1_NAME)==0) {
      currAlexaState = state ? 1 : 0;
      currAlexaVal = value;
      if (state)
      {
        leds(1, 4, 50, value);
        leds(0, 8, 240, (value > 1) ? value/2 : 0);
        ser.serMove(ser.getLowerLimit());
      }
      else
      {
        leds(1, 5, 70, 0);
        leds(0, 8, 240, 0);
        ser.serMove(ser.getUpperLimit());
      }
      // Gorna Tasma - BIALE
        //state ? leds(1, 4, 50, value) : leds(1, 5, 70, 0);
      // Dolna Tasma - CIEPLE BIALE 1/2 Jasnosci
        //state ? leds(0, 8, 240, (value > 1) ? value/2 : 0) : leds(0, 8, 240, 0);
  }

  });
#endif
