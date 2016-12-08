#include <DHT.h>      //DHT 라이브러리 사용

#define DHTPIN 2      //DHT 데이터 핀 번호를 2번으로 설정
#define DHTTYPE DHT22 //DHT22를 사용한다는 의미

//상태를 초기화하는 함수
void reset();
//색을 출력하도록 하는 함수
void setColor(int red, int blue, int green);

//각각 LED의 색을 출력할 핀 설정
int redPin = 9;
int greenPin = 10;
int bluePin = 11;

int mode;         //선택한 모드를 저장할 변수

DHT dht(DHTPIN, DHTTYPE); //DHT22를 2번 핀을 통해 사용함

void setup()  {
  Serial.begin(9600);   //시리얼 통신 시작, 속도는 9600
  Serial1.begin(9600);  //블루투스 통신 시작, 속도는 9600

  //각각의 데이터 핀 번호를 출력으로 설정
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  reset();
  dht.begin();  //DHT를 시작하도록 라이브러리에게 알림
}

void loop() {
  //모드를 입력받도록 함
  if (Serial1.available()) {
    int tmp = Serial1.parseInt();       //정수형으로 값을 수신

    //모드로 1, 2, 3번만 가능하도록
    if (tmp == 1 || tmp == 2 || tmp == 3)  {
      mode = tmp;                        //모드변수에 값 대입
      //시리얼 모니터에 현재 모드 상태 출력
      Serial.print("Current Mode : ");
      Serial.println(mode);
    }
  }

  //1번 모드가 선택된다면
  if (mode == 1) {
    //모드가 바뀔 때까지 반복
    while (true)  {
      char c;

      //스마트폰으로부터 값 수신
      if (Serial1.available()) {
        c = Serial1.read();
        switch (c)  {
          //값으로 'r'이 들어올 경우
          case 'r' :
            analogWrite(redPin, 255 - Serial1.parseInt()); //redPin 색 변화
            break;
          //값으로 'g'이 들어올 경우
          case 'g' :
            analogWrite(greenPin, 255 - Serial1.parseInt()); //greenPin 색 변화
            break;
          //값으로 'b'이 들어올 경우
          case 'b' :
            analogWrite(bluePin, 255 - Serial1.parseInt()); //bluePin 색 변화
            break;
          //값으로 'q'이 들어올 경우
          case 'q' :
            reset();
            break;
        }
      }

      //모드가 바뀐다면 while문 탈출
      if (mode != 1) break;
    }
  }

  //2번 모드가 선택된다면
  else if (mode == 2)  {
    int cycle_state = 0;        //주기의 상태를 저장할 변수
    int cycle = 200;           //주기를 저장할 변수
    int ledPin[3] = {9, 10, 11};//red, green, blue의 연결 핀 저장

    //모드가 바뀔 때까지 반복
    while (true)  {
      char buf[10] = {0};
      delay(cycle);     //주기만큼 지연

      //random으로 정해진 밝기를 저장
      int ran[] = {random(0, 255), random(0, 255), random(0, 255)};
      int state[3] = {0};   //현재 각 led의 상태를 기억

      //색을 random으로 바꾸기 위한 반복문
      for (int i = 0 ; i < 3 ; i++) {
        //현재 상태가 바꾸고 싶은 상태 값보다 작다면
        if (state[i] <= ran[i])  {
          for (int j = state[i] ; j <= ran[i] ; j++)  {
            analogWrite(ledPin[i], 255 - j);  //바꾸고 싶은 값까지 증가
            //delay(2);
            delay(cycle/100);
          }
        }
        //현재 상태가 바꾸고 싶은 상태 값보다 크다면
        else  {
          for (int j = state[i] ; j >= ran[i] ; j--) {
            analogWrite(ledPin[i], 255 - j);  //바꾸고 싶은 값까지 감소
            //delay(2);
            delay(cycle/100);
          }
        }
      }
      //현재상태 
      for (int i = 0 ; i < 3 ; i++)  {
        state[i] = ran[i];
      }
      
      if (Serial1.available()) {
        char c = Serial1.read();

        //주기변경 버튼이 클릭된다면
        if (c == 'c')  {
          //주기상태 확인 및 주기 변경
          if (cycle_state == 0)  {
            cycle_state++;
            cycle = 400;
            continue;
          }
          else if (cycle_state == 1) {
            cycle_state++;
            cycle = 600;
            continue;
          }
          else if (cycle_state == 2) {
            cycle_state++;
            cycle = 800;
            continue;
          }
          else if (cycle_state == 3) {
            cycle_state++;
            cycle = 1000;
            continue;
          }
          else if (cycle_state == 4) {
            cycle_state = 0;
            cycle = 200;
            continue;
          }
        }

        //값으로 'q'이 들어올 경우
        else if (c == 'q'); {
          reset();
          break;
        }
      }

      //모드가 바뀐다면 while문 탈출
      if (mode != 2) break;
    }
  }

  //3번 모드가 선택된다면
  else if (mode == 3)  {

    //모드가 바뀔 때까지 반복
    while (true)  {
      delay(500);
      // 센서의 온도와 습도를 읽어온다.
      char buf_t[10], buf_h[10], buf_di[10];          //값 송신을 위한 문자열 버퍼
      float h = dht.readHumidity();                   //변수 h에 습도 값 저장
      float t = dht.readTemperature();                //변수 t에 온도 값 저장
      float di = (1.8*t)-(0.55*(1-(h/100))*(1.8*t-26))+32;//불쾌지수 값 계산
      //isnan(value)는 어떤 값 value가 숫자인지 아닌지 여부를 나타냄
      if (isnan(t) || isnan(h)) {
        //값 읽기 실패시 시리얼 모니터 출력
        Serial.println("Failed to read from DHT");
      }

      else {
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

        dtostrf(t, 5, 1, buf_t);                 //dtostrf() 함수를 사용하여 온도를 총 5자리, 소수점 첫째자리까지 반올림 한 문자열을 buf에 저장
        Serial1.write(buf_t);                   //온도 값을 의미하는 문자열 전송
        dtostrf(h, 5, 1, buf_h);
        Serial1.write(buf_h);                   //습도 값을 의미하는 문자열 전송
        dtostrf(di, 5, 1, buf_di);
        Serial1.write(buf_di);                  //불쾌지수 값을 의미하는 문자열 전송

        //불쾌지수가 0일 경우
        if (di < 72.0)  {
          setColor(0, 255, 0);  //초록색 출력
        }
        //불쾌지수가 72와 75 사이일 경우
        else if (di < 75.0)  {
          setColor(255, 255, 0);  //노란색 출력
        }
        //불쾌지수가 75와 80 사이일 경우
        else if (di < 80.0)  {
          setColor(255, 170, 0);  //주황색 출력
        }
        //불쾌지수가 80과 83 사이일 경우
        else if (di < 83.0)  {
          setColor(255, 85, 0);   //다홍색 출력
        }
        //불쾌지수가 83 이상일 경우
        else  {
          setColor(255, 0, 0);    //빨간색 출력
        }
      }

      if (Serial1.available()) {
        char c = Serial1.read();
        //값으로 'q'이 들어올 경우
        if (c == 'q')  {
          reset();
        }
      }

      //모드가 바뀐다면 while문 탈출
      if (mode != 3) break;
    }
  }
}

//led의 상태와 모드 상태를 초기화
void reset()  {
  mode = 0;
  setColor(0, 0, 0);
}

//원하는 색을 출력하는 기능
void setColor(int red, int green, int blue) {
  analogWrite(redPin, 255 - red);
  analogWrite(greenPin, 255 - green);
  analogWrite(bluePin, 255 - blue);
}
