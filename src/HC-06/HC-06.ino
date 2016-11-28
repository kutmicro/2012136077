int TxPin = 18;   //아두이노에서 보내는 핀 설정
int RxPin = 19;   //아두이노에서 받는 핀 설정
int ledPin = 11;  //led 핀 설정
String myString="";//받는 문자열 정의

void setup()  
{
  Serial.begin(9600);   //아두이노의 시리얼 속도를 9600으로 설정
  Serial1.begin(9600); //블루투스의 시리얼 속도를 9600으로 설정
  pinMode(ledPin, OUTPUT); //led가 연결된 핀을 출력으로 설정
}

void loop()
{
  if (Serial1.available()) // 블루투스 시리얼 값이 있다면
  {
    char c = (char)Serial1.read(); //블루투스 시리얼의 내용을 읽음
    myString += c;  //수신되는 문자열을 myString에 모두 붙임(1바이트씩)
    delay(5);       //수신 문자열 끊김 방지
   }
   if(!myString.equals("")) //myString값이 공백이 아니라면
   {
    if(myString == "ON") {      //블루투스 시리얼에 1이 입력되었다면
       digitalWrite(ledPin,HIGH);  //led의 전원을 ON
     } else if(myString == "OFF") {   //블루투스 시리얼에 0이 입력되었다면
       digitalWrite(ledPin,LOW); //led의 전원을 OFF
     }
   }
}

void setup()  {
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  if(Serial1.available()) {
    Serial.write(Serial1.read());
  }

  if(Serial.available())  {
    Serial1.write(Serial.read());
  }
}
