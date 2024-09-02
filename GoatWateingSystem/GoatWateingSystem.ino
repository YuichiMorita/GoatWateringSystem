//ヤギ給水システム
#include <M5Stack.h>
#include "Unit_RTC.h"     //RTC

#define RELAY_PIN 26       //リレーピン設定

//RTC
Unit_RTC RTC;
rtc_time_type RTCtime;
rtc_date_type RTCdate;
char str_buffer[64];

bool working; //稼働中かどうか

//初期化
void setup() {
  M5.begin();
  M5.Power.begin();
  dacWrite(25, 0);  // disable the speak noise.
  pinMode(RELAY_PIN, OUTPUT);
  RTC.begin();

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("Goat Watering System");

  //初回のみ使用の時計合わせコード
  /*
  RTCtime.Hours   = 16;
  RTCtime.Minutes = 55;
  RTCtime.Seconds = 0;
  RTCdate.WeekDay = 4; //これいる？
  RTCdate.Month   = 8;
  RTCdate.Date    = 15;
  RTCdate.Year    = 2024;
  RTC.setTime(&RTCtime);
  RTC.setDate(&RTCdate);
  */

  delay(100);
  digitalWrite(RELAY_PIN, LOW);//ソレノイドバルブ リレーOFF
  working = false;
}

//注水
void fill(int time){
  working = true;//稼働中フラグON
  digitalWrite(RELAY_PIN, HIGH);//ソレノイドバルブ リレーON
  delay(time);  //水が溜まるまで待機
  digitalWrite(RELAY_PIN, LOW);//ソレノイドバルブ リレーOFF
  working = false;//稼働中フラグOFF
}

//メインループ
void loop() {
  M5.update();
  RTC.getTime(&RTCtime);//時間所得
  M5.Lcd.fillRect(0, 30, 320, 30, TFT_BLACK);
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.printf("%02d:%02d:%02d\n", RTCtime.Hours,RTCtime.Minutes, RTCtime.Seconds);

  //朝8時の水やり
  if(RTCtime.Hours == 8 && RTCtime.Minutes == 0 && RTCtime.Seconds >= 0 && RTCtime.Seconds <= 1 && working== false){
    M5.Lcd.setCursor(0, 30);
    M5.Lcd.fillRect(0, 30, 320, 30, TFT_BLACK);
    M5.Lcd.println("It's 8 o'clock! Let's work!");
    fill(60000); //60秒
  }

  //午後15時の水やり
  if(RTCtime.Hours == 15 && RTCtime.Minutes == 0 && RTCtime.Seconds >= 0 && RTCtime.Seconds <= 1 && working== false){
    M5.Lcd.setCursor(0, 30);
    M5.Lcd.fillRect(0, 30, 320, 30, TFT_BLACK);
    M5.Lcd.println("It's 15 o'clock! Let's work!");
    fill(60000); //60秒
  }

  if(M5.BtnA.wasReleased()){
  //ボタン”A”が押された時の動作
    M5.Lcd.setCursor(0, 60);
    M5.Lcd.fillRect(0, 60, 320, 30, TFT_BLACK);

    M5.Lcd.println("A BTN:fill 60sec");
    fill(60000); //60秒
    M5.Lcd.fillRect(0, 60, 320, 30, TFT_BLACK);

  } else if(M5.BtnB.wasReleased()){
    //ボタン”B”が押された時の動作
    M5.Lcd.setCursor(0, 60);
    M5.Lcd.fillRect(0, 60, 320, 30, TFT_BLACK);

    M5.Lcd.println("B BTN:Water stop");
    digitalWrite(RELAY_PIN, LOW);//ソレノイドバルブ リレーOFF
    working = false;//稼働中フラグOFF
    delay(2000);
    M5.Lcd.fillRect(0, 60, 320, 30, TFT_BLACK);

  }else if(M5.BtnC.wasReleased()){
    //ボタン”C”が押された時の動作
    M5.Lcd.fillRect(0, 60, 320, 30, TFT_BLACK);
    M5.Lcd.setCursor(0, 60);
    M5.Lcd.println("C BTN:Water out");
    digitalWrite(RELAY_PIN, HIGH);//ソレノイドバルブ リレーON
    working = true;//稼働中フラグON
  }
  delay(300);
}
