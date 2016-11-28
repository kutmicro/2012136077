#include "DHT.h"

#define DHTPIN 2        // Signal 핀을 2번으로 설정
#define DHTTYPE DHT22   // DHT 타입을 DHT22로 정의
void setColor(int red, int green, int blue);

int redPin = 9;    //red 핀을 11번에 연결
int greenPin = 10;  //green 핀을 10번에 연결
int bluePin = 11;    //blue 핀을 9번에 연결

DHT dht(DHTPIN, DHTTYPE); // DHT 설정 - dht(digital 2, DHT22)

void setup() {
  Serial.begin(9600); //시리얼 통신을 시작하고 통신속도를 9600으로 한다.
  //led 핀을 출력으로 설정
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  dht.begin();         //온습도 센서를 사용할 것을 라이브러리에게 알려줌
}

void loop() {
  float h = dht.readHumidity();                   //변수 h에 습도 값 저장
  float t = dht.readTemperature();                //변수 t에 온도 값 저장
  float di = (5*t/9)-(0.55*(1-h/100)*((5*t/9)-26))+32;//불쾌지수 값 게산
        
  //isnan(value)는 어떤 값 value가 숫자인지 아닌지 여부를 나타냄
  if (isnan(t) || isnan(h)) {
    //값 읽기 실패시 시리얼 모니터 출력
    Serial.println("Failed to read from DHT");
  } 
  //불쾌지수가 0일 경우
  else if(di < 72.0)  {
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
  //습도, 온도, 불쾌지수를 시리얼 모니터에 출력
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C\t");
  Serial.print("DI : ");
  Serial.print(di);
  Serial.println(" %\t");
  delay(1000);  //1초간의 지연 시간
}

//PWM을 이용한 밝기 조절을 통해 색을 출력하는 함수
void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
