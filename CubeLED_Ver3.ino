#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
#include "Myheader.h"
// jh 수정
void control_BT_color();
void control_gyro_color();
void sensing_gyro();

int iGyro_flag = 0;
int iBT_Flag = 0;
int iFlag = 0;

// jh 수정

int save_iLedStatus = 0;
const int GYRO = 1;
const int BT = 2;
int sequence = 1;

// Init -----------------------------------------------------------------------------
void setup()                                     // 초기화
{
    setup_Init();
    sensing_gyro();
    save_iLedStatus = iLedStatus;
}



// Main Function  -----------------------------------------------------------------------------
void loop()                                      // 무한 루프
{
  if(mySerial.available()) { // 블루투스로 입력되는 시리얼 데이터가 있으면
    char ch = mySerial.read(); // ch에 데이터 저장    
  
    if (ch == '#')
      cnt = 0;
    else
      cnt++;
  
    rgb_data[cnt] = ch; // 블루투스로 넘어온 데이터를 rgb_data에 스트리밍으로 저장
  
    if (cnt == DATA - 1) { // 블루투스에서 날라온 데이터가 8개가 되면
      Serial.println(); // 시리얼 통신창 개행
      Serial.println(rgb_data); // 입력된 스트리밍 데이터 출력
      number = strtol(&rgb_data[3], NULL, 16); // 스트리밍 데이터를 숫자 데이터로 변경(맨앞 3글자는 필요 없음)
  
      // 쉬프트 연산과 and 연산을 통해 8bit 씩 데이터를 끊어서 저장
      r = number >> 16 & 0xff;
      g = number >> 8 & 0xff;
      b = number & 0xff;
  
      // 입력된 데이터를 12개의 LED에 모두 같은색으로 출력
      for (i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(r, g, b));
        pixels.show();
      }
      iGyro_flag = 0;
    }
  }  
  else{ 
    sensing_gyro();                                                   // 자이로값 센싱
    if(save_iLedStatus != iLedStatus){
        save_iLedStatus = iLedStatus;
        iGyro_flag = 1;
    }
  }

  if(iGyro_flag){control_gyro_color();}
  

}


void sensing_gyro(){
  gyro_Init();
  if ((GyX <= -50) && (GyY >= -10) && (GyZ >= -10))         {
    iLedStatus = 1;
  }
  else if ((GyX >= 50) && (GyY >= -10) && (GyZ >= -10))     {
    iLedStatus = 2;
  }
  else if ((GyX >= -10) && (GyY <= -50) && (GyZ >= -10))    {
    iLedStatus = 3;
  }
  else if ((GyX >= -10) && (GyY >= 50) && (GyZ >= -10))     {
    iLedStatus = 4;
  }
  else if ((GyX >= -10) && (GyY >= -10) && (GyZ <= -50))    {
    iLedStatus = 5;
  }
  else if ((GyX >= -10) && (GyY >= -10) && (GyZ >= 50))     {
    iLedStatus = 6;
  }
  else                                                      {
    iLedStatus = iLedFlag;  // 전 값을 기억하게
  }
}

void control_gyro_color(){  
  
  switch (iLedStatus)
  {
    case 0 :
      rgb_Init();
      break;
    case 1 :
      event_One();
      break;
    case 2 :
      event_Two();
      break;
    case 3 :
      event_Three();
      break;
    case 4 :
      event_Four();
      break;
    case 5 :
      event_Five();
      break;
    case 6 :
      event_Six();
      break;
    default :
      iLedStatus = iLedFlag;
      break;
  }    
}

