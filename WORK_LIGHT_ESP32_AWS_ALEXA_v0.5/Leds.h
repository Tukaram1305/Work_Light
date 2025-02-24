#ifndef LEDS_H
#define LEDS_H

class LEDSY
{
  public:
  LEDSY( int T1Rpin, int T1Gpin, int T1Bpin, int T2Rpin, int T2Gpin, int T2Bpin, int FREQ)
  : t1r(T1Rpin), t1g(T1Gpin), t1b(T1Bpin), t2r(T2Rpin), t2g(T2Gpin), t2b(T2Bpin), freq(FREQ) 
  {
      ledcAttachPin(t1r, 1); ledcAttachPin(t1g, 2); ledcAttachPin(t1b, 3);
      ledcAttachPin(t2r, 4); ledcAttachPin(t2g, 5); ledcAttachPin(t2b, 6);
      for (int i=1; i<7; i++)
      {
         ledcSetup(i, freq, 8); // kanal/freq/depth
         ledcWrite(i, 0);
      }
    };
    
  ~LEDSY(){};

  LEDSY& operator() (byte tape, byte h, byte s, byte v)
  {
    double  H, S, V, P, Q, T, RC,GC,BC, fract;
    H = 1.4117647058823529411764705882353*(double)h; // mapuj 0-360 -> 0-255
    S = 0.0039215686274509803921568627451*(double)s; //       0-1   -> 0-255
    V = 0.0039215686274509803921568627451*(double)v; //       0-1   -> 0-255

    (H == 360.)?(H = 0.):(H /= 60.);
    fract = H - floor(H);

    P = V*(1. - S);
    Q = V*(1. - S*fract);
    T = V*(1. - S*(1. - fract));

         if (0. <= H && H < 1.) { RC = V; GC = T; BC = P; } else if (1. <= H && H < 2.) { RC = Q; GC = V; BC = P; }
    else if (2. <= H && H < 3.) { RC = P; GC = V; BC = T; } else if (3. <= H && H < 4.) { RC = P; GC = Q; BC = V; }
    else if (4. <= H && H < 5.) { RC = T; GC = P; BC = V; } else if (5. <= H && H < 6.) { RC = V; GC = P; BC = Q; }
       else {RC = 0; GC = 0; BC = 0;}

    switch(tape)
    {
      case 0:
      { T1R = static_cast<byte>(round(RC*255)); T1G = static_cast<byte>(round(GC*255)); T1B = static_cast<byte>(round(BC*255));
      T1H = h; T1S = s; T1V = v; break; }
      case 1:
      { T2R = static_cast<byte>(round(RC*255)); T2G = static_cast<byte>(round(GC*255)); T2B = static_cast<byte>(round(BC*255));
      T2H = h; T2S = s; T2V = v; break; }
      default: return *this;
    }
    return *this;
  }
  
  void writeRGB(byte tape, byte r, byte g, byte b)
  {
    switch(tape)
    {
      case 0: { T1R = r; T1G = g; T1B = b; break; }
      case 1: { T2R = r; T2G = g; T2B = b; break; }
      default: return;
    }
  }
  
  void ledsHandler () // GLOWNY HANDLER, STOPNIOWA REGULACJA na podstawie RGB
  {
    // STRIP /1/
    if ((T1Rp!=T1R || T1Gp!=T1G || T1Bp!=T1B) && strip1del.del(cDEL)){
    if (T1Rp != T1R) // RED S1
    {      
        int delta = abs(T1Rp-T1R);
             if (delta>timD1)                 { if (T1Rp > T1R) {T1Rp-=tim1;} else {T1Rp+=tim1;} ledcWrite(1, T1Rp); }
        else if (delta<=timD1 && delta>timD2) { if (T1Rp > T1R) {T1Rp-=tim2;} else {T1Rp+=tim2;} ledcWrite(1, T1Rp); }
        else if (delta<=timD2 && delta>timD3) { if (T1Rp > T1R) {T1Rp-=tim3;} else {T1Rp+=tim3;} ledcWrite(1, T1Rp); }
        else if (delta<=timD3)                { if (T1Rp > T1R) {T1Rp-=tim4;} else {T1Rp+=tim4;} ledcWrite(1, T1Rp); }
    }
    if (T1Gp != T1G) // GREEN S1
    {      
        int delta = abs(T1Gp-T1G);
             if (delta>timD1)                 { if (T1Gp > T1G) {T1Gp-=tim1;} else {T1Gp+=tim1;} ledcWrite(2, T1Gp); }
        else if (delta<=timD1 && delta>timD2) { if (T1Gp > T1G) {T1Gp-=tim2;} else {T1Gp+=tim2;} ledcWrite(2, T1Gp); }
        else if (delta<=timD2 && delta>timD3) { if (T1Gp > T1G) {T1Gp-=tim3;} else {T1Gp+=tim3;} ledcWrite(2, T1Gp); }
        else if (delta<=timD3)                { if (T1Gp > T1G) {T1Gp-=tim4;} else {T1Gp+=tim4;} ledcWrite(2, T1Gp); }
    }
    if (T1Bp != T1B) // BLUE S1
    {      
        int delta = abs(T1Bp-T1B);
             if (delta>timD1)                 { if (T1Bp > T1B) {T1Bp-=tim1;} else {T1Bp+=tim1;} ledcWrite(3, T1Bp); }
        else if (delta<=timD1 && delta>timD2) { if (T1Bp > T1B) {T1Bp-=tim2;} else {T1Bp+=tim2;} ledcWrite(3, T1Bp); }
        else if (delta<=timD2 && delta>timD3) { if (T1Bp > T1B) {T1Bp-=tim3;} else {T1Bp+=tim3;} ledcWrite(3, T1Bp); }
        else if (delta<=timD3)                { if (T1Bp > T1B) {T1Bp-=tim4;} else {T1Bp+=tim4;} ledcWrite(3, T1Bp); }
    }
    }// ROZNICA S1

    // STRIP /2/
    if ((T2Rp!=T2R || T2Gp!=T2G || T2Bp!=T2B) && strip2del.del(cDEL)){
    if (T2Rp != T2R) // RED S2
    {      
        int delta = abs(T2Rp-T2R);
             if (delta>timD1)                 { if (T2Rp > T2R) {T2Rp-=tim1;} else {T2Rp+=tim1;} ledcWrite(4, T2Rp); }
        else if (delta<=timD1 && delta>timD2) { if (T2Rp > T2R) {T2Rp-=tim2;} else {T2Rp+=tim2;} ledcWrite(4, T2Rp); }
        else if (delta<=timD2 && delta>timD3) { if (T2Rp > T2R) {T2Rp-=tim3;} else {T2Rp+=tim3;} ledcWrite(4, T2Rp); }
        else if (delta<=timD3)                { if (T2Rp > T2R) {T2Rp-=tim4;} else {T2Rp+=tim4;} ledcWrite(4, T2Rp); }
    }
    if (T2Gp != T2G) // GREEN S2
    {      
        int delta = abs(T2Gp-T2G);
             if (delta>timD1)                 { if (T2Gp > T2G) {T2Gp-=tim1;} else {T2Gp+=tim1;} ledcWrite(5, T2Gp); }
        else if (delta<=timD1 && delta>timD2) { if (T2Gp > T2G) {T2Gp-=tim2;} else {T2Gp+=tim2;} ledcWrite(5, T2Gp); }
        else if (delta<=timD2 && delta>timD3) { if (T2Gp > T2G) {T2Gp-=tim3;} else {T2Gp+=tim3;} ledcWrite(5, T2Gp); }
        else if (delta<=timD3)                { if (T2Gp > T2G) {T2Gp-=tim4;} else {T2Gp+=tim4;} ledcWrite(5, T2Gp); }
    }
    if (T2Bp != T2B) // BLUE S2
    {      
        int delta = abs(T2Bp-T2B);
             if (delta>timD1)                 { if (T2Bp > T2B) {T2Bp-=tim1;} else {T2Bp+=tim1;} ledcWrite(6, T2Bp); }
        else if (delta<=timD1 && delta>timD2) { if (T2Bp > T2B) {T2Bp-=tim2;} else {T2Bp+=tim2;} ledcWrite(6, T2Bp); }
        else if (delta<=timD2 && delta>timD3) { if (T2Bp > T2B) {T2Bp-=tim3;} else {T2Bp+=tim3;} ledcWrite(6, T2Bp); }
        else if (delta<=timD3)                { if (T2Bp > T2B) {T2Bp-=tim4;} else {T2Bp+=tim4;} ledcWrite(6, T2Bp); }
    }
    }// ROZNICA S2
  }
  
  private:
  const int tim1{5},    tim2{3},   tim3{2},   tim4{1};    // Wartosci regulacji
  const int timD1{128}, timD2{64}, timD3{32};             // Przedzialy regulacji
  Kronos    strip1del, strip2del;                         // S1 i S2 kronosy
  const int cDEL{15};                                     // Opoznienie Kronosa
  int t1r, t1g, t1b, t2r, t2g, t2b;                       // PINY
  byte T1H, T1S, T1V, T2H, T2S, T2V;                      // NOWE  HSV
  byte T1Hp,T1Sp,T1Vp,T2Hp,T2Sp,T2Vp;                     // STARE HSV - chwilo bez znaczenia
  byte T1R{0}, T1G{0}, T1B{0}, T2R{0}, T2G{0}, T2B{0};    // NOWE  RGB
  byte T1Rp{0},T1Gp{0},T1Bp{0},T2Rp{0},T2Gp{0},T2Bp{0};   // STARE RGB
  int freq;
};

#endif
