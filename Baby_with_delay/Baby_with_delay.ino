#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
LiquidCrystal_I2C lcd(0x27,16,2);

int Mic_Pin = A0;
int Moisture_Pin = A1;
int mic_Value,moisture_Value;
int buzzer = 13;

int r_en = 2;
int l_en = 3;
int r_pwm = 5;
int l_pwm = 6;
int x,y = 0;

int motor_speed = 60;    //Speed control
int Motor_Start_delay = 10000;   //in milliseconds
int Motor_Stop_delay1 = 30000;   //in milliseconds
int Motor_Stop_delay2 = 30000;   //in milliseconds
int Motor_Stop_delay3 = 1000;   //in milliseconds

int Mic_Thd = 280;
int Moisture_Thd = 700;

void setup()
{
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT); 
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(13, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.setBacklight(HIGH);  

  lcd.setCursor(0,0);
  lcd.print("Swing:");
  lcd.setCursor(6,0);
  lcd.print("OFF");
  lcd.setCursor(10,0);
  lcd.print(+motor_speed);
  digitalWrite(13,LOW);
}

void loop()
{
  mic_Value = analogRead(A0);
  moisture_Value= analogRead(A1);
  digitalWrite(r_en, HIGH);
  digitalWrite(l_en, HIGH);
  
  Serial.print("mic_Value = ");
  Serial.print(mic_Value);
  Serial.print("\t\t\t");
  Serial.print("moisture_Value = ");
  Serial.print(moisture_Value);
  Serial.print("\n");
  delay(80);

//Mic
  if(mic_Value >= Mic_Thd && y == 0)
  {
    delay(Motor_Start_delay);
    Serial.println("Motor on");
    lcd.setCursor(6,0);
    lcd.print("ON ");
    analogWrite(r_pwm, motor_speed);
    analogWrite(l_pwm, 0);
    x = 1;
    y = 1;
  }
  else if(mic_Value >= Mic_Thd && y == 1)
  {
    Serial.println("Motor on");
    lcd.setCursor(6,0);
    lcd.print("ON ");
    analogWrite(r_pwm, motor_speed);
    analogWrite(l_pwm, 0);
  }
  else if(mic_Value < Mic_Thd && x == 1)
  {
    delay(Motor_Stop_delay1);
    delay(Motor_Stop_delay2);
    delay(Motor_Stop_delay3);
    Serial.println("Motor off");
    lcd.setCursor(6,0);
    lcd.print("OFF");
    analogWrite(r_pwm, 0);
    analogWrite(l_pwm, 0);
    x =0;
    y = 0;
  }
  else if(x ==0)
  {
    Serial.println("Motor off");
    delay(10);
    analogWrite(r_pwm, 0);
    analogWrite(l_pwm, 0);
  }

//Moisture
  if(moisture_Value >= Moisture_Thd)
  {
    digitalWrite(13,LOW);
    lcd.setCursor(0,1);
    lcd.print("Baby is Dry");
    delay(40);
  }
  else if(moisture_Value < Moisture_Thd)
  {
    digitalWrite(13,HIGH);
    lcd.setCursor(0,1);
    lcd.print("Baby is Wet");
    delay(40);
  }
}
