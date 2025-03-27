#define ES_ES           "000002"
#define ES_SON          "000103"
#define ES_LA           "000502"
#define ES_LAS          "000503"
#define ES_CUATRO       "000906"

#define ES_TRES         "010004"
#define ES_SEIS         "010304"
#define ES_SIETE        "010605"
#define ES_NUEVE        "011105"

#define ES_DIEZ_H       "020004"
#define ES_CINCO_H      "020405"
#define ES_OCHO         "020804"
#define ES_ONCE         "021104"

#define ES_MEDIANOCHE   "030010"
#define ES_UNA          "031003"
#define ES_DOS          "031303"

#define ES_MEDIODIA     "040208"
#define ES_Y            "041101"

// #define ES_DOCE         "021204"

#define ES_MENOS        "050005"
#define ES_MEDIA        "050505"
#define ES_DIEZ_M       "051004"

#define ES_VEINTICINCO  "060211"
#define ES_CINCO_M      "060805"

#define ES_VEINTE       "070906"
#define ES_UN           "070002"
#define ES_CUARTO       "070306"

#define ES_MINUTE_1     "071501"
#define ES_MINUTE_2     "061501"
#define ES_MINUTE_3     "051501"
#define ES_MINUTE_4     "041501"


char ES_map[] = {
// 0123456789012345
  "ESON.LAS.CUATRO."
  "TRESEISIETENUEVE"
  "DIEZCINCOCHONCE."
  "MEDIANOCHEUNADOS"
  "..MEDIODIA.Y...4"
  "MENOSMEDIADIEZ.3"
  "..VEINTICINCO..2"
  "UN.CUARTOVEINTE1"
};


extern void setWord(const char *wrd);

void ES_time(int hour, int minute, int second) {

  switch(minute % 5) {
    case 4: setWord(ES_MINUTE_4);
    case 3: setWord(ES_MINUTE_3);
    case 2: setWord(ES_MINUTE_2);
    case 1: setWord(ES_MINUTE_1);
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
    case 5:   setWord(ES_Y); setWord(ES_CINCO_M); break;
    case 10:  setWord(ES_Y); setWord(ES_DIEZ_M); break;
    case 15:  setWord(ES_Y); setWord(ES_UN); setWord(ES_CUARTO); break;
    case 20:  setWord(ES_Y); setWord(ES_VEINTE); break;
    case 25:  setWord(ES_Y); setWord(ES_VEINTICINCO); break;
    case 30:  setWord(ES_Y); setWord(ES_MEDIA);break;
    case 35:  setWord(ES_MENOS); setWord(ES_VEINTICINCO); break;
    case 40:  setWord(ES_MENOS); setWord(ES_VEINTE); break;
    case 45:  setWord(ES_MENOS); setWord(ES_UN); setWord(ES_CUARTO); break;
    case 50:  setWord(ES_MENOS); setWord(ES_DIEZ_M); break;
    case 55:  setWord(ES_MENOS); setWord(ES_CINCO_M); break;
  }

  switch (final_hour % 12) {
    case 0: setWord(ES_ES); setWord(final_hour == 0 ? ES_MEDIANOCHE : ES_MEDIODIA); break;
    case 1: setWord(ES_ES); setWord(ES_LA); setWord(ES_UNA); break;
    case 2: setWord(ES_SON); setWord(ES_LAS); setWord(ES_DOS); break;
    case 3: setWord(ES_SON); setWord(ES_LAS); setWord(ES_TRES); break;
    case 4: setWord(ES_SON); setWord(ES_LAS); setWord(ES_CUATRO); break;
    case 5: setWord(ES_SON); setWord(ES_LAS); setWord(ES_CINCO_H); break;
    case 6: setWord(ES_SON); setWord(ES_LAS); setWord(ES_SEIS); break;
    case 7: setWord(ES_SON); setWord(ES_LAS); setWord(ES_SIETE); break;
    case 8: setWord(ES_SON); setWord(ES_LAS); setWord(ES_OCHO); break;
    case 9: setWord(ES_SON); setWord(ES_LAS); setWord(ES_NUEVE); break;
    case 10: setWord(ES_SON); setWord(ES_LAS);setWord(ES_DIEZ_H); break;
    case 11: setWord(ES_SON); setWord(ES_LAS);setWord(ES_ONCE); break;
  }
}


