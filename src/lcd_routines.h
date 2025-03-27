void updateSingleChar(int px, int py, char ch, bool light) {

    // special chars defined in the language maps:
    // a=Ä, o=Ö, u=Ü, s=ß  for German
    // e=È for Italian
    // *=full circle
    // all unknown chars are printed as space

    int index;
    if ((ch >= 'A') && (ch <= 'Z')) index=ch-65;
    else if (ch == '.') index = (px+py)%26;  // fills pseudo randomly . chars
    else if ((ch >= '1') && (ch <= '5')) index = 29; // circle
    else if (ch == 'a') index = 26; // Ä
    else if (ch == 'o') index = 27; // Ö
    else if (ch == 'u') index = 28; // Ü
    else if (ch == '*') index = 29; // circle
    else if (ch == 'e') index = 30;  // È
    else if (ch == '\'') index = 31; // '
    else return; // any other char is rendered as space

    int alphabet_pointer = HCHAR * WCHAR * index;  // saved in true color (4 bytes)

    // absolute pos onscreen
    px *= WCHAR;
    px += 16;
    py *= HCHAR;
    py += 20;

    for (int y=0; y<HCHAR-1; y++) {
        for (int x=0; x<WCHAR; x++) {
            int col = alphabet2_map[alphabet_pointer];
            int colR = col/div_gray;
            int colG = col/div_gray;
            int colB = col/div_gray;
            if (light) {
                colR = col/divR;
                colG = col/divG;
                colB = col/divB;
            }
            lcd_buff.drawPixel(px+x, py+y, lcd.color888(colR, colG, colB));
            alphabet_pointer++;
        }
    }
}


void setWord(const char *wrd) {  
    // set 1 each char of a word
    int py=(wrd[0]-48)*10+wrd[1]-48;
    int px=(wrd[2]-48)*10+wrd[3]-48;
    int len_=(wrd[4]-48)*10+wrd[5]-48;
    int offset=py*NUM_COLS+px;
    for (int i=0; i<len_; i++) {
        current_light_status[offset+i] = 1;
    }
    map_changed = true;  // need a refresh!
}

void updateChangedChars() {
    char *map;
    switch(language) {
        case 1: map = IT_map; break;
        case 2: map = VE_map; break;
        case 3: map = DE_map; break;
        case 4: map = ES_map; break;
        case 5: map = FR_map; break;
        case 6: map = TP_map; break;
        case 7: map = EO_map; break;
        default: map = EN_map; 
    }
    for (int i=0; i<NUM_ROWS*NUM_COLS; i++) {
        if (current_light_status[i] != previous_light_status[i]) {  // only changed chars are updated
        updateSingleChar(i%NUM_COLS, i/NUM_COLS, map[i], current_light_status[i]);
        previous_light_status[i] = current_light_status[i];
        }
    }

} 

void force_complete_redraw() {
    for (int i=0; i<NUM_COLS*NUM_ROWS; i++) {
        previous_light_status[i] = 2;  
    }
    map_changed = true;
}

void clear_map(void) {
    // clear current char map
    for (int i=0; i<NUM_ROWS*NUM_COLS; i++) {
        current_light_status[i] = 0;  
    }
}

void drawTestPoints() {
    lcd_buff.setColor(0xffffffu);
    lcd_buff.drawPixel(  8, 12, 2);
    lcd_buff.drawPixel(  8,307, 3);
    lcd_buff.drawPixel(471, 12, 4);
    lcd_buff.drawPixel(471,307, 5);
}
