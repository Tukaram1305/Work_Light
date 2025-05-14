// Markowiak Pawel ARR 2025 v0.3
// WIFI CONSTS n BASE LIBS
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include <AsyncElegantOTA.h>
#include "fauxmoESP.h"
#include <Preferences.h>
#include <ESP32Servo.h>
#include "Kronos.h"

//GLOBALNE
#include "VARS.h"

// MY LIBS
#include "ColorConv.h"
#include "Leds.h"

//  OBJCECTS
AsyncWebServer server(81);
Preferences preferences;
Servo servo1;
#include "servo.h"
SERVO ser;

fauxmoESP alexa;
//PINS  T1 R  G  B / T2  R  G  B   FREQ  -  GLOWNA INSTANCJA
LEDSY leds(13,14,12,     15,16,17, 120);

#include "funcsdefs.h"

void setup() { 
  #include "setup.h" 
  } // SETUP

Kronos bt;
unsigned long PUSHACTION{0};

void loop() {

// HANDLERY
alexa.handle();
ser.handle();
leds.handle();

//PEDAL
if (isPedalReleased==1 && check_pedal() && pedalDel.del(2) ) // Wcisniety
{ isPedalReleased = 0; PUSHACTION = millis(); }

if (isPedalReleased==0 && !check_pedal() && pedalDel.del(2) ) // Zwolniony
{
  if (millis() - PUSHACTION >= 10 ) // zabezpieczenie przed spadkiem napiecia
  {
    isPedalReleased = 1;
    pedalClickCounter += 1;
    pedalTimer = millis();
  }
}

if (millis()-pedalTimer > pedalReleaseTime && pedTimesUp==false && pedalClickCounter > 0)
{
  pedTimesUp = true; 
}

if (!check_pedal() && pedTimesUp==true && pedalClickCounter > 0)
{
  pedTimesUp=false;
  switch (pedalClickCounter)
  {
    case 0: { break; }
    case 1:
    { leds(1, random(0,255), 255, 128); leds(0, random(0,255), 255, 64); break; }
    case 2:
    {
      if (leds.isON()==0) { leds(1, 4,  50, 254); leds(0, 8, 240, 128); }
      else { leds(1, 4,  50, 0); leds(0, 8, 240, 0); }
      break;
    }
    case 3:
    {     if (serCurrPos==0) { serCurrPos=1; ser.serMove(ser.getLowerLimit()); }
          else if (serCurrPos==1) { serCurrPos=0; ser.serMove(ser.getUpperLimit()); }
          break;
    }
    default: break;
  }
  pedalClickCounter = 0;
}
/*
if (isPedalReleased==1 && check_pedal() && !isSerRegulating && pedalDel.del(250)) // Wcisniety
{
  isPedalReleased = 0;
  // AKCJA po WCISNIECIU
  pedalDel.CNT();
}
if (isPedalReleased==0 && !check_pedal() && !isSerRegulating ) // Zwolniony
{
  isPedalReleased=1; 
  // AKCJA po WCISNIECIU
  unsigned long P_TIMER = pedalDel.STP();

  if (P_TIMER > protectionPrsTm && P_TIMER < frsOrdPrsTm) // 25 - 350
  {
    leds(1, random(0,255), 255, 128);
    leds(0, random(0,255), 255, 64);
  }
  else if (P_TIMER >=frsOrdPrsTm && P_TIMER <secOrdPrsTm) // 350 - 1200
  {
    leds(1, 4,  50, 254);
    leds(0, 8, 240, 128);
  }
  else if (P_TIMER >=secOrdPrsTm && P_TIMER <thdOrdPrsTm) // 1200 - 2000
  {
    leds(1, 1, 255, 0);
    leds(0, 1, 255, 0);
  }
  else if (P_TIMER >=thdOrdPrsTm) // > 2000
  {
    if (serCurrPos==0) { serCurrPos=1; ser.serMove(ser.getLowerLimit()); }
    else if (serCurrPos==1) { serCurrPos=0; ser.serMove(ser.getUpperLimit()); }
  }
}
*/

if (rbowState==1 && rbowSTState==0 && rbowdel.del(rbowDel))
{
  leds(1, random(0,255), 255, rbowLightness);
  leds(0, random(0,255), 255, rbowLightness);
}
if (rbowState==0 && rbowSTState==1 && rbowSTdel.del(rbowSLDel))
{
  ++RBSThue1;
  ++RBSThue2offset;
  if (RBSThue1 < 0 || RBSThue1 > 255) RBSThue1 = {0};
  if (RBSThue2offset < 0 || RBSThue2offset > 255) RBSThue2offset = {0};
  leds(1, RBSThue1,       255, rbowLightness);
  leds(0, RBSThue2offset, 255, rbowLightness);
}


}//LOOP END
