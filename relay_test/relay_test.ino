//リレーテスト
#include <M5Stack.h>

#define RELAY_PIN 26       //リレーピン設定

//ログ表示機能
#define MAX_LINES 11
String lines[MAX_LINES];
int currentLine = 0;
const int lineHeight = 20;  // 1行の高さ

void printText(String text) {
  // 古い行を1つ削除する
  if (currentLine == MAX_LINES) {
    for (int i = 0; i < MAX_LINES - 1; i++) {
      lines[i] = lines[i + 1];
    }
    lines[MAX_LINES - 1] = text;
  } else {
    lines[currentLine++] = text;
  }

  // 画面をクリアして、全行を再描画
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);

  // 各行を描画
  int y = 10;
  for (int i = 0; i < currentLine; i++) {
    M5.Lcd.setCursor(10, y);
    M5.Lcd.print(lines[i]);
    y += lineHeight;
  }
}

void setup() {
  M5.begin();
  M5.Power.begin(); 
  dacWrite(25, 0);  // disable the speak noise.
  pinMode(RELAY_PIN, OUTPUT);

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  printText("Goat Watering System");

}

void fill(bool full){
  digitalWrite(RELAY_PIN, HIGH);//ソレノイドバルブ リレーON
  printText("Water filling");

  //水が溜まるまで待機
  if(full){//フル注水
    delay(1000); 
  }else{//リンス用注水
    delay(1000);
  }

  digitalWrite(RELAY_PIN, LOW);//ソレノイドバルブ リレーOFF
  printText("Water stopped");
}

void loop() {
fill(true);
delay(5000);
}
