#define EO_ESTAS        "000005"
#define EO_KVIN         "001204"
#define EO_DEK_M        "000803"
#define EO_MINUTOJ      "010107"
#define EO_KVARONO      "010807"
#define EO_DUDEK        "000605"
#define EO_DUONO        "020105"
#define EO_ANTAU        "020605"
#define EO_POST         "021104"
#define EO_NOKTOMEZO    "030009"
#define EO_TAGMEZO      "030907"
#define EO_LA           "040302"
#define EO_UNUA         "050504"
#define EO_DUA          "070603"
#define EO_TRIA         "041104"
#define EO_KVARA        "040605"
#define EO_KVINA        "060105"
#define EO_SESA         "070204"
#define EO_SEPA         "060904"
#define EO_OKA          "060603"
#define EO_NAUA         "051004"
#define EO_DEK_H        "050103"
#define EO_DEKA         "050104"
#define EO_HORO         "071004"

#define EO_MINUTE_1     "071501"
#define EO_MINUTE_2     "061501"
#define EO_MINUTE_3     "051501"
#define EO_MINUTE_4     "041501"

char EO_map[] = {
// 0123456789012345
  "ESTAS.DUDEK.KVIN"
  ".MINUTOJKVARONO."
  ".DUONOANTAuPOST."
  "NOKTOMEZOTAGMEZO"
  "...LA.KVARATRIA4"
  ".DEKAUNUA.NAuA.3"
  ".KVINAOKASEPA..2"
  "..SESADUA.HORO.1"
};

extern void setWord(const char *wrd);

void EO_time(int hour, int minute, int second) {

  setWord(EO_ESTAS);

  switch(minute % 5) {
    case 4: setWord("041501");
    case 3: setWord("051501");
    case 2: setWord("061501");
    case 1: setWord("071501");
    case 0: break;  
  }

  int minute5 = minute - minute % 5;  // 0, 5, 10, 15, ..
  int final_hour = hour;
  if (minute5 > 30) {  // use ANTAU next hour
    final_hour++;
    final_hour %= 24;
  }

  if (minute5 != 0) {
    setWord(minute5 <= 30 ? EO_POST : EO_ANTAU);
  }

  switch(minute5) {
    case 0:   break;   
    case 5:   setWord(EO_KVIN); 
              setWord(EO_MINUTOJ); break;
    case 10:  setWord(EO_DEK_M); 
              setWord(EO_MINUTOJ); break;
    case 15:  setWord(EO_KVARONO); break;
    case 20:  setWord(EO_DUDEK); 
              setWord(EO_MINUTOJ); break;
    case 25:  setWord(EO_DUDEK);
              setWord(EO_KVIN); 
              setWord(EO_MINUTOJ); break;
    case 30:  setWord(EO_DUONO); break;
    case 35:  setWord(EO_DUDEK);
              setWord(EO_KVIN); 
              setWord(EO_MINUTOJ); break;
    case 40:  setWord(EO_DUDEK);
              setWord(EO_MINUTOJ); break;
    case 45:  setWord(EO_KVARONO); break;
    case 50:  setWord(EO_DEK_M);  break;
    case 55:  setWord(EO_KVIN); break;
  }

  if (final_hour % 12 != 0) {
    setWord(EO_LA);
    if (minute5 == 0) setWord(EO_HORO);
  }

  switch (final_hour % 12) {
    case 0: setWord(final_hour == 0 ? EO_NOKTOMEZO : EO_TAGMEZO); break;
    case 1: setWord(EO_UNUA); break;
    case 2: setWord(EO_DUA); break;
    case 3: setWord(EO_TRIA); break;
    case 4: setWord(EO_KVARA); break;
    case 5: setWord(EO_KVINA); break;
    case 6: setWord(EO_SESA); break;
    case 7: setWord(EO_SEPA); break;
    case 8: setWord(EO_OKA); break;
    case 9: setWord(EO_NAUA); break;
    case 10: setWord(EO_DEKA); break;
    case 11: setWord(EO_DEK_H); 
             setWord(EO_UNUA); break;
  }
}