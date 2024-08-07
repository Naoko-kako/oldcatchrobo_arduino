# oldcatchrobo_arduino
アルディーノで昔のキャチロボの機体を動かすプログラミング

#include <Arduino.h>
#define Max 75 

//void send_serial(int left, int right){
  //Serial.print(left);
  //Serial.print(",");
 // Serial.print(right);
  //Serial.println();
  //delay(200);}

  
int msg[3]={0};


void receive_serial() {
    if (Serial.available() > 0) {
        String receivedData = Serial.readStringUntil('\n'); // 改行までのデータを読み込む
        // データのパース（カンマで分割された2つの値を取得）
         
        String msf[3];
        int commaIndex = receivedData.indexOf(',');

        if (commaIndex != -1) {
         msf[0] = receivedData.substring(0, commaIndex);
         msf[1] = receivedData.substring(commaIndex + 1);
         msf[2] = receivedData.substring(commaIndex + 2);
        msg[0] = msf[0].toInt();
        msg[1]= msf[1].toInt();
        msg[2]= msf[2].toInt(); // 文字列を浮動小数点数に変換
        
        // データをシリアルモニターに表示
       
      
          
        }
      
    }
}

int MOT1 = 3;
 int DIR1 =6 ;  // put your setup code here, to run once:
 int MOT2 = 5;
 int DIR2=8 ;
 int MOT3=9;
 int DIR3=7;                                                                                                                                                                                                                                                                                                  

void setup() {
    Serial.begin(115200);

pinMode(MOT1,OUTPUT);
  //モーター１の速度
  pinMode(DIR1,OUTPUT);
  //モーター１の角度
  pinMode(MOT2,OUTPUT);
  //モーター２の速度
  pinMode(DIR2,OUTPUT);
  //モーター２の角度
  pinMode(MOT3,OUTPUT);
  pinMode(DIR3,OUTPUT);

}


void loop() {
    receive_serial(); // uncomment out to recieve serial data
    // send_serial(); // uncomment out to send serial data

  //ロボットの土台（右回転）
   if(msg[0]>0){
   
    analogWrite(MOT1,abs(msg[0])*0.6);
    digitalWrite(DIR1,HIGH);
   
   }else if(msg[0]<0){
    analogWrite(MOT1,abs(msg[0])*0.6);
    digitalWrite(DIR1,LOW);}
    else if(msg[1]>0){
      analogWrite(MOT2,abs(msg[1]));
      digitalWrite(DIR2,HIGH);
    }
    else if(msg[1]<0){
      analogWrite(MOT2,abs(msg[1]));
      digitalWrite(DIR2,LOW);
    }
    else{
    analogWrite(MOT1,0);
     analogWrite(MOT2,0);
      analogWrite(MOT3,0);
   }

   
       
 

}

