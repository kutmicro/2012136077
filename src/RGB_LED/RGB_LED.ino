int ledRed = 11;//rgb led의 red부분 핀 설정 
int ledGreen = 10;//rgb led의 green부분 핀 설정
int ledBlue = 9;//rgb led의 blue부분 핀 설정

void setColor(int red, int green, int blue);
void setup()
{
 pinMode(ledRed, OUTPUT);    //각 데이터 핀을 출력으로 설정
 pinMode(ledGreen, OUTPUT);
 pinMode(ledBlue, OUTPUT); 
}
 
void loop()
{
  //random으로 색이 바뀌도록 함
  setColor(rand()%256, rand()%256, rand()%256);
  
  //1초의 지연시간을 줌
  delay(1000);
}
 
void setColor(int red, int green, int blue) //각각 인자를 받아 색을 출력하는 함수
{
  //analogWrite는 Duty rate를 조절하여 LED가 출력하는 밝기 조절 가능
  analogWrite(ledRed, red);   //red 핀의 값 입력   
  analogWrite(ledGreen, green); //green 핀의 값 입력
  analogWrite(ledBlue, blue);     //blue 핀의 값 입력
}
