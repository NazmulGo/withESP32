//for display 128*32

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_ADDR 0x3C

#define START_DELAY_MS 3000   
#define OFFSET_MS 0          
#define ONE_WORD_MODE 1       

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

struct Word {
  unsigned long ms;   
  uint8_t line;       
  const char* text;
}; 

const Word words[] = {
  {   50, 0, "amar"},
  { 1320, 0, "rater"},
  { 2200, 0, "akashe"},
  { 3400, 0, "tumi"},
  { 4400, 0, "jeno"},
  { 5500, 0, "sondha"},
  { 6700, 0, "tara"},
  { 9470, 1, "provad"},
  {10090, 1, "himel"},
  {10900, 1, "batash"},
  {11760, 1, "e"},
  {11960, 1, "tumi"},
  {12910, 1, "jeno"},
  {13640, 1, "rojonigondha"},
  {15510, 1, "suvash"},
  {17400, 2, "amar"},
  {18580, 2, "e"},
  {19120, 2, "valobasha"},
  {20700, 2, "mane"},
  {21900, 2, "na"},
  {22260, 2, "je"},
  {23000, 2, "kono"},
  {24000, 2, "badha"},
  {26560, 3, "preyoshi"},
  {28180, 3, "tumi"},
  {29140, 3, "sob"},
  {29390, 3, "toko"},
  {30400, 3, "amar"},
};
const int WORD_COUNT = sizeof(words) / sizeof(words[0]);
const unsigned long END_MS = 33000;

String lineText = "";
int shownIndex = -1;
unsigned long songStart;

void drawBuilding() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setTextWrap(true);
  display.setCursor(0, 0);
  display.print(lineText);
  display.display();
}

void drawOneWord(const char* w) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextWrap(false);

  int len = strlen(w);

  if (len > 10) {
    int half = (len + 1) / 2;
    char a[16], b[16];
    strncpy(a, w, half); a[half] = 0;
    strcpy(b, w + half);
    display.setTextSize(2);
    display.setCursor((SCREEN_WIDTH - strlen(a) * 12) / 2, 0);
    display.print(a);
    display.setCursor((SCREEN_WIDTH - strlen(b) * 12) / 2, 16);
    display.print(b);
  } else {
    int size = 4;
    while (size > 1 && len * 6 * size > SCREEN_WIDTH) size--;
    int wpx = len * 6 * size - size;          // minus trailing letter gap
    display.setTextSize(size);
    display.setCursor((SCREEN_WIDTH - wpx) / 2, (SCREEN_HEIGHT - 8 * size) / 2);
    display.print(w);
  }
  display.display();
}

void message(const char* m) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 8);
  display.print(m);
  display.display();
}

void setup() {
  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    while (true) delay(1000);
  }

  for (int i = 3; i >= 1 && START_DELAY_MS >= 3000; i--) {
    char b[8]; sprintf(b, "%d", i);
    message(b);
    delay(START_DELAY_MS / 3);
  }
  message("GO");
  songStart = millis();
}

void loop() {
  long t = (long)(millis() - songStart) - OFFSET_MS;

  int idx = -1;
  for (int i = 0; i < WORD_COUNT; i++) {
    if (t >= (long)words[i].ms) idx = i;
  }

  if (idx != shownIndex && idx >= 0) {
    if (shownIndex < 0 || words[idx].line != words[shownIndex].line) lineText = "";
    if (lineText.length()) lineText += " ";
    lineText += words[idx].text;
    shownIndex = idx;

#if ONE_WORD_MODE
    drawOneWord(words[idx].text);
#else
    drawBuilding();
#endif
  }

  if (t > (long)END_MS) {
    display.clearDisplay();
    display.display();
    while (true) delay(1000);
  }
}
