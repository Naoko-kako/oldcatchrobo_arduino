

#include <Arduino.h>
#define Max 75
void send_serial(int left,int right){
  Serial.print(left);
  Serial.print(","); 
  Serial.print(right); 
  Serial.println();
  delay(200);}





int msg[5] = {0};



void receive_serial() {
  if (Serial.available() > 0) {

    String received_data = Serial.readStringUntil('\n'); 
      
    String msgstr[5];   // 改行までのデータを読み込む
    Serial.println(received_data);                          // データをシリアルモニターに表示

    int comma_index1 = received_data.indexOf(',');                                        // 1番目のカンマの位置を検索
    if (comma_index1 != -1)
    {
        msgstr[0] = received_data.substring(0, comma_index1);                            // 1番目の部分文字列を取得
        int comma_index2 = received_data.indexOf(',', comma_index1 + 1);                  // 2番目のカンマの位置を検索
        if (comma_index2 != -1)
        {
            msgstr[1] = received_data.substring(comma_index1 + 1);                      // 2番目の部分文字列を取得
            int comma_index3 = received_data.indexOf(',', comma_index2 + 1); 
            if(comma_index3 != -1)                                                       // 3番目のカンマの位置を検索
            {
              msgstr[2] = received_data.substring(0, comma_index2);                            // 1番目の部分文字列を取得
              int comma_index4 = received_data.indexOf(',', comma_index3 + 1);     
              if (comma_index4 != -1)
              {
                  msgstr[3] = received_data.substring(comma_index3 + 1, comma_index4);   // 3番目の部分文字列を取得
                  msgstr[4] = received_data.substring(comma_index4 + 1);                 // 4番目の部分文字列を取得
              }
              else
              {
                  // カンマが3つ未満の場合のエラーハンドリング
                  Serial.println("Error: Less than 2 commas in the inputString.");
              }
        }
        else
        {
            // カンマが2つ未満の場合のエラーハンドリング
            Serial.println("Error: Less than 2 commas in the inputString.");
        }
    }
    else
    {
        // カンマが見つからない場合のエラーハンドリング
        Serial.println("Error: No comma found in the inputString.");
    }

    msg[0] = msgstr[0].toInt();
    msg[1] = msgstr[1].toInt();
    msg[2] = msgstr[2].toInt();
    msg[3] = msgstr[3].toInt();
    msg[4] = msgstr[4].toInt();


      // 文字列を浮動小数点数に変換

      // データをシリアルモニターに表示
    
  }
}         
}     

//int なので整数値で設定

int MOT1 = 3;
int DIR1 = 4;
int MOT2 = 6;
int DIR2 = 5;
int MOT3 = 9;
int DIR3 = 8;
int relay = 10;



void setup()
{
  Serial.begin(115200);
  pinMode(MOT1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(MOT2, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(MOT3, OUTPUT);
  pinMode(DIR3, OUTPUT);
  pinMode(relay, OUTPUT);
}


void loop() 
{
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






  if (msg[1] > 5) {
    analogWrite(MOT1, 75);
    digitalWrite(DIR1, HIGH);
  } 
  else if (msg[1] < -5) {
    analogWrite(MOT1, 75);
    digitalWrite(DIR1, LOW);
  }

  else if (msg[2] > 5) {
    analogWrite(MOT2, 75);
    digitalWrite(DIR2, HIGH);
  }

  else if (msg[2] < -5) {
    analogWrite(MOT2, 75);
    digitalWrite(DIR2, LOW);
  }

  else if (msg[3] > 5) {
    analogWrite(MOT3, 75);
    digitalWrite(DIR3, HIGH);
  }
  else if (msg[3] < -5) {
    analogWrite(MOT3, 75);
    digitalWrite(DIR3, LOW);
  }
  //R1R2
  else if (msg[4] > 5) {
    digitalWrite(relay, LOW);
   } 
  else if (msg[4] < -5) {
    digitalWrite(relay, HIGH);
   }
  else {
    analogWrite(MOT1, 0);
    analogWrite(MOT2, 0);
    analogWrite(MOT3, 0);
  }

}