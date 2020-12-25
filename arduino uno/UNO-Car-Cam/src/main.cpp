#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <stdio.h>
#define IN1  7
#define IN2 6
#define IN3 5
#define IN4 4
#define MAX_SPEED 255 //từ 0-255
#define MIN_SPEED 0
LiquidCrystal_I2C lcd(0x27,16,2); 
String data, mainCommand, subCommand;
#define SERVO A0
Servo servo;
void motor_1_Dung() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

}
 
void motor_2_Dung() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
 
void motor_1_Lui(int speed) { //speed: từ 0 - MAX_SPEED  
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  digitalWrite(IN1, HIGH);// chân này không có PWM
  analogWrite(IN2, 255 - speed);
}
 
void motor_1_Tien(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  digitalWrite(IN1, LOW);// chân này không có PWM
  analogWrite(IN2, speed);
}
 
void motor_2_Tien(int speed) { //speed: từ 0 - MAX_SPEED
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  analogWrite(IN3, speed);
  digitalWrite(IN4, LOW);// chân này không có PWM
}
 
void motor_2_Lui(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  analogWrite(IN3, 255 - speed);
  digitalWrite(IN4, HIGH);// chân này không có PWM
}
void waiting_wifi(){
  lcd.clear(); 
  lcd.setCursor(0,0);
  lcd.print("scan wifi");
  delay(500);
  lcd.setCursor(10,0);
  lcd.print(".");
  delay(500);
  lcd.setCursor(10,0);
  lcd.print("..");
  lcd.setCursor(10,0);
  delay(500);
  lcd.print("...");
  delay(500);
}
void servo_control(String command){
  static int angle = 90;
  if(command == "+"){
    angle = angle + 10;
  }
  if(command == "-"){
    angle = angle - 10;
  }
  if(angle > 180) angle = 180;
  if(angle < 0) angle = 0;
  servo.write(angle);
  Serial.println(angle); 
  command == "";
}
void motor_control(String command){
  if(command == "forward"){
    motor_1_Tien(MAX_SPEED);
    motor_2_Tien(MAX_SPEED);
  }
  if(command == "backward"){
    motor_1_Lui(MAX_SPEED);
    motor_2_Lui(MAX_SPEED);
  }
  if(command == "left"){
    motor_1_Tien(MAX_SPEED-100);
    motor_2_Tien(MAX_SPEED-50);
  }
  if(command == "right"){
    motor_1_Tien(MAX_SPEED-50);
    motor_2_Tien(MAX_SPEED-100);
  }
  if(command == "stop"){
    motor_1_Dung();
    motor_2_Dung();
  }
}

void setup()
{
  lcd.init();                    
  lcd.backlight();
  Serial.begin(115200);  
  servo.attach(SERVO);  
  servo.write(90);
  delay(1000);
}

void loop()
{
  while (Serial.available()){  //Kiểm tra byte để đọc
    delay(30); //Delay để ổn định hơn 
    char c = Serial.read(); // tiến hành đọc
    if (c == '#' || c == '\n' || c == '\r') {break;} //Thoát khỏi vòng lặp khi phát hiện từ #
    data += c; // data = data + c
  } 
  if(data != "") {
    mainCommand = data.substring(0, data.indexOf(" "));
    subCommand = data.substring(data.indexOf(" ")+1);
  }

  if (data.length() > 0) {
    Serial.println(data); 
    lcd.clear(); 
    lcd.setCursor(0,1);
    lcd.print(data);
  }
  if(mainCommand == "scan"){
    waiting_wifi();
  }
  if(mainCommand == "servo"){
    servo_control(subCommand);
    mainCommand = "";
    subCommand = "";
  }
  if(mainCommand == "motor"){
    motor_control(subCommand);
    delay(1000);
  }
  data = "";
}