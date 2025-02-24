// POZIOM SETUP
#ifndef AWS_H
#define AWS_H

server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  String form {"Tutaj AWS z Work Light!"};
  request->send(200, "application/json",form.c_str());
  Serial.println("Tutaj AWS z Work Light!");
});

server.on("/ledsOff", HTTP_GET, [](AsyncWebServerRequest *request){
  leds.writeRGB(0, 0, 0, 0);
  leds.writeRGB(1, 0, 0, 0);
  String form {"Leds Off"};
  request->send(200, "application/json",form.c_str());
  Serial.println("Leds Off");
});

server.on("/setSer", HTTP_GET, [] (AsyncWebServerRequest *request) {
  if (request->hasParam("v")) 
  {
    String inputMessage = request->getParam("v")->value();
    int val = inputMessage.toInt();
    ser.serMove(val);
    String txt = "OK, SER na "+String(val);
    request->send(200, "text/plain", txt.c_str());
  }
  else request->send(200, "text/plain", String("A NIC!").c_str());
  });

server.on("/setLedRGB", HTTP_GET, [] (AsyncWebServerRequest *request) {
  if (request->hasParam("n") && request->hasParam("r") && request->hasParam("g") && request->hasParam("b")) 
  {
    byte N, R, G, B;
    String inputMessage = request->getParam("n")->value();
    N = static_cast<byte>(inputMessage.toInt());
    inputMessage = request->getParam("r")->value();
    R = static_cast<byte>(inputMessage.toInt());
    inputMessage = request->getParam("g")->value();
    G = static_cast<byte>(inputMessage.toInt());
    inputMessage = request->getParam("b")->value();
    B = static_cast<byte>(inputMessage.toInt());
    leds.writeRGB(N, R, G, B);
    String txt = "OK, LEDY";
    request->send(200, "text/plain", txt.c_str());
  }
  else request->send(200, "text/plain", String("A NIC!").c_str());
  });

server.on("/setLedHSV", HTTP_GET, [] (AsyncWebServerRequest *request) {
  if (request->hasParam("n") && request->hasParam("h") && request->hasParam("s") && request->hasParam("v")) 
  {
    byte N, H, S, V;
    String inputMessage = request->getParam("n")->value();
    N = static_cast<byte>(inputMessage.toInt());
    inputMessage = request->getParam("h")->value();
    H = static_cast<byte>(inputMessage.toInt());
    inputMessage = request->getParam("s")->value();
    S = static_cast<byte>(inputMessage.toInt());
    inputMessage = request->getParam("v")->value();
    V = static_cast<byte>(inputMessage.toInt());
    leds(N, H, S, V);
    // Tylko debug!
    bool ARMP = digitalRead(33);
    bool PEDAL = digitalRead(32);
    String ST{}, STA{};
    (PEDAL) ? ST="no-PRES" : ST="PRES";
    (ARMP) ? STA="HORIZONTAL" : STA="VERTICAL";
    String txt = "OK, LEDY - ARM: "+ String(STA) +", PED: "+ ST;
    request->send(200, "text/plain", txt.c_str());
    //// Tylko debug!
  }
  
  else request->send(200, "text/plain", String("A NIC!").c_str());
  });

server.on("/rbow", HTTP_GET, [] (AsyncWebServerRequest *request) {
  if (request->hasParam("state")) 
  {
    String inputMessage = request->getParam("state")->value();
    int val = inputMessage.toInt();
    if (val==0) { rbowState=0; leds.writeRGB(0, 0, 0, 0); leds.writeRGB(1, 0, 0, 0); } else { rbowState=1; }
    
    if (request->hasParam("del"))
    {
      inputMessage = request->getParam("del")->value();
      val = inputMessage.toInt();
      rbowDel = static_cast<uint16_t>(val);
    }
    if (request->hasParam("lness"))
    {
      inputMessage = request->getParam("lness")->value();
      val = inputMessage.toInt();
      rbowLightness = static_cast<byte>(val);
    }
    String txt = "Rainbow Switch";
    request->send(200, "text/plain", txt.c_str());
  }
  else request->send(200, "text/plain", String("A NIC!").c_str());
  });

server.on("/rbowSL", HTTP_GET, [] (AsyncWebServerRequest *request) {
  if (request->hasParam("state")) 
  {
    RBSThue1 = {0};
    RBSThue2offset = {0};
    String inputMessage = request->getParam("state")->value();
    int val = inputMessage.toInt();
    if (val==0) { rbowSTState=0; leds.writeRGB(0, 0, 0, 0); leds.writeRGB(1, 0, 0, 0); } else { rbowSTState=1; }
    
    if (request->hasParam("del"))
    {
      inputMessage = request->getParam("del")->value();
      val = inputMessage.toInt();
      rbowSLDel = static_cast<uint16_t>(val);
    }
    if (request->hasParam("offset"))
    {
      inputMessage = request->getParam("offset")->value();
      val = inputMessage.toInt();
      RBSThue2offset = static_cast<byte>(val);
    }
    if (request->hasParam("lness"))
    {
      inputMessage = request->getParam("lness")->value();
      val = inputMessage.toInt();
      rbowLightness = static_cast<byte>(val);
    }
    String txt = "RainbowSL Switch";
    request->send(200, "text/plain", txt.c_str());
  }
  else request->send(200, "text/plain", String("A NIC!").c_str());
  });
  
#endif
