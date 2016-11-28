int redPin = 9;
int greenPin = 10;
int bluePin = 11;

void setup()  
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 
  Serial.begin(9600);
  Serial1.begin(9600);  // set the data rate for the BT port
}
 
void loop()
{
  if(Serial1.available()) {       //입력된 값이 있다면
   char c = Serial1.read();      //블루투스에서 값을 읽어옴
          
     switch(c) {
       case 'r':                                    //문자가 r일 경우
       analogWrite(redPin, Serial1.parseInt());    //슬라이더의 값을 정수로 바꾼 후 red 핀에 출력
       Serial.write(Serial1.parseInt());
       break;
       case 'g':                                     //문자가 g일 경우
       analogWrite(greenPin, Serial1.parseInt());  //슬라이더의 값을 정수로 바꾼 후 green 핀에 출력
       Serial.write(Serial1.parseInt());
       break;
       case 'b':                                     //문자가 b일 경우
       analogWrite(bluePin, Serial1.parseInt()); //슬라이더의 값을 정수로 바꾼 후 blue 핀에 출력
       Serial.write(Serial1.parseInt());
       break;
    }
  }
}


