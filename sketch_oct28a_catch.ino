

#include<Arduino.h>
#define Max 75
void send_serial(int left,int right){
  Serial.print(left);
  Serial.print(","); 
 Serial.print(right); 
 Serial.println();
 delay(200);}




int msg[5]={0};


void receive_serial() {
  if (Serial.available() > 0) {

   String receivedData = Serial.readStringUntil('\n'); // 改行までのデータを読み込む // データのパース（カンマで分割された2つの値を取得）

    String msf[5];
    int commaIndex = receivedData.indexOf(',');

    if (commaIndex != -1) {
     msf[0] = receivedData.substring(0, commaIndex);
     msf[1] = receivedData.substring(commaIndex + 1);
     msf[2] = receivedData.substring(commaIndex + 2);
     msf[3] = receivedData.substring(commaIndex + 3);
     msf[4] = receivedData.substring(commaIndex + 4);

     msg[0] = msf[0].toInt();
     msg[1]= msf[1].toInt();
     msg[2]= msf[2].toInt(); 
     msg[3]= msf[3].toInt();
     msg[4]= msf[4].toInt();  // 文字列を浮動小数点数に変換
    
     // データをシリアルモニターに表示
   
    }

  }
}



//int なので整数値で設定

int MOT1=3;
int DIR1=4;
int MOT2=6;
int DIR2=5;
int MOT3=9; 
int DIR3=8;
int relay=10;



void setup(){
	Serial.begin(115200);
	pinMode(MOT1,OUTPUT);
	pinMode(DIR1,OUTPUT);
	pinMode(MOT2,OUTPUT);
	pinMode(DIR2,OUTPUT);
	pinMode(MOT3,OUTPUT);
	pinMode(DIR3,OUTPUT);
	pinMode(relay,OUTPUT);

	
}


void loop(){
  receive_serial();

        Serial.println(msg[0]);
        Serial.print(" msg[0]: ");
        Serial.print(msg[1]);
        Serial.print(" msg[1]: ");
        Serial.print(msg[2]);
        Serial.print(" msg[2]: ");
        Serial.print(msg[3]);
        Serial.print(" msg[3]: ");
        Serial.println(msg[4]);
        Serial.print(" msg[4]: ");
 
	


	
	if(msg[1]>0){
	analogWrite(MOT1,75);
	digitalWrite(DIR1,HIGH);
	}
  else if(msg[1]<0){
	analogWrite(MOT1,75);
	digitalWrite(DIR1,LOW);}		
	
	else if(msg[2]>0){
	analogWrite(MOT2,75); 		
	digitalWrite(DIR2,HIGH);}

	else if(msg[2]<0){
	analogWrite(MOT2,75);
	digitalWrite(DIR2,LOW);}

	else if(msg[3]>0){
	analogWrite(MOT3,75);
	digitalWrite(DIR3,HIGH);}

	else if(msg[3]<0){
	analogWrite(MOT3,75);
	analogWrite(DIR3,LOW);}

  //R1R2
	else if(msg[4]>0){
	digitalWrite(relay,LOW);}
	else if(msg[4]<0){
	digitalWrite(relay,HIGH);}
  
  
  else{
  analogWrite(MOT1,0); 
  analogWrite(MOT2,0);
  analogWrite(MOT3,0); 
 
  }

}