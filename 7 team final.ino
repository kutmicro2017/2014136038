#include <Wire.h>//I2C헤더파일
#include <TimeLib.h>//RTC사용을 위해 필수 헤더파일
#include <DS1307RTC.h>//RTC사용을 위해 필수 헤더파일
#include <LiquidCrystal_I2C.h>//LCD 사용을 위해 필수 헤더파일
LiquidCrystal_I2C lcd(0x27,16,2);//LCD 0x27은 주소 가로16 세로2 쓰겠다 선언
#define sensor 4
#define BUTTON1 18
volatile bool state2 = true;
int Color;
long CheckTime;
long Min;
long Sec;
bool TimerSet;
bool CheckLcd;
bool doubleLed;
bool singleLed;
volatile bool state1 = true;

void setup() {
  Color = 0;
  doubleLed = false;
  singleLed = false;
  TimerSet = false;
  CheckLcd = false;
  Min = 0;
  Sec = 0;
  SetColor(0, 0, 0);
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(40, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, Botton, FALLING);
  lcd.begin();//lcd를 사용하겟다 는함수
  lcd.noBacklight();
  // lcd.backlight();//lcd뒤의 조명을 밝게함
  pinMode(BUTTON1,INPUT_PULLUP);
  pinMode(sensor,INPUT);
}

void loop() {
   printtime();
   // printtime();
  char c;
    bluetooth(c);
    //타이머
    if(TimerSet == true)
    {
      CheckTime = millis();
      while((millis() - CheckTime) < 1000)
      {
        printtime();
        bluetooth(c);
      }
      if(TimerSet == true)
    {
      if(Min <= 0 && Sec <= 0)
      {
        TimerSet = false;
        Min = 0;
        Sec = 0;
        singleLed = false;
        doubleLed = false;
        SetColor(1, 1, 1);
      }
      else if (Sec > 0)
      {
        Sec = Sec - 1;
      }
      else if(Min > 0 && Sec == 0)
      {
        Sec = 59;
        Min = Min - 1;
      }
      lcd.clear();
    }
  }//타이머 끝
  //터치센서
  if(state1 == false)
    {
      Tsenser();
    }
    if(digitalRead(sensor) == HIGH){
      singleLed == false;
      doubleLed == false;
      Color = 0;
      SetColor(1, 1, 1);
    }
}//터치센서


void SetColor(int a, int b, int c)//불빛 색 변경 , ON OFF > LED 모든것
{
  if(singleLed == true)
  {
    digitalWrite(40, a);
    digitalWrite(42, b);
    digitalWrite(44, c);
  }
  if(doubleLed == true)
  {
    digitalWrite(34, a);
    digitalWrite(36, b);
    digitalWrite(38, c);
  }
  if(singleLed == false && doubleLed == false)
  {
    digitalWrite(40, 1);
    digitalWrite(34, 1);
    digitalWrite(42, 1);
    digitalWrite(36, 1);
    digitalWrite(44, 1);
    digitalWrite(38, 1);
  }
}
void Botton()//터치센서 인식
{
  state1 = false;
}

void print2digits(int number) {//여기에 숫자를 입력받고 출력한다 실질적으로
  if (number >= 0 && number < 10) {//조건 입력받은 숫자가 0이상이거나 10이하 이면
    Serial.write('0');
    lcd.print("0");//0을 출력
  }
  Serial.print(number);
  lcd.print(number);//넘버를 그대로 출력 반환
}
void printtime(){
  tmElements_t tm;//time 변수 선언
  if (RTC.read(tm)) {//RTC.read는 ds1307자체의 함수 현재시간을tm에 저장한다
    lcd.setCursor(0,0);//lcd 0번째 첫째줄
    print2digits(tm.Hour);//구현한 함수로 시간출력 tm.hour는 현재시간을 받아오겟다는 뜻
    Serial.write(':');
    lcd.setCursor(2,0);
    lcd.print(":");
    ///////////////////////////////////////////-위에가 시간
    lcd.setCursor(3,0);
    print2digits(tm.Minute);
    Serial.write(':');
    lcd.setCursor(5,0);
    lcd.print(":");
    ///////////////////////////////////////////-위에 분
    lcd.setCursor(6,0);
    print2digits(tm.Second);
   //////////////////////////////////////////--위에 초
    lcd.setCursor(8,0);
    lcd.print("&&");
    Serial.print(tm.Month);
    lcd.setCursor(10,0);
    lcd.print(tm.Month);
    lcd.setCursor(12,0);
    lcd.print("/");
    //////////////////////////////////////위에는 달
    lcd.setCursor(13,0);
    lcd.print(tm.Day) ;
    Serial.print(tm.Day);
    /////////////////////////////////////위에는 일
    lcd.setCursor(0,1);
    lcd.print("Timer = ");
    lcd.setCursor(11,1);
    lcd.print(Min);
    lcd.setCursor(13,1);
    lcd.print(":");
    lcd.setCursor(14,1);
    lcd.print(Sec);
   /*
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    //lcd.setCursor(,0);
    //lcd.print(tmYearToCalendar(tm.Year));
    이거는 년도를 출력하는건데 혹시 필요할까봐 놔둠*/
    Serial.println();//시리얼 프린트 보기 편하게 한칸뜀
  } else {
    if (RTC.chipPresent()) {// DS1307 호환 칩이 있는 경우 True를 반환합니다. 오류가 발생하는 경우, 이는 실행되지 않는 DS1307과 전혀 연결되지 않은 DS1307을 구분하는 데 사용 
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);////////////////////////위에 else 문은 에러났을때 확인하는건데 시리얼창으로 확인해볼수 있음
  }
}
void bluetooth(char c)
{
  if(Serial1.available()) {
    Serial.write(c = Serial1.read());
    if(c == 'a')  //ON/OFF 및 밝기 조절
    {
      if(singleLed == false)
      {
        singleLed = true;
        doubleLed = false;
        Color = 0;
        SetColor(0, 0, 0);
      }
      else if (doubleLed == false)
      {
        singleLed = true;
        doubleLed = true;
        Color = 0;
        SetColor(0, 0, 0);
      }
      else
      {
        singleLed = false;
        doubleLed = false;
        Color = 0;
        SetColor(1, 1, 1);
      }
    }
    if(c == 'b') //색 변경
    {
       Color = Color + 1;
       if(Color > 3)
        Color = 0;
       if(Color == 0)
        SetColor(0, 0, 0);
       if(Color == 1)
        SetColor(0, 1, 1);
       if(Color == 2)
        SetColor(1, 0, 1);
       if(Color == 3)
        SetColor(1, 1, 0);
    }
    if(c == 'c')  //LCD
    {
      if(CheckLcd == false) {
        lcd.backlight();//lcd뒤의 조명을 밝게함
        lcd.clear();
        printtime();
        CheckLcd = true;
        
      }
      else
      {
        lcd.noBacklight();
        CheckLcd = false;
        
      }
    }
    if(c == 'd')  //MIN +
    {
      
      Min = Min + 1;
      if (Min > 60)
        Min = 0;
        Serial.println(Min);
        lcd.clear();
        printtime();
    }
    if(c == 'e')  //MIN -
    {
      if(Min > 0)
        Min = Min - 1;
        Serial.println(Min);
        lcd.clear();
        printtime();
    }
    if(c == 'f')  //타이머 ON
    {
      TimerSet = true; 
    }
    if(c == 'g')  //SEC +5
    {
      Sec = Sec + 5;
      if (Sec >= 60)
        Sec = 0;
      lcd.clear();
      printtime();
    }
    if(c == 'h')  //SEC -5
    {
      
      if(Sec >= 5)
        Sec = Sec - 5;
      lcd.clear();
      printtime();
    }
    if(c == 'i')  //타이머 OFF
    {
      TimerSet = false;
      Min = 0;
      Sec = 0;
      lcd.clear();
      printtime();
    }
    }
}

void Tsenser()
{
  if(singleLed == false && doubleLed == false)
      {
        singleLed = true;
        Color = 0;
        SetColor(0, 0, 0);
      }
      else if(singleLed == true && doubleLed == false)
      {
        doubleLed = true;
        Color = 0;
        SetColor(0, 0, 0);
      }
      else if(doubleLed == true && Color == 0)
      {
        Color = 1;
        SetColor(0, 1, 1);
      }
      else if(doubleLed == true && Color == 1)
      {
        Color = 2;
        SetColor(1, 0, 1);
      }
      else if(doubleLed == true && Color == 2)
      {
        Color = 3;
        SetColor(1, 1, 0);
      }
      else if(doubleLed == true && Color == 3)
      {
        Color = 0;
        SetColor(1, 1, 1);
        singleLed = false;
        doubleLed = false;
        Min = 0;
        Sec = 0;
      }
      state1 = true;
}


