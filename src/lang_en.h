#define EN_IT_S     "000004"
#define EN_TWENTY   "000506"
#define EN_FIVE_M   "001104"
#define EN_QUARTER  "010207"
#define EN_TEN_M    "010903"
#define EN_HALF     "011204"
#define EN_PAST     "020004"
#define EN_TO       "020302"
#define EN_ELEVEN   "020606"
#define EN_FOUR     "021204"
#define EN_NOON     "030004"
#define EN_ONE      "030203"
#define EN_EIGHT    "030405"
#define EN_SEVEN    "030905"
#define EN_MIDNIGHT "040008"
#define EN_TWO      "040703"
#define EN_THREE    "041005"
#define EN_FIVE_H   "050004"
#define EN_SIX      "050403"
#define EN_TEN_H    "050703"
#define EN_NINE     "050904"
#define EN_AM       "060202"
#define EN_PM       "060402"
#define EN_O_CLOCK  "060707"
// #define EN_TEMPUS_FUGIT "070212"

char EN_map[] = {
// 0123456789012345
  "IT'S.TWENTYFIVE."
  "A.QUARTERTENHALF"
  "PASTO.ELEVENFOUR"
  "NOONEIGHTSEVEN.5"
  "MIDNIGHTWOTHREE4"
  "FIVESIXTENINE..3"
  "..AMPM.O'CLOCK.2"
  "..TEMPUS.FUGITA1"
};


extern void setWord(const char *wrd);

void EN_time(int hour, int minute, int second) {

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

  setWord(EN_IT_S);

  switch(minute5) {
    case 0:   if (final_hour % 12 != 0) setWord(EN_O_CLOCK); break;   
    case 5:   setWord(EN_PAST); setWord(EN_FIVE_M); break;
    case 10:  setWord(EN_PAST); setWord(EN_TEN_M); break;
    case 15:  setWord(EN_PAST); setWord(EN_QUARTER); break;
    case 20:  setWord(EN_PAST); setWord(EN_TWENTY); break;
    case 25:  setWord(EN_PAST); setWord(EN_TWENTY); setWord(EN_FIVE_M); break;
    case 30:  setWord(EN_PAST); setWord(EN_HALF);break;
    case 35:  setWord(EN_TO); setWord(EN_TWENTY); setWord(EN_FIVE_M); break;
    case 40:  setWord(EN_TO); setWord(EN_TWENTY); break;
    case 45:  setWord(EN_TO); setWord(EN_QUARTER); break;
    case 50:  setWord(EN_TO); setWord(EN_TEN_M); break;
    case 55:  setWord(EN_TO); setWord(EN_FIVE_M); break;
  }

  switch (final_hour % 12) {
    case 0: setWord(final_hour == 0 ? EN_MIDNIGHT : EN_NOON); break;
    case 1: setWord(EN_ONE); break;
    case 2: setWord(EN_TWO); break;
    case 3: setWord(EN_THREE); break;
    case 4: setWord(EN_FOUR); break;
    case 5: setWord(EN_FIVE_H); break;
    case 6: setWord(EN_SIX); break;
    case 7: setWord(EN_SEVEN); break;
    case 8: setWord(EN_EIGHT); break;
    case 9: setWord(EN_NINE); break;
    case 10: setWord(EN_TEN_H); break;
    case 11: setWord(EN_ELEVEN); break;
  }

  if (final_hour % 12 != 0) {
    // setWord(final_hour < 12 ? EN_AM : EN_PM );
  }
}


