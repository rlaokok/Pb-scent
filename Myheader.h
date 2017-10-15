#include <Adafruit_NeoPixel.h>
#include<Wire.h>

const int MPU_addr = 0x68;                // I2C address of the MPU-6050
int16_t GyX, GyY, GyZ;
int iLedStatus = 0; 
int iLedFlag = 0;

// Defines  -----------------------------------------------------------------------------
#define NUMPIXELS       6
#define PIN             6
#define DATA            9

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//  -----------------------------------------------------------------------------
char rgb_data[DATA]; // 블루투스로 날라온 RGB 데이터 저장
long number; // 스트리밍 데이터를 숫자 데이터로 변경
int r; // 레드
int g; // 그린
int b; // 블루
char cnt = 0; // 문자열 카운트
int i; // LED 카운트

// Functions -----------------------------------------------------------------------------
void setup_Init()
{
    pixels.begin(); // NeoPixel library 초기화
    Serial.begin(115200); // 시리얼 속도 초기화
    mySerial.begin(9600); // 소프트 시리얼 속도 초기화
    rgb_data[DATA] = '\0'; // rgb 문자열 배열 저장 마지막 기호
    Wire.begin();
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x6B);                            // PWR_MGMT_1 register
    Wire.write(0);                                // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);
    //Serial.begin(9600);                          // 시리얼 통신 사용, 통신 보레이트 9600bps 설정
    
}

void gyro_Init()
{
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);                           // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  
    GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
    delay(100);
   
    // %화
    GyX = (GyX / (double)16000) * 100;
    GyY = (GyY / (double)16000) * 100;
    GyZ = (GyZ / (double)16000) * 100;

  
//  debug 용
//  Serial.print(F("gyro x,y,z : "));
//  Serial.print(" | GyX = "); Serial.print(GyX);   // 자이로 X축 값
//  Serial.print(" | GyY = "); Serial.print(GyY);   // 자이로 Y축 값
//  Serial.print(" | GyZ = "); Serial.println(GyZ);  // 자이로 Z축 값

}

void rgb_Init()
{
    for(i=0; i<NUMPIXELS; i++) 
    {
      pixels.setPixelColor(i, pixels.Color(0,0,0)); // LED 색깔 표현 r g b
      pixels.show(); // LED 보여주기
    }
}

void event_One()
{
//    Serial.println("EVENT ONE OCCER");
//    Serial.println("---------------");
    for(i=0; i<NUMPIXELS; i++) 
    {
      pixels.setPixelColor(i, pixels.Color(255,0,0)); // LED 색깔 표현 r g b
      pixels.show(); // LED 보여주기
    }
    iLedFlag = 1;
}

void event_Two()
{
//    Serial.println("EVENT TWO OCCER");
//    Serial.println("---------------");
    for(i=0; i<NUMPIXELS; i++) 
    {
      pixels.setPixelColor(i, pixels.Color(0,255,0)); // LED 색깔 표현 r g b
      pixels.show(); // LED 보여주기
    }
    iLedFlag = 2;
}

void event_Three()
{
//    Serial.println("EVENT THREE OCCER");
//    Serial.println("---------------");
    for(i=0; i<NUMPIXELS; i++) 
    {
      pixels.setPixelColor(i, pixels.Color(0,0,255)); // LED 색깔 표현 r g b
      pixels.show(); // LED 보여주기
    }
    iLedFlag = 3;
}

void event_Four()
{
//    Serial.println("EVENT FOUR OCCER");
//    Serial.println("---------------");
    for(i=0; i<NUMPIXELS; i++) 
    {
      pixels.setPixelColor(i, pixels.Color(100,100,100)); // LED 색깔 표현 r g b
      pixels.show(); // LED 보여주기
    }
    iLedFlag = 4;
}

void event_Five()
{
//    Serial.println("EVENT FIVE OCCER");
//    Serial.println("---------------");
    for(i=0; i<NUMPIXELS; i++) 
    {
      pixels.setPixelColor(i, pixels.Color(255,100,0)); // LED 색깔 표현 r g b
      pixels.show(); // LED 보여주기
    }
    iLedFlag = 5;
}

void event_Six()
{
//    Serial.println("EVENT SIX OCCER");
//    Serial.println("---------------");
    for(i=0; i<NUMPIXELS; i++) 
    {
      pixels.setPixelColor(i, pixels.Color(255,50,150)); // LED 색깔 표현 r g b
      pixels.show(); // LED 보여주기
    }
    iLedFlag = 6;
}

// Functions -----------------------------------------------------------------------------
void setup_Init();
void rgb_Init();
void event_One();
void event_Two();
void event_Three();
void event_Four();
void event_Five();
void event_Six();
void gyro_Init();


