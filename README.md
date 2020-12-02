# ロボットシステム学課題１　
## 17C1013 石原新也
####   4つのLEDの点灯・消灯　
	GPIOピン24,25,26,27にon/offを書き込み視力検査を再現
	また４つのLEDを順番に２０回点灯させた

#### 環境
	Raspberry Pi 3 Model B+ 
	Linux(WSL) version4.4.0-
	ubuntu20.04.1 LTS


#### 操作手順
	①sudo insmod myled.ko
	②sudo chmod 666 /dev/myled 
	③echo () > /dev/myled0      ()内には下記の番号 
		*全消灯(0)
		*↑(1)
 		*→(2)
		*↓(3)
		*←(4)
		*順番に２０回点灯
	④sudo rmmod myled
	
#### 動画
https://youtu.be/Q6ngi2x8QxA
