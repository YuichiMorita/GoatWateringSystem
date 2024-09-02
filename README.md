# やぎ自動給水システム

やぎに自動で水をあげる。タイマー制御で8時と15時に水をバケツに満たす。
これで旅行中も万全。  

## 構成
- M5Core
- Base M5GO BOTTOM
- リレー
- ソレノイドバルブ
- RTC

## 開発環境
- Arduino IDE
- 守田裕一(info@reju.jp)

## ボタン
- A: 手動給水（60秒）
- B: 停止ボタン
- C: 連続吐水

## メモ

### リレー

https://docs.m5stack.com/en/unit/relay  

リレーはGPIO26番として認識するらしい。GPIOインターフェースは黒のPort.Bに繋ぐ必要がある。  
その為、Port.Bを持たないcoreにはそのままでは接続できないのでBase M5GO BOTTOMを使用した。

https://docs.m5stack.com/en/base/m5go_bottom  

### ソレノイドバルブ

Amazonで購入 DC12Vで通電時に開くタイプのソレノイドバルブ  
https://www.amazon.co.jp/gp/product/B07VSLV73Y/ref=ppx_yo_dt_b_asin_title_o03_s00?ie=UTF8&psc=1  

G3/4という型の水栓コネクターに繋がる。

### RTC

設置場所はWIFI届くかどうか怪しい上に、雨とヤギの攻撃を避け缶のケース内に設置する為、ネットワークアクセス
は期待できない。その為、RTCで時間を所得して8時と15時を判定する。Port.Aで接続

https://docs.m5stack.com/en/unit/UNIT%20RTC

### ボツになった案

ヤギが水を飲んだ際に水に浮くゴミを処理する為にバケツの下部に紐をつけて、DCモーターで巻き上げて排水をする仕組みも考慮していた。  
排水 -> 半分給水でリンス -> 排水 -> フル給水 のシーケンスで処理のプランだった。  
しかし、リレーがPort.Bを必要とし、RTCがPort.Aが必要だった為、ボトムをつける必要があってGPIOが使えなくなったので諦めた。ギアボックス作ったけどまたなんか別のプロジェクトでDCモーター制御やってみたい。

