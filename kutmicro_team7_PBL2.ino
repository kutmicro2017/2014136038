const int row[8] = {22, 23, 24, 25, 26, 27, 28, 29 };
const int col[8] = {30, 31, 32, 33, 34, 35, 36, 37 };
const int row2[8] = {38, 39, 40, 41, 42, 43, 44, 45};
const int col2[8] = {46, 47, 48, 49, 19, 18, 17, 16};

int number[10][8][4] = {
  {0, 1, 1, 0,  //0
   1, 0, 0, 1,
   1, 0, 0, 1,
   1, 0, 0, 1,
   1, 0, 0, 1,
   1, 0, 0, 1,
   1, 0, 0, 1,
   0, 1, 1, 0},
  {0, 0, 1, 0,  //1
   0, 1, 1, 0,
   1, 0, 1, 0,
   0, 0, 1, 0,
   0, 0, 1, 0,
   0, 0, 1, 0,
   0, 0, 1, 0,
   1, 1, 1, 1},
  {1, 1, 1, 1,  //2
   0, 0, 0, 1,
   0, 0, 0, 1,
   1, 1, 1, 1,
   1, 0, 0, 0,
   1, 0, 0, 0,
   1, 0, 0, 0,
   1, 1, 1, 1},
  {1, 1, 1, 1,  //3
   0, 0, 0, 1,
   0, 0, 0, 1,
   1, 1, 1, 1,
   0, 0, 0, 1,
   0, 0, 0, 1,
   0, 0, 0, 1,
   1, 1, 1, 1},
  {1, 0, 0, 1,  //4
   1, 0, 0, 1,
   1, 0, 0, 1,
   1, 1, 1, 1,
   0, 0, 0, 1,
   0, 0, 0, 1,
   0, 0, 0, 1,
   0, 0, 0, 1},
  {1, 1, 1, 1,  //5
   1, 0, 0, 0,
   1, 0, 0, 0,
   1, 1, 1, 1,
   0, 0, 0, 1,
   0, 0, 0, 1,
   0, 0, 0, 1,
   1, 1, 1, 1},
  {1, 1, 1, 1,  //6
   1, 0, 0, 1,
   1, 0, 0, 0,
   1, 1, 1, 1,
   1, 0, 0, 1,
   1, 0, 0, 1,
   1, 0, 0, 1,
   1, 1, 1, 1},
  {1, 1, 1, 1,  //7
   1, 0, 0, 1,
   1, 0, 0, 1,
   0, 0, 0, 1,
   0, 0, 0, 1,
   0, 0, 0, 1,
   0, 0, 0, 1,
   0, 0, 0, 1},
  {1, 1, 1, 1,  //8
   1, 0, 0, 1,
   1, 0, 0, 1,
   1, 1, 1, 1,
   1, 0, 0, 1,
   1, 0, 0, 1,
   1, 0, 0, 1,
   1, 1, 1, 1},
  {1, 1, 1, 1,  //9
   1, 0, 0, 1,
   1, 0, 0, 1,
   1, 1, 1, 1,
   0, 0, 0, 1,
   1, 0, 0, 1,
   1, 0, 0, 1,
   1, 1, 1, 1}
};
int PTLight[2][8][8] = {
  {0, 0, 0, 1, 1, 0, 0, 0,  //정지
   0, 0, 0, 1, 1, 0, 0, 0,
   0, 0, 1, 1, 1, 1, 0, 0,
   0, 1, 0, 1, 1, 0, 1, 0,
   0, 1, 0, 1, 1, 0, 1, 0,
   0, 0, 0, 1, 1, 0, 0, 0,
   0, 0, 1, 0, 0, 1, 0, 0,
   0, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0,  //출발
   0, 0, 0, 1, 1, 0, 0, 0,
   0, 0, 1, 1, 1, 1, 1, 0,
   0, 0, 1, 1, 1, 0, 0, 1,
   1, 1, 0, 1, 1, 0, 0, 1,
   0, 0, 0, 1, 1, 0, 0, 0,
   0, 0, 1, 0, 0, 1, 0, 0,
   0, 0, 1, 0, 0, 0, 1, 0}
};

#define Right_G 1   //우측 신호등
#define Right_Y 2
#define Right_R 3
#define Up_G 4      //위측 신호등
#define Up_Y 5
#define Up_R 6
#define Left_G 7    //좌측 신호등
#define Left_Y 8
#define Left_R 9
#define Down_G 10   //아래쪽 신호등
#define Down_Y 11
#define Down_R 12
#define Botton_1 20 //스위치
long interval;
long IntervalSet = 20000;
long IntervalAdd = 10000;
long BlinkYellow = 3;  //노란불 점멸 카운트
int SDelay = 3000;
volatile bool state1 = true;  //스위치를 누르면 false로 변환

long CheckTime;

void setup() {
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
  for (int thisPin = 0; thisPin < 8; thisPin++) 
   {
    pinMode(row[thisPin], OUTPUT);
    pinMode(col[thisPin], OUTPUT);
    pinMode(row2[thisPin], OUTPUT);
    pinMode(col2[thisPin], OUTPUT);
   }
}

void loop() {
  //unsigned long CheckTime = millis(); //타이머 함수, deley를 이용하여도 millis()는 흐른다
  int Time;
  interval = IntervalSet;
  digitalWrite(Right_G, HIGH);
  digitalWrite(Up_R, HIGH);
  digitalWrite(Left_G, HIGH);
  digitalWrite(Down_R, HIGH);
 
  CheckTime = millis();
  SwitchLoop(Right_G, Right_Y, Right_R, Left_G, Left_Y, Left_R);
  digitalWrite(Up_R, LOW);
  digitalWrite(Down_R, LOW);
  digitalWrite(Up_G, HIGH);
  digitalWrite(Down_G, HIGH);

  CheckTime = millis();
  while(interval > (millis() - CheckTime)) {
    PSignal(0);
    Time = (interval - (millis() - CheckTime)) / 1000;
    /*
    if(state1 == false){
        interval += IntervalAdd;
        delay(100);
    }
    CleanDOT();
    state1 = true;
    */
    NSignal(Time);
  }
  interval = IntervalSet;
  digitalWrite(Up_G, LOW);
  digitalWrite(Down_G, LOW);
  BlinkLED(Up_Y, Down_Y);
  digitalWrite(Up_R, HIGH);
  digitalWrite(Down_R, HIGH);
  
  digitalWrite(Left_R, LOW);
  digitalWrite(Right_R, LOW);
  
}

// 인터럽트 발생시 호출(스위치를 누를 경우 호출)
void Botton() {
  /*
  if(digitalRead(Right_G) == HIGH){
  state1 = false;
  }
  */
  state1 = false;
}

// 노란불 점멸 함수
void BlinkLED(const int YellowLED1, const int YellowLED2) {
  long Time;
   for(int i = 0; i <  BlinkYellow; i++){
    digitalWrite(YellowLED1, HIGH);
    digitalWrite(YellowLED2, HIGH);
    Time = millis();
    while((millis() - Time) <= 500)
    {
      PSignal(0);
      //NSignal((BlinkYellow - i));
    }
    digitalWrite(YellowLED1, LOW);
    digitalWrite(YellowLED2, LOW);
    Time = millis();
    while((millis() - Time) <= 500)
    {
      PSignal(0);
      //NSignal((BlinkYellow - i));
    }
   }
}

// 스위치 함수
void SwitchLoop(int GLight1, int YLight1, int RLight1, int GLight2, int YLight2, int RLight2) {
  int Time;
  long DTime;
  
  state1 = true;
  while(interval > (millis() - CheckTime)) {  //interval 시간 동안 진행
    if(state1 == false) { //위측 신호등이 녹색등일 동안에 스위치를 누를 경우 진행
      DTime = millis();
      while(SDelay > (millis() - DTime)){ 
       PSignal(0);
       Time = (SDelay - (millis() - DTime)) / 1000;
       NSignal(Time);
       CleanDOT();
      }
      digitalWrite(GLight1, LOW);
      digitalWrite(GLight2, LOW);
      BlinkLED(YLight1, YLight2);
      digitalWrite(RLight1, HIGH);
      digitalWrite(RLight2, HIGH);
      state1 = true;
      //CheckTime = millis();
      while(interval > (millis() - CheckTime))
      {
        PSignal(1);
        Time = (interval - (millis() - CheckTime)) / 1000;
        /*
        if(state1 == false){
           interval += IntervalAdd;
           delay(100);
        }
        */
        NSignal(Time);
        CleanDOT();
        state1 = true;
      }
      CleanDOT();
    }
    PSignal(0);
    Time = (interval - (millis() - CheckTime)) / 1000;
    NSignal(Time);
    interval = IntervalSet;
    CleanDOT();
  }
  if(digitalRead(GLight1) == HIGH) { //스위치가 눌리지 않았을 경우 진행
    digitalWrite(GLight1, LOW);
    digitalWrite(GLight2, LOW);
    BlinkLED(YLight1, YLight2);
    digitalWrite(RLight1, HIGH);
    digitalWrite(RLight2, HIGH);
  }
  else
    BlinkLED(YLight1, YLight2);
} 

void CleanDOT() //도트 매트릭스 전체를 정리
{
  for(int i = 0; i < 8; i++)
  {
     digitalWrite(row[i], LOW);
     digitalWrite(col[i], HIGH);
     digitalWrite(row2[i], LOW);
     digitalWrite(col2[i], HIGH);
  }
}

void NSignal(int Time)  // 남은 시간
{
  int FTime;
  int LTime;

  FTime = Time / 10;
  LTime = Time % 10;
  for(int i = 0; i < 8; i++)
  {
    CleanDOT();
    for(int j = 0; j < 4; j++)
    {
      digitalWrite(row[i], HIGH);
      if(number[FTime][i][j]){
       digitalWrite(col[j], LOW);
       delay(1);
      }
      if(number[LTime][i][j]){
        digitalWrite(col[j+4], LOW);
        delay(1);
      }
    }
  }
  CleanDOT();
}

void PSignal(int GoStop)  //사람 모습
{
  for(int i = 0; i < 8; i++)
  {
    CleanDOT();
    for(int j = 0; j < 8; j++)
    {
      digitalWrite(row2[i], HIGH);
      if(PTLight[GoStop][i][j] == 1){
       digitalWrite(col2[j], LOW);
        delay(1);
      }
    }
  }
}



