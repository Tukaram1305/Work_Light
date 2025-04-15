#ifndef VARS_H
#define VARS_H
// WIFI/ALEXA
const char* ssid = "RagNet";
const char* password =  "azgard666";
// spobuje ustawic statyczne IP
IPAddress local_IP(192, 168, 1, 81);
IPAddress gateway(192, 168, 1 ,1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8); 
IPAddress secondaryDNS(8, 8, 4, 4);

//PEDAL
const uint16_t protectionPrsTm {25};  // zabezpieczenie przeciwspeciowe
const uint16_t frsOrdPrsTm {350};     // kolory losowo
const uint16_t secOrdPrsTm {1200};    // normalny tryb
const uint16_t thdOrdPrsTm {2000};    // leds off       - x > // motory on/off
//PEDAL NOWE
uint16_t pedalReleaseTime{350}; // ms
uint32_t pedalTimer{0};
byte pedalClickCounter{0};
bool pedTimesUp{false};

enum START_POS_DEF {VERT=0, HOR=1};
START_POS_DEF st_pos = VERT;
bool isSerRegulating{0};
bool isPedalReleased{1};
Kronos pedalDel;
int SERPOS{0};
bool serCurrPos{0};
const int servoPin{25}; // PIN IMPORTANT!
// ALEXA
bool currAlexaState{0};
byte currAlexaVal{0};
bool currAlexaStateEngine{0};
byte currAlexaValEngine{0};
const char* ALX_DEV1_NAME = {"Work Light"};
const char* ALX_DEV2_NAME = {"Work Engine"};
//RAINBOW FX
Kronos rbowdel;
volatile uint16_t rbowDel{3000};
volatile bool rbowState{0};
volatile uint16_t rbowLightness{128}; // uzywa RB1 i RB2

Kronos rbowSTdel;
volatile uint16_t rbowSLDel{40};
volatile bool rbowSTState{0};
volatile byte RBSThue1{0};
volatile byte RBSThue2offset{128};
#endif
