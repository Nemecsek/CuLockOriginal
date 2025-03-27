
extern void setWord(const char *wrd);

                  //  y x text_lenght  
#define DE_ES          "000002"
#define DE_IST         "000303"
#define DE_UHR         "071103"
#define DE_FUNF_M      "010104"
#define DE_ZEHN_M      "010504"
#define DE_FUNFZEHN    "010108"  
#define DE_VIERTEL     "010907"
#define DE_VOR         "020103"
#define DE_NACH        "020404"
#define DE_HALB        "021004"
#define DE_VIER        "061104"
#define DE_EIN         "051003"
#define DE_EINS        "051004"
#define DE_ZWEI        "030004"
#define DE_ZWOLF       "030405"
#define DE_ZEHN_H      "030904"
#define DE_ELF         "040003"
#define DE_NEUN        "040304"
#define DE_FUNF_H      "040704"
#define DE_DREI        "041104"
#define DE_SECHS       "050005"
#define DE_SIEBEN      "050406"
#define DE_ACHT        "060704"
#define DE_MITTERNACHT "060011"
#define DE_MITTAG      "070006"
#define DE_TEMPUS      "000506"    
#define DE_FUGIT       "070605"
#define DE_EIN_V       "001103"  // EIN viertel

char DE_map[] = {
// 0123456789012345
  "ES.ISTEMPUSEIN.."
  ".FuNFZEHNVIERTEL"
  ".VORNACHTSHALB.."
  "ZWEIZWoLFZEHN..5"
  "ELFNEUNFuNFDREI4"
  "SECHSIEBENEINS.3"
  "MITTERNACHTVIER2"
  "MITTAGFUGITUHRA1"
};

void DE_time(int hour, int minute, int second) {

  setWord(DE_ES);
  setWord(DE_IST);

  switch(minute % 5) {
    case 4: setWord("041501");
    case 3: setWord("051501");
    case 2: setWord("061501");
    case 1: setWord("071501");
    case 0: break;  
  }

  int minute5 = minute - minute % 5;  // 0, 5, 10, 15, ..
  int final_hour = hour;
  if (minute5 > 15) {
    final_hour++;
    final_hour %= 24;
  }

  bool used_halb = false;
  bool mitternacht_mittag = false;

  switch(minute5) {
    case 0:   break;   
    case 5:   setWord(DE_FUNF_M); 
              setWord(DE_NACH); break;
    case 10:  setWord(DE_ZEHN_M); 
              setWord(DE_NACH); break;
    case 15:  setWord(DE_EIN_V); 
              setWord(DE_VIERTEL);
              setWord(DE_NACH); break;
    case 20:  setWord(DE_ZEHN_M); 
              setWord(DE_VOR); 
              setWord(DE_HALB); 
              used_halb = true;
              break;
    case 25:  setWord(DE_FUNF_M); 
              setWord(DE_VOR); 
              setWord(DE_HALB); 
              used_halb = true;
              break;
    case 30:  setWord(DE_HALB); 
              used_halb = true;
              break;
    case 35:  setWord(DE_FUNF_M); 
              setWord(DE_NACH); 
              setWord(DE_HALB); 
              used_halb = true;
              break;
    case 40:  setWord(DE_ZEHN_M); 
              setWord(DE_NACH); 
              setWord(DE_HALB); 
              used_halb = true;
              break;
    case 45:  setWord(DE_EIN_V); 
              setWord(DE_VIERTEL);
              setWord(DE_VOR); break;
    case 50:  setWord(DE_ZEHN_M); 
              setWord(DE_VOR); break;
    case 55:  setWord(DE_FUNF_M); 
              setWord(DE_VOR); break;
  }

  switch (final_hour % 12) {
    case 0: if (used_halb) setWord(DE_ZWOLF); 
            else if (final_hour == 0) {
              setWord(DE_MITTERNACHT);
              mitternacht_mittag = true;
            }
            else {
              setWord(DE_MITTAG);
              mitternacht_mittag = true;
            }
            break;
    case 1: setWord(minute5 == 0 ? DE_EIN : DE_EINS); break;
    case 2: setWord(DE_ZWEI); break;
    case 3: setWord(DE_DREI); break;
    case 4: setWord(DE_VIER); break;
    case 5: setWord(DE_FUNF_H); break;
    case 6: setWord(DE_SECHS); break;
    case 7: setWord(DE_SIEBEN); break;
    case 8: setWord(DE_ACHT); break;
    case 9: setWord(DE_NEUN); break;
    case 10: setWord(DE_ZEHN_H); break;
    case 11: setWord(DE_ELF); break;
  }

  // DE_HOUR
  if ((minute5 == 0) && !mitternacht_mittag) {
    setWord(DE_UHR);
  }
}
