#define IT_SONO         "000004"
#define IT_E_ACC        "000401"
#define IT_LE           "000502"
#define IT_L_UNA        "000705"
#define IT_NOVE         "001204"
#define IT_UNDICI       "010006"
#define IT_QUATTRO      "010607"
#define IT_DUE          "011303"
#define IT_CINQUE_H     "020006"
#define IT_SETTE        "020605"
#define IT_DIECI_H      "021105"
#define IT_MEZZOGIORNO  "030011"
#define IT_OTTO         "031004"
#define IT_MEZZANOTTE   "040010"
#define IT_SEI          "041003"
#define IT_TRE          "050003"
#define IT_E            "050601"
#define IT_MENO         "050504"
#define IT_DIECI_M      "051005"
#define IT_UN           "060002"
#define IT_QUARTO       "060306"
#define IT_MEZZA        "060905"
#define IT_VENTI        "070005"
#define IT_CINQUE_M     "070506"

char IT_map[] = {
// 0123456789012345
  "SONOeLEL'UNANOVE"
  "UNDICIQUATTRODUE"
  "CINQUESETTEDIECI"
  "MEZZOGIORNOTTO.5"
  "MEZZANOTTESEI..4"
  "TRE..MENO.DIECI3"
  "UN.QUARTOMEZZA.2"
  "VENTICINQUE...A1"
};


extern void setWord(const char *wrd);

void IT_time(int hour, int minute, int second) {

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

  switch(minute5) {
    case 0:   break;   
    case 5:   setWord(IT_E); setWord(IT_CINQUE_M); break;
    case 10:  setWord(IT_E); setWord(IT_DIECI_M); break;
    case 15:  setWord(IT_E); setWord(IT_UN); setWord(IT_QUARTO); break;
    case 20:  setWord(IT_E); setWord(IT_VENTI); break;
    case 25:  setWord(IT_E); setWord(IT_VENTI); setWord(IT_CINQUE_M); break;
    case 30:  setWord(IT_E); setWord(IT_MEZZA);break;
    case 35:  setWord(IT_MENO); setWord(IT_VENTI); setWord(IT_CINQUE_M); break;
    case 40:  setWord(IT_MENO); setWord(IT_VENTI); break;
    case 45:  setWord(IT_MENO); setWord(IT_UN); setWord(IT_QUARTO); break;
    case 50:  setWord(IT_MENO); setWord(IT_DIECI_M); break;
    case 55:  setWord(IT_MENO); setWord(IT_CINQUE_M); break;
  }

  switch (final_hour % 12) {
    case 0: setWord(IT_E_ACC); setWord(final_hour == 0 ? IT_MEZZANOTTE : IT_MEZZOGIORNO); break;
    case 1: setWord(IT_E_ACC); setWord(IT_L_UNA); break;
    case 2: setWord(IT_SONO); setWord(IT_LE); setWord(IT_DUE); break;
    case 3: setWord(IT_SONO); setWord(IT_LE); setWord(IT_TRE); break;
    case 4: setWord(IT_SONO); setWord(IT_LE); setWord(IT_QUATTRO); break;
    case 5: setWord(IT_SONO); setWord(IT_LE); setWord(IT_CINQUE_H); break;
    case 6: setWord(IT_SONO); setWord(IT_LE); setWord(IT_SEI); break;
    case 7: setWord(IT_SONO); setWord(IT_LE); setWord(IT_SETTE); break;
    case 8: setWord(IT_SONO); setWord(IT_LE); setWord(IT_OTTO); break;
    case 9: setWord(IT_SONO); setWord(IT_LE); setWord(IT_NOVE); break;
    case 10: setWord(IT_SONO); setWord(IT_LE);setWord(IT_DIECI_H); break;
    case 11: setWord(IT_SONO); setWord(IT_LE);setWord(IT_UNDICI); break;
  }
}


