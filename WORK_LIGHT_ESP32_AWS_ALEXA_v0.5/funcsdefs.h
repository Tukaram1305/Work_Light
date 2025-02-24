#ifndef FUNCSDEFS_H
#define FUNCSDEFS_H

void wifiSetup() {

  // Set WIFI module to STA mode
  WiFi.mode(WIFI_STA);

  // Connect
  Serial.printf("[WIFI] Connecting to %s ", ssid);
  WiFi.begin(ssid, password);

  // Wait
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("Nie udalo sie skonfigurowac WiFi STA");
  }

  // Connected!
  Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());

}

bool check_arm_pos(void)
{
  if (digitalRead(33)) 
  { st_pos = HOR; return false; }
  else
  { st_pos = VERT; return true; }
}
bool check_pedal(void)
{
  if (digitalRead(32)) { return false;  }
  else                 { return true; }
}
// Chwilowo nie uzywane
void saveSerPos(unsigned int ser_val)
{
  preferences.begin("SLOT1", false);
  preferences.putUInt("SER_POS", ser_val);
  preferences.end(); 
}
unsigned int loadSerPos()
{
  preferences.begin("SLOT1", false);
  unsigned int SP = preferences.getUInt("SER_POS", 0); // 0 - default val
  preferences.end(); 
  return SP;
}
#endif
