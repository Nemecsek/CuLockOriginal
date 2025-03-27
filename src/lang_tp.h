extern void setWord(const char *wrd);

#define TP_TENPO   "000005"
#define TP_H_LI    "000602"
#define TP_PIMEJA  "000806"
#define TP_SUNO    "010004"
#define TP_SEWI    "010504"
#define TP_KAMA    "010904"
#define TP_ALA     "011203"
#define TP_LAPE    "020204"

#define TP_H_MUTE  "020704"
#define TP_H_LUKA1 "021204"
#define TP_H_LUKA2 "030004"
#define TP_H_LUKA3 "030504"
#define TP_H_TU1   "031002"
#define TP_H_TU2   "031302"
#define TP_H_WAN   "040003"

#define TP_TOKI    "040404"
#define TP_PONA    "040904"

#define TP_M_LI    "050002"
#define TP_M_MUTE1 "050304"
#define TP_M_MUTE2 "050804"
#define TP_M_LUKA1 "060004"
#define TP_M_LUKA2 "060504"
#define TP_M_LUKA3 "061004"
#define TP_M_TU1   "070002"
#define TP_M_TU2   "070302"
#define TP_M_WAN   "070603"

char TP_map[] = {
// 0123456789012345
  "TENPO.LIPIMEJA.."  // 0 TENPO H_LI PIMEJA
  "SUNO.SEWIKAMALA."  // 1 SUNO SEWI KAMA ALA  
  "..LAPE.MUTE.LUKA"  // 2 LAPE H_MUTE H_LUKA1
  "LUKA.LUKA.TU.TU5"  // 3 H_LUKA2 H_LUKA3 H_TU1 H_TU2
  "WAN.TOKI.PONA..4"  // 4 H_WAN TOKI PONA
  "LI.MUTE.MUTE...3"  // 5 M_LI M_MUTE1 M_MUTE2
  "LUKA.LUKA.LUKA.2"  // 6 M_LUKA1 M_LUKA2 M_LUKA3
  "TU.TU.WAN......1"  // 7 M_TU1 M_TU2 M_WAN
};


void TP_time(int hour, int minute, int second) {

  // hours
  switch(hour) {
    case  0: setWord(TP_TENPO); setWord(TP_PIMEJA); break;
    case  1: setWord(TP_TENPO); setWord(TP_H_LI);  setWord(TP_H_WAN); break;
    case  3: setWord(TP_TENPO); setWord(TP_H_LI);  setWord(TP_H_TU1); break;
    case  4: setWord(TP_TENPO); setWord(TP_H_LI);  setWord(TP_H_TU1); setWord(TP_H_TU2); break;
    case  5: setWord(TP_TENPO); setWord(TP_H_LI);  setWord(TP_H_LUKA1); break;
    case  6: setWord(TP_SUNO); setWord(TP_KAMA); break;
    case  7: setWord(TP_TENPO); setWord(TP_H_LI);  setWord(TP_H_LUKA1); setWord(TP_H_TU1); break;
    case  8: setWord(TP_TENPO); setWord(TP_H_LI);  setWord(TP_H_LUKA1); setWord(TP_H_TU1); setWord(TP_H_WAN); break;
    case  9: setWord(TP_TENPO); setWord(TP_H_LI);  setWord(TP_H_LUKA1); setWord(TP_H_TU1); setWord(TP_H_TU2); break;
    case 10: setWord(TP_TENPO); setWord(TP_H_LI);  setWord(TP_H_LUKA1); setWord(TP_H_LUKA2); break;
    case 11: setWord(TP_TENPO); setWord(TP_H_LI);  setWord(TP_H_LUKA1); setWord(TP_H_LUKA2); setWord(TP_H_WAN); break;
    case 12: setWord(TP_SUNO); setWord(TP_SEWI); break;
    case 13: setWord(TP_TENPO); setWord(TP_H_LI);  setWord(TP_H_LUKA1); setWord(TP_H_LUKA2); setWord(TP_H_TU1); setWord(TP_H_WAN); break;
    case 14: setWord(TP_TENPO); setWord(TP_H_LI);  setWord(TP_H_LUKA1); setWord(TP_H_LUKA2); setWord(TP_H_TU1); setWord(TP_H_TU2); break;
    case 15: setWord(TP_TENPO); setWord(TP_H_LI);  setWord(TP_H_LUKA1); setWord(TP_H_LUKA2); setWord(TP_H_LUKA3); break;
    case 16: setWord(TP_TENPO); setWord(TP_H_LI);  setWord(TP_H_LUKA1); setWord(TP_H_LUKA2); setWord(TP_H_LUKA3); setWord(TP_H_WAN); break;
    case 17: setWord(TP_TENPO); setWord(TP_H_LI);  setWord(TP_H_LUKA1); setWord(TP_H_LUKA2); setWord(TP_H_LUKA3); setWord(TP_H_TU1); break;
    case 18: setWord(TP_SUNO); setWord(TP_LAPE); break;
    case 19: setWord(TP_TENPO); setWord(TP_H_LI);  setWord(TP_H_LUKA1); setWord(TP_H_LUKA2); setWord(TP_H_LUKA3); setWord(TP_H_TU1); setWord(TP_H_TU2); break;
    case 20: setWord(TP_TENPO); setWord(TP_H_LI);  setWord(TP_H_MUTE); break;
    case 21: setWord(TP_TENPO); setWord(TP_H_LI);  setWord(TP_H_MUTE); setWord(TP_H_WAN); break;
    case 22: setWord(TP_TENPO); setWord(TP_H_LI);  setWord(TP_H_MUTE); setWord(TP_H_TU1); break;
    case 23: setWord(TP_TENPO); setWord(TP_H_LI);  setWord(TP_H_MUTE); setWord(TP_H_TU1); setWord(TP_H_WAN); break;
  }

  // minutes
  int minute5 = minute - minute%5;

  if (minute > 0) {
    setWord(TP_M_LI);
  }

  switch (minute5) {
    case  0: break;
    case  5: setWord(TP_M_LUKA1); break;
    case 10: setWord(TP_M_LUKA1); setWord(TP_M_LUKA2); break;
    case 15: setWord(TP_M_LUKA1); setWord(TP_M_LUKA2); setWord(TP_M_LUKA3); break;
    case 20: setWord(TP_M_MUTE1); break;
    case 25: setWord(TP_M_MUTE1); setWord(TP_M_LUKA1); break;
    case 30: setWord(TP_M_MUTE1); setWord(TP_M_LUKA1); setWord(TP_M_LUKA2); break;
    case 35: setWord(TP_M_MUTE1); setWord(TP_M_LUKA1); setWord(TP_M_LUKA2); setWord(TP_M_LUKA3); break;
    case 40: setWord(TP_M_MUTE1); setWord(TP_M_MUTE2); break;
    case 45: setWord(TP_M_MUTE1); setWord(TP_M_MUTE2); setWord(TP_M_LUKA1); break;
    case 50: setWord(TP_M_MUTE1); setWord(TP_M_MUTE2); setWord(TP_M_LUKA1); setWord(TP_M_LUKA2); break;
    case 55: setWord(TP_M_MUTE1); setWord(TP_M_MUTE2); setWord(TP_M_LUKA1); setWord(TP_M_LUKA2); setWord(TP_M_LUKA3); break;
  }

  switch (minute%5) {
    case 0: break;
    case 1: setWord(TP_M_WAN); break;
    case 2: setWord(TP_M_TU1); break;
    case 3: setWord(TP_M_TU1); setWord(TP_M_WAN); break;
    case 4: setWord(TP_M_TU1); setWord(TP_M_TU2); break;
  }
}
