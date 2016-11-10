#include "DHT.h"

#define DHTPIN 2        // Signal 핀을 2번으로 설정
#define DHTTYPE DHT22   // DHT 타입을 DHT22로 정의
//void setColor(int red, int green, int blue);

//Serial1 모니터를 사용
int TxPin = 18;     // 아두이노에서 신호를 보낼 핀
int RxPin = 19;     // 아두이노에서 신호를 받을 핀
int ledRed = 11;    //red 핀을 11번에 연결
int ledGreen = 10;  //green 핀을 10번에 연결
int ledBlue = 9;    //blue 핀을 9번에 연결
int mode = 0;         //mode 변수 정의

DHT dht(DHTPIN, DHTTYPE); // DHT 설정 - dht(digital 2, DHT22)

void setup() {
  mode = 0;
  Serial.begin(9600); //시리얼 통신을 시작하고 통신속도를 9600으로 한다.
  Serial1.begin(9600);//블루투스 통신을 시작하고 통신속도를 9600으로 한다.
  //led 핀을 출력으로 설정
  for(int i=11 ; i>8 ; i--) {
    pinMode(i, OUTPUT);
  }
  dht.begin();         //온습도 센서를 사용할 것을 라이브러리에게 알려줌
}

void loop() {
  if(Serial1.available()) {
    mode = Serial1.parseInt();
    //mode가 1로 입력된다면
    if(mode == 1) {
      while(mode!=1)  {
        if(Serial1.available()) {
          char c = Serial1.read();
          switch(c) {
            case 'r':
            analogWrite(ledRed, Serial1.parseInt());
            break;
            case 'g':
            analogWrite(ledGreen, Serial1.parseInt());
            break;
            case 'b':
              analogWrite(ledBlue, Serial1.parseInt());
              break;
         }
         if(c=='q') mode = 0;
        }
      }
    }
    //mode가 2로 입력된다면
    else if(mode == 2)  {
      while(mode!=2)  {
        setColor(rand()%256, rand()%256, rand()%256);
        if(Serial1.available()) {
          if(Serial1.read()=='q')  mode = 0;
        }
        delay(1000);
      }
    }
    //mode가 3으로 입력된다면
    else if(mode == 3) {
      while(mode!=3)  {
        // 센서의 온도와 습도를 읽어온다.
        char buf_t[10], buf_h[10], buf_di[10];  //값 송신을 위한 문자열 버퍼
        float h = dht.readHumidity();           //변수 h에 습도 값 저장
        float t = dht.readTemperature();        //변수 t에 온도 값 저장
        float di = (5*t/9)-(0.55*(1-h)*((5*t/9)-26))+32;

        if (isnan(t) || isnan(h)) {
        //isnan(value)는 어떤 값 value가 숫자인지 아닌지 여부를 나타냄
        //값 읽기 실패시 시리얼 모니터 출력
        Serial.println("Failed to read from DHT");
        } else {
         //온도, 습도 표시 시리얼 모니터 출력
         dtostrf(t, 5, 1, buf_t);
         Serial1.write(buf_t);
         dtostrf(h, 5, 1, buf_h);
         Serial1.write(buf_h);
         dtostrf(di, 5, 1, buf_di);
         Serial1.write(buf_di);
         //불쾌지수가 0일 경우
         if(di < 72.0)  {
            setColor(0, 255, 0);  //초록색 출력
          }
          //불쾌지수가 72와 75 사이일 경우
          else if(di < 75.0)  {
            setColor(255, 255, 0);  //노란색 출력
          }
          //불쾌지수가 75와 80 사이일 경우
          else if(di < 80.0)  {
            setColor(255, 170, 0);  //주황색 출력
          }
          //불쾌지수가 80과 83 사이일 경우
          else if(di < 83.0)  {
            setColor(255, 85, 0);   //다홍색 출력
          }
          //불쾌지수가 83 이상일 경우
          else  {
            setColor(255, 0, 0);    //빨간색 출력
          }
        }
        if(Serial1.available()) {
          if(Serial1.read()=='q')  mode = 0;
        }
        delay(2000);
    }
   }
  }
}

void setColor(int red, int green, int blue) {
  analogWrite(ledRed, red);
  analogWrite(ledGreen, green);
  analogWrite(ledBlue, blue);
}


