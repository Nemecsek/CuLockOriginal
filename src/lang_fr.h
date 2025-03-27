#define FR_IL       "000002"
#define FR_EST      "000303"
#define FR_DIX_H    "000703"
#define FR_QUATRE   "001006"
#define FR_TROIS    "010005"
#define FR_UN       "010502"
#define FR_DEUX     "010704"
#define FR_MIDI     "011104"
#define FR_NEUF     "020004"
#define FR_CINQ_H   "020404"
#define FR_SEPT     "020804"
#define FR_HUIT     "021104"
#define FR_ONZE     "030004"
#define FR_SIX      "030403"
#define FR_MINUIT   "030706"
#define FR_HEURE    "040105"
#define FR_HEURES   "040106"
#define FR_MOINS    "040805"
#define FR_LE       "050002"
#define FR_ET       "050102"
#define FR_DEMIE    "050405"
#define FR_DIX_M    "051003"
#define FR_VINGT    "060005"
#define FR_CINQ_M   "060604"
#define FR_QUART    "060905"


char FR_map[] = {
// 0123456789012345
  "IL.EST.DIXQUATRE"
  "TROISUNDEUXMIDI."
  "NEUFCINQSEPTHUIT"
  "ONZESIXMINUIT..5"
  ".HEURES.MOINS..4"
  "LET.DEMIE.DIX..3"
  "VINGT.CINQUART.2"
  ".LE.TEMP.PASSE.1"
};


extern void setWord(const char *wrd);

void FR_time(int hour, int minute, int second) {

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

  setWord(FR_IL);
  setWord(FR_EST);

  switch (final_hour % 12) {
    case 0: setWord(final_hour == 0 ? FR_MINUIT : FR_MIDI); break;
    case 1: setWord(FR_UN); setWord(FR_HEURE); break;
    case 2: setWord(FR_DEUX); break;
    case 3: setWord(FR_TROIS); break;
    case 4: setWord(FR_QUATRE); break;
    case 5: setWord(FR_CINQ_H); break;
    case 6: setWord(FR_SIX); break;
    case 7: setWord(FR_SEPT); break;
    case 8: setWord(FR_HUIT); break;
    case 9: setWord(FR_NEUF); break;
    case 10: setWord(FR_DIX_H); break;
    case 11: setWord(FR_ONZE); break;
  }
  if (final_hour % 12 > 1) setWord(FR_HEURES);

  switch(minute5) {
    case 0:   break;   
    case 5:   setWord(FR_CINQ_M); break;
    case 10:  setWord(FR_DIX_M); break;
    case 15:  setWord(FR_ET); setWord(FR_QUART); break;
    case 20:  setWord(FR_VINGT); break;
    case 25:  setWord(FR_VINGT); setWord(FR_CINQ_M); break;
    case 30:  setWord(FR_ET); setWord(FR_DEMIE);break;
    case 35:  setWord(FR_MOINS); setWord(FR_VINGT); setWord(FR_CINQ_M); break;
    case 40:  setWord(FR_MOINS); setWord(FR_VINGT); break;
    case 45:  setWord(FR_MOINS); setWord(FR_LE); setWord(FR_QUART); break;
    case 50:  setWord(FR_MOINS); setWord(FR_DIX_M); break;
    case 55:  setWord(FR_MOINS); setWord(FR_CINQ_M); break;
  }
}
