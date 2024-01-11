#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27,16,2); 
const int DHTPIN = 5;//Chân Out của cảm biến nối chân số 5 Arduino
const int DHTTYPE = DHT11;   // Khai báo kiểu cảm biến là DHT11
DHT dht(DHTPIN, DHTTYPE); //Khai báo thư viện chân cảm biến và kiểu cảm biến

void setup() 
{
  Serial.begin(9600);
  dht.begin(); //Khởi động cảm biến
  lcd.init(); //Khởi động LCD                    
  lcd.backlight(); //Mở đèn
  lcd.setCursor(0,0);
  lcd.print("InternetOfThings");
  lcd.setCursor(0,1);
  lcd.print("C|F:");
}

void loop() 
{
  float doC = dht.readTemperature(); //Đọc nhiệt độ C
  float doF = dht.readTemperature(true); //Đọc nhiệt độ F
  // Kiểm tra cảm biến có hoạt động hay không
  if ( isnan(doC) || isnan(doF)) 
  {
    Serial.println("Không có giá trị trả về từ cảm biến DHT");
    return;
  }

  Serial.print("InternetOfThings");
  Serial.print("  Nhiệt độ: ");
  Serial.print(doC);
  Serial.print("°C | ");
  Serial.print(doF);
  Serial.println("°F");
  lcd.setCursor(5,1);
  lcd.print(doC);
  lcd.setCursor(10,1);
  lcd.print("|");
  lcd.setCursor(11,1);
  lcd.print(doF);
  delay(1000);
}