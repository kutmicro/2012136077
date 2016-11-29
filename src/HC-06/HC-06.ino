void setup()  {
  Serial.begin(9600); //시리얼 통신을 시작하고 속도를 9600으로 함
  Serial1.begin(9600);//시리얼1 통신을 시작하고 속도를 9600으로 함
}

void loop() {
  //Serial1에 값이 들어왔다면
  if(Serial1.available()) {       
    Serial.write(Serial1.read());      //Serial에 출력
  }
  //Serial에 값이 들어왔다면
  if(Serial.available())  {            
    Serial1.write(Serial.read());//Serial1에 출력
  }
}
