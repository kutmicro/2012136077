#include "DHT.h"
 
#define DHTPIN 2        // Signal 핀을 2번으로 설정
#define DHTTYPE DHT22   // DHT 타입을 DHT22로 정의
 
DHT dht(DHTPIN, DHTTYPE); // DHT 설정 - dht(digital 2, DHT22)
 
void setup() {
  Serial.begin(9600); //시리얼 통신을 시작하고 통신속도를 9600으로 한다.
  dht.begin();         //온습도 센서를 사용할 것을 라이브러리에게 알려줌
}
 
void loop() {
  // 센서의 온도와 습도를 읽어온다.
  float h = dht.readHumidity();   //변수 h에 습도 값 저장
  float t = dht.readTemperature();//변수 t에 온도 값 저장
 
  if (isnan(t) || isnan(h)) {
    //isnan(value)는 어떤 값 value가 숫자인지 아닌지 여부를 나타냄
    //값 읽기 실패시 시리얼 모니터 출력
    Serial.println("Failed to read from DHT");
  } else {
    //온도, 습도 표시 시리얼 모니터 출력
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
  }
  delay(2000);
}

