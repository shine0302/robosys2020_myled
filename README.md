# robosys2020_myled
####  2つのLEDの点灯・消灯を行う

#### 環境
	Raspberry Pi 3 Model B+ 
	Linux(WSL) version4.4.0-18362-Microsoft 
	ubuntu20.04.1 LTS


#### 操作手順
	①sudo insmod myled.ko
	②sudo chmod 666 /dev/myled 
	③echo () > /dev/myled0      ()内には下記の番号 
		*両方消灯(0)
		*両方点灯(1)
 		*パトカーランプ風点滅20回(2)
	④sudo rmmod myled
