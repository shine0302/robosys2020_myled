 # 課題１　デバイスドライバの作成
####  4つのLEDを操作するデバイスドライバを作成

#### 内容
	LED４つを上から時計回りにGPIOピン24,25,26,27と接続。
	それぞれにon/offを書き込み視力検査みたいなものを4パターン再現しました。  
	また４つのLEDを順番に２０回点灯させました。  
------------------------


#### 環境
	:Linux(WSL) version4.4.0-
	:ubuntu20.04.1 LTS
-----------------------
	
#### 使用機材
	:Raspberry Pi 3 Model B+ 
	:ELECOM 有線LANアダプタ/USB2.0/Type-A/USBハブ付/ブラック #EDC-FUA2H-B
	:LANケーブル
	:ELEGOO Electronics Fun Kit
		+Resistor 220Ω ×4
		+LED ×4
		+Breadboard ×1
		+F-M Dupont Wire ×8
		
------------------------
		
#### 接続
GPIOピン24～27を[こちら](https://www.raspberrypi.org/documentation/usage/gpio/README.md)のサイトを参考にしながら下の写真の様に接続します。
LEDは足の長いほうをプラス極に接続してください。マイナス極側はGroundと接続します。  
>https://www.raspberrypi.org/documentation/usage/gpio/README.md  

![IMG_5458](https://user-images.githubusercontent.com/51872484/101022761-2c172880-35b5-11eb-8aae-f2af947cbe37.JPG)  
色で囲ってある部分が1セット  
![IMG_E5460](https://user-images.githubusercontent.com/51872484/101022285-84015f80-35b4-11eb-96cb-4022c85392d2.JPG)  
		
		
------------------------

#### 操作手順
	1.>git clone https://github.com/shine0302/robosys2020_myled.git //このリポジトリを取得
	2.>cd robosys2020_myled 　　　//ディレクトリに入る
	3.>make 　　　　　　　　　　　//プログラムのコンパイル
	4.>sudo insmod myled.ko　　　　 //デバイスドライバのインストール
	5.>sudo chmod 666 /dev/myled0 　　//権限の付与
	6.>echo () > /dev/myled0      //実行　※()内には下記の番号 
	
		*全消灯(0)
		*↑(1)
 		*→(2)
		*↓(3)
		*←(4)
		*順番に２０回点灯(5)	
		
	7.>sudo rmmod myled　　　　　　　//デバイスドライバのアンインストール		
	
------------------------

#### 動画
[YouTube](https://youtu.be/Q6ngi2x8QxA)
※音はないです。
