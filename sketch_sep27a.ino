#define Right_G 1 //우측 신호등
#define Right_Y 2
#define Right_R 3
#define Up_G 4   //위측 신호등
#define Up_Y 5
#define Up_R 6
#define Left_G 7  //좌측 신호등
#define Left_Y 8
#define Left_R 9
#define Down_G 10 //아래쪽 신호등
#define Down_Y 11
#define Down_R 12
#define Botton_1 20 //스위치
int interval = 30000;
volatile bool state1 = true;  //스위치를 누르면 false로 변환

void setup() {  //셋팅
  pinMode(Right_G, OUTPUT);
  pinMode(Right_Y, OUTPUT);
  pinMode(Right_R, OUTPUT);
  pinMode(Up_G, OUTPUT);
  pinMode(Up_Y, OUTPUT);
  pinMode(Up_R, OUTPUT);
  pinMode(Left_G, OUTPUT);
  pinMode(Left_Y, OUTPUT);
  pinMode(Left_R, OUTPUT);
  pinMode(Down_G, OUTPUT);
  pinMode(Down_Y, OUTPUT);
  pinMode(Down_R, OUTPUT);
  pinMode(Botton_1, INPUT_PULLUP);  //input과의 차이는 프로세서 내부에 있는 pull-up 저항을 사용
  attachInterrupt(3, Botton, FALLING);  //인터럽트 지정함수(어느핀으로 인터럽트 처리, 호출함수 이름, 모드(신호가 high에서 low))
}

void loop() {
  digitalWrite(Right_G, HIGH);  //처음 신호
  digitalWrite(Up_R, HIGH);
  digitalWrite(Left_R, HIGH);
  digitalWrite(Down_R, HIGH);
  delay(30000); //30초 대기
  digitalWrite(Right_G, LOW);
  BlinkLED(Right_Y);  //yellow신호 점멸함수
  digitalWrite(Right_R, HIGH); 
  digitalWrite(Up_R, LOW);
  digitalWrite(Up_G, HIGH);
  unsigned long CheckTime = millis(); //타이머 함수(deley를 이용하여도 millis()는 흐른다
  while(interval > (millis() - CheckTime)) {  //interval 시간 동안 진행
    if(state1 == false) { //위측 신호등이 녹색등일 동안에 스위치를 누를 경우 진행
      delay(3000);
      digitalWrite(Up_G, LOW);
      BlinkLED(Up_Y);
      digitalWrite(Up_R, HIGH);
      state1 = true;
    }
    delay(5000);
  }
  if(digitalRead(Up_G) == HIGH) { //스위치가 눌리지 않았을 경우 진행
    digitalWrite(Up_G, LOW);
    BlinkLED(Up_Y);
    digitalWrite(Up_R, HIGH);
  }
  digitalWrite(Left_R, LOW);
  digitalWrite(Left_G, HIGH);
  delay(30000);
  digitalWrite(Left_G, LOW);
  BlinkLED(Left_Y);
  digitalWrite(Left_R, HIGH);
  digitalWrite(Down_R, LOW);
  digitalWrite(Down_G, HIGH);
  delay(30000);
  digitalWrite(Down_G, LOW);
  BlinkLED(Down_Y);
  digitalWrite(Down_R, HIGH);
  digitalWrite(Right_R, LOW);
}

void Botton() { //인터럽트 발생시 호출(스위치를 누를 경우 호출)
  if(digitalRead(Up_G) == HIGH)
  state1 = false;
}

void BlinkLED(const int YellowLED) {  //yellow신호 점멸
   for(int i =0; i < 5; i++) {
    digitalWrite(YellowLED, HIGH);
    delay(500);
    digitalWrite(YellowLED, LOW);
    delay(500);
   }
}
