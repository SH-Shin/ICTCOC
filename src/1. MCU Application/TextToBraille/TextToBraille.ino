// 문자->점자

/***********************************************************************/
/**************************** MACRO ************************************/
/***********************************************************************/
#define DATA 8  // 입력되는 데이터 수

/***********************************************************************/
/**************************** GPIO ************************************/
/***********************************************************************/
#define B1_1 7
#define B1_2 6
#define B1_3 5
#define B1_4 4
#define B1_5 3
#define B1_6 2
#define BUTTON 12


#define B2_1 32
#define B2_2 30
#define B2_3 28
#define B2_4 26
#define B2_5 24
#define B2_6 22

#define B3_1 52
#define B3_2 50
#define B3_3 48
#define B3_4 46
#define B3_5 44
#define B3_6 42

/***********************************************************************/
/**************************** Variable *********************************/
/***********************************************************************/
char cnt = 0; // 문자열 카운트
int i; // 반복문 카운트
char chBrailleData[DATA]; // 시리얼 통신으로 들어온 데이터를 저장

long lNumber; // 스트리밍 데이터를 숫자 데이터로 변경
int iBraille_1; // 점자틀 1
int iBraille_2; // 점자틀 2
int iBraille_3; // 점자틀 3

bool bBraille_1_1 = false;    // 점자틀 1 핀 출력용 변수
bool bBraille_1_2 = false;
bool bBraille_1_3 = false;
bool bBraille_1_4 = false;
bool bBraille_1_5 = false;
bool bBraille_1_6 = false;


bool bBraille_2_1 = false;    // 점자틀 2 핀 출력용 변수
bool bBraille_2_2 = false;
bool bBraille_2_3 = false;
bool bBraille_2_4 = false;
bool bBraille_2_5 = false;
bool bBraille_2_6 = false;

bool bBraille_3_1 = false;    // 점자틀 3 핀 출력용 변수
bool bBraille_3_2 = false;
bool bBraille_3_3 = false;
bool bBraille_3_4 = false;
bool bBraille_3_5 = false;
bool bBraille_3_6 = false;

bool bReadStatus = true;    // 버튼 리드
bool bSendStatus = true;    // 버튼 플래그

/***********************************************************************/
/**************************** Initialize *******************************/
/***********************************************************************/
void setup() {
  Serial.begin(9600); // 시리얼 속도 초기화
  pinMode(BUTTON, INPUT);

  pinMode(B1_1, OUTPUT);
  pinMode(B1_2, OUTPUT);
  pinMode(B1_3, OUTPUT);
  pinMode(B1_4, OUTPUT);
  pinMode(B1_5, OUTPUT);
  pinMode(B1_6, OUTPUT);

  digitalWrite(B1_1, HIGH);
  digitalWrite(B1_2, HIGH);
  digitalWrite(B1_3, HIGH);
  digitalWrite(B1_4, HIGH);
  digitalWrite(B1_5, HIGH);
  digitalWrite(B1_6, HIGH);
  
  pinMode(B2_1, OUTPUT);
  pinMode(B2_2, OUTPUT);
  pinMode(B2_3, OUTPUT);
  pinMode(B2_4, OUTPUT);
  pinMode(B2_5, OUTPUT);
  pinMode(B2_6, OUTPUT);

  digitalWrite(B2_1, HIGH);
  digitalWrite(B2_2, HIGH);
  digitalWrite(B2_3, HIGH);
  digitalWrite(B2_4, HIGH);
  digitalWrite(B2_5, HIGH);
  digitalWrite(B2_6, HIGH);

  pinMode(B3_1, OUTPUT);
  pinMode(B3_2, OUTPUT);
  pinMode(B3_3, OUTPUT);
  pinMode(B3_4, OUTPUT);
  pinMode(B3_5, OUTPUT);
  pinMode(B3_6, OUTPUT);

  digitalWrite(B3_1, HIGH);
  digitalWrite(B3_2, HIGH);
  digitalWrite(B3_3, HIGH);
  digitalWrite(B3_4, HIGH);
  digitalWrite(B3_5, HIGH);
  digitalWrite(B3_6, HIGH);
}

/***********************************************************************/
/************************ Main Function *******************************/
/***********************************************************************/
void loop() {
  if (Serial.available())
  { // 블루투스로 입력되는 시리얼 데이터가 있으면
    char ch = Serial.read(); // ch에 데이터 저장

    if (ch == '#')
      cnt = 0;
    else
      cnt++;

    chBrailleData[cnt] = ch; // 블루투스로 넘어온 데이터를 rgb_data에 스트리밍으로 저장
    if (cnt == DATA - 1)
    { // 블루투스에서 날라온 데이터가 8-1개가 되면
      if (chBrailleData[DATA - 1] != '@') return; // 끝문자가 @가 아니면 리턴
      chBrailleData[DATA] = '\0'; // 문자열 배열 저장 마지막 기호

      lNumber = strtol(&chBrailleData[1], NULL, 16); // 스트리밍 데이터를 숫자 데이터로 변경(맨앞 1글자는 필요 없음)

      // 쉬프트 연산과 and 연산을 통해 8bit 씩 데이터를 끊어서 저장
      iBraille_1 = lNumber >> 16 & 0xff;
      iBraille_2 = lNumber >> 8 & 0xff;
      iBraille_3 = lNumber & 0xff;

      // 10진수 -> 2진수 변환
      for (i = 0; i <= iBraille_1; i++) // 점자틀 1
      {
        // 아래와 같이 쉬프트 연산을 통해 각 비트의 자리수에 해당하는 비트를 구할 수 있음
        //        Serial.print((i >> 7) % 2); // 입력된 스트리밍 데이터 출력
        //        Serial.print((i >> 6) % 2 ); // 입력된 스트리밍 데이터 출력
        bBraille_1_1 = (i >> 5) % 2;  
        bBraille_1_2 = (i >> 4) % 2;
        bBraille_1_3 = (i >> 3) % 2;
        bBraille_1_4 = (i >> 2) % 2;
        bBraille_1_5 = (i >> 1) % 2;
        bBraille_1_6 = i % 2;
      }

      // 10진수 -> 2진수 변환
      for (i = 0; i <= iBraille_2; i++) // 점자틀 2
      {
        // 아래와 같이 쉬프트 연산을 통해 각 비트의 자리수에 해당하는 비트를 구할 수 있음
        //        Serial.print((i >> 7) % 2); // 입력된 스트리밍 데이터 출력
        //        Serial.print((i >> 6) % 2 ); // 입력된 스트리밍 데이터 출력
        bBraille_2_1 = (i >> 5) % 2;  
        bBraille_2_2 = (i >> 4) % 2;
        bBraille_2_3 = (i >> 3) % 2;
        bBraille_2_4 = (i >> 2) % 2;
        bBraille_2_5 = (i >> 1) % 2;
        bBraille_2_6 = i % 2;
      }

      // 10진수 -> 2진수 변환
      for (i = 0; i <= iBraille_3; i++) // 점자틀 3
      {
        // 아래와 같이 쉬프트 연산을 통해 각 비트의 자리수에 해당하는 비트를 구할 수 있음
        //        Serial.print((i >> 7) % 2); // 입력된 스트리밍 데이터 출력
        //        Serial.print((i >> 6) % 2 ); // 입력된 스트리밍 데이터 출력
        bBraille_3_1 = (i >> 5) % 2;  
        bBraille_3_2 = (i >> 4) % 2;
        bBraille_3_3 = (i >> 3) % 2;
        bBraille_3_4 = (i >> 2) % 2;
        bBraille_3_5 = (i >> 1) % 2;
        bBraille_3_6 = i % 2;
      }

      

      digitalWrite(B1_1, !bBraille_1_1);
      digitalWrite(B1_2, !bBraille_1_2);
      digitalWrite(B1_3, !bBraille_1_3);
      digitalWrite(B1_4, !bBraille_1_4);
      digitalWrite(B1_5, !bBraille_1_5);
      digitalWrite(B1_6, !bBraille_1_6);

      digitalWrite(B2_1, !bBraille_2_1);
      digitalWrite(B2_2, !bBraille_2_2);
      digitalWrite(B2_3, !bBraille_2_3);
      digitalWrite(B2_4, !bBraille_2_4);
      digitalWrite(B2_5, !bBraille_2_5);
      digitalWrite(B2_6, !bBraille_2_6);

      digitalWrite(B3_1, !bBraille_3_1);
      digitalWrite(B3_2, !bBraille_3_2);
      digitalWrite(B3_3, !bBraille_3_3);
      digitalWrite(B3_4, !bBraille_3_4);
      digitalWrite(B3_5, !bBraille_3_5);
      digitalWrite(B3_6, !bBraille_3_6);



//      Serial.print("1 : ");
//      Serial.print(bBraille_1_1);
//      Serial.print(bBraille_1_2);
//      Serial.print(bBraille_1_3);
//      Serial.print(bBraille_1_4);
//      Serial.print(bBraille_1_5);
//      Serial.println(bBraille_1_6);
//      Serial.print("2 : ");
//      Serial.print(bBraille_2_1);
//      Serial.print(bBraille_2_2);
//      Serial.print(bBraille_2_3);
//      Serial.print(bBraille_2_4);
//      Serial.print(bBraille_2_5);
//      Serial.println(bBraille_2_6);
//      Serial.print("3 : ");
//      Serial.print(bBraille_3_1);
//      Serial.print(bBraille_3_2);
//      Serial.print(bBraille_3_3);
//      Serial.print(bBraille_3_4);
//      Serial.print(bBraille_3_5);
//      Serial.println(bBraille_3_6);
      
    }
  }
  else
  {
    bool bReadButton = digitalRead(BUTTON);
    delay(50);
    if (!bReadButton)
    {
      if (bReadStatus)
      {
        Serial.println('R'); 
      }
      bReadStatus = false;
    }
    else if (bReadButton)
    {
      bReadStatus = true;
    }
  }
}
