#define VE_XE       "000002"
#define VE_LE       "000302"
#define VE_UN_H     "000602"
#define VE_BOTO     "001204"
#define VE_OTO      "001303"
#define VE_UNDEZE   "000606"
#define VE_MEZOGIORNO "010010"
#define VE_QUATRO   "011006"
#define VE_DIEZE_H  "020005"
#define VE_TRE      "020503"
#define VE_DO       "020802"
#define VE_SINQUE_H "021006"
#define VE_MEZANOTE "030008"
#define VE_SIE      "030803"
#define VE_SETE     "031104"
#define VE_NOVE     "040004"
#define VE_E        "040501"
#define VE_MANCA    "040605"
#define VE_MEZA     "041104"
#define VE_UN_M     "050102"
#define VE_DIEZE_M  "050305"
#define VE_QUARTO   "050806"
#define VE_VINTI    "060005"
#define VE_SINQUE_M "060506"

// #define VE_ALEX     "061104"
// #define VE_EL       "070002"
// #define VE_TEMPO    "070305"
// #define VE_CORE     "070904"

char VE_map[] = {   
// 0123456789012345
  "XE.LE.UNDESEBOTO"
  "MEZOGIORNOQUATRO"
  "DIESETREDOSINQUE"
  "MEZANOTESIESETE5"
  "NOVE.EMANCAMEZA4"
  ".UNDIESEQUARTO.3"
  "VINTISINQUEALEX2"
  "EL.TEMPO.CORE.A1"
};

extern void setWord(const char *wrd);

void VE_time(int hour, int minute, int second) {

  switch(minute % 5) {
    case 4: setWord("041501");
    case 3: setWord("051501");
    case 2: setWord("061501");
    case 1: setWord("071501");
    case 0: break;  
  }

  int minute5 = minute - minute % 5;  // 0, 5, 10, 15, ..
  int final_hour = hour;
  if (minute5 > 30) {
    final_hour++;
    final_hour %= 24;
  }

  setWord(VE_XE);

  switch(minute5) {
    case 0:   break;   
    case 5:   setWord(VE_E); setWord(VE_SINQUE_M); break;
    case 10:  setWord(VE_E); setWord(VE_DIEZE_M); break;
    case 15:  setWord(VE_E); setWord(VE_UN_M); setWord(VE_QUARTO); break;
    case 20:  setWord(VE_E); setWord(VE_VINTI); break;
    case 25:  setWord(VE_E); setWord(VE_VINTI); setWord(VE_SINQUE_M); break;
    case 30:  setWord(VE_E); setWord(VE_MEZA);break;
    case 35:  setWord(VE_MANCA); setWord(VE_VINTI); setWord(VE_SINQUE_M); break;
    case 40:  setWord(VE_MANCA); setWord(VE_VINTI); break;
    case 45:  setWord(VE_MANCA); setWord(VE_UN_M); setWord(VE_QUARTO); break;
    case 50:  setWord(VE_MANCA); setWord(VE_DIEZE_M); break;
    case 55:  setWord(VE_MANCA); setWord(VE_SINQUE_M); break;
  }

  switch (final_hour % 12) {
    case 0: setWord(final_hour == 0 ? VE_MEZANOTE : VE_MEZOGIORNO); break;
    case 1: setWord(VE_UN_H); setWord(VE_BOTO); break;
    case 2: setWord(VE_LE); setWord(VE_DO); break;
    case 3: setWord(VE_LE); setWord(VE_TRE); break;
    case 4: setWord(VE_LE); setWord(VE_QUATRO); break;
    case 5: setWord(VE_LE); setWord(VE_SINQUE_H); break;
    case 6: setWord(VE_LE); setWord(VE_SIE); break;
    case 7: setWord(VE_LE); setWord(VE_SETE); break;
    case 8: setWord(VE_LE); setWord(VE_OTO); break;
    case 9: setWord(VE_LE); setWord(VE_NOVE); break;
    case 10: setWord(VE_LE);setWord(VE_DIEZE_H); break;
    case 11: setWord(VE_LE);setWord(VE_UNDEZE); break;
  }
}

