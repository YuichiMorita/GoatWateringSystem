#include <M5Stack.h>
#include "Unit_RTC.h"     //RTC

//RTC
Unit_RTC RTC;
rtc_time_type RTCtime;
rtc_date_type RTCdate;
char str_buffer[64];

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
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);

  printText("RTC test");
  RTC.begin();

  //初回のみ使用の時計合わせコード
/*
  RTCtime.Hours   = 14;
  RTCtime.Minutes = 56;
  RTCtime.Seconds = 0;
  RTCdate.WeekDay = 4; //これいる？
  RTCdate.Month   = 8;
  RTCdate.Date    = 15;
  RTCdate.Year    = 2024;
  RTC.setTime(&RTCtime);
  RTC.setDate(&RTCdate);
*/
}

void loop() {
    M5.Lcd.fillRect(0, 20, 320, 140, BLACK);
    RTC.getTime(&RTCtime);  // To get the time.  获取时间
    RTC.getDate(&RTCdate);  // Get the date.  获取日期
    M5.Lcd.setCursor(0, 20);
    M5.Lcd.printf("RTC Time Now is \n%02d:%02d:%02d\n", RTCtime.Hours,
                  RTCtime.Minutes, RTCtime.Seconds);
    M5.Lcd.printf("RTC Date Now is \n%02d:%02d:%02d WeekDay:%02d\n",
                  RTCdate.Year, RTCdate.Month, RTCdate.Date, RTCdate.WeekDay);
    delay(1000);

}
