#include "DHT.h"

#define DHTPIN 2        // Signal 핀을 2번으로 설정
#define DHTTYPE DHT22   // DHT 타입을 DHT22로 정의

DHT dht(DHTPIN, DHTTYPE); // DHT 설정 - dht(digital 2, DHT22)

void setup() {
  Serial.begin(9600); //시리얼 통신을 시작하고 통신속도를 9600으로 한다.
  Serial1.begin(9600);//블루투스 통신을 시작하고 통신속도를 9600으로 한다.
  dht.begin();         //온습도 센서를 사용할 것을 라이브러리에게 알려줌
}

void loop() {
  // 센서의 온도와 습도를 읽어온다.
  char buf_t[10], buf_h[10], buf_di[10];          //값 송신을 위한 문자열 버퍼
  float h = dht.readHumidity();                   //변수 h에 습도 값 저장
  float t = dht.readTemperature();                //변수 t에 온도 값 저장
  float di = (5*t/9)-(0.55*(1-h/100)*((5*t/9)-26))+32;//불쾌지수 값 계산
        
  //isnan(value)는 어떤 값 value가 숫자인지 아닌지 여부를 나타냄
  if (isnan(t) || isnan(h)) {
    //값 읽기 실패시 시리얼 모니터 출력
    Serial.println("Failed to read from DHT");
  } else {
    //온도, 습도 표시 시리얼 모니터 출력
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.print(" *C\t");
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("DI : ");
    Serial.print(di);
    Serial.println(" %\t");

    //블루투스를 통해 값들을 송신
    dtostrf(t, 5, 1, buf_t);                 //dtostrf() 함수를 사용하여 온도를 총 5자리, 소수점 첫째자리까지 반올림 한 문자열을 buf에 저장
    Serial1.write(buf_t);                   //온도 값을 의미하는 문자열 전송
    dtostrf(h, 5, 1, buf_h);                 
    Serial1.write(buf_h);                   //습도 값을 의미하는 문자열 전송
    dtostrf(di, 5, 1, buf_di);     
    Serial1.write(buf_di);                  //불쾌지수 값을 의미하는 문자열 전송
    delay(1000);
  }
}
