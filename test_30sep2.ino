#include <puppybot.h> //คำสั่ง #include <puppybot.h> ใช้ใน Arduino เพื่อเรียกใช้ไฟล์หรือไลบรารีที่ชื่อว่า "puppybot.h"
//เป็นไฟล์หรือไลบรารีที่มีโค้ดหรือคำสั่งเฉพาะสำหรับโปรเจคหรือการใช้งานที่เกี่ยวข้องกับหุ่นยนต์หรือระบบอื่น ๆ ที่เรียกว่า "puppybot
int Servo_degreeA1 = 50;   //ตัวแปรเก็บค่าองศาใน function catch_the_can
int Servo_degreeA2 = 50;   //ตัวแปรเก็บค่าองศาใน function release_can
int Servo_degreeB1 = 160;  //ตัวแปรเก็บค่าองศาใน function put_hand_up
int Servo_degreeB2 = 60;   //ตัวแปรเก็บค่าองศาใน function put_hand_down
int reff[] = { 512, 512, 512, 512, 512 };   //ประกาศตัวแปรเพื่อเก็บค่า reference ใช้เปรียบเทียบ ขาว และ ดำ
/* *********************************************************************************************************** */
void setup() {       //ส่วนการทำงานของโปรแกรมทำงานรอบเดียว
  puppybot_setup();  // ฟังก์ชันที่ทำงานเพื่อตั้งค่าเริ่มต้นของระบบหุ่นยนต์หรืออุปกรณ์ "puppybot" ในโปรแกรม Arduino.
  wait_SW1();        //รอให้ผู้ใช้กดสวิตช์ SW1
  trackstop();       //ฟังก์ชันวิ่งแทร็กเส้นและเมื่อเจอเส้นตัดจะทำการควบคุมการหยุดการทำงานหรือการเคลื่อนไหวของระบบหุ่นยนต์ให้หยุด
}
/* *********************************************************************************************************** */
void loop() {  //ส่วนการทำงานของโปรแกรมทำงานวนซ้ำ

}
/* *********************************************************************************************************** */
unsigned long Timesince = 0;  // ประกาศตัวแปร Timesince แบบ unsigned long และกำหนดค่าเริ่มต้นเป็น 0
void tracktime(int timer) {   // สร้างฟังก์ชัน tracktime ที่รับพารามิเตอร์ timer
  Timesince = millis();       // millis() ใช้ในการดูเวลาปัจจุบันในมิลลิวินาที (1/1000 วินาที) ของ Arduino
  while ((millis() - Timesince) < timer) { // timer คือระยะเวลาที่คุณต้องการให้ผ่านไปจนกว่าจะออกจากลูป while.
    // รอจนกว่า (เวลาปัจจุบัน - เวลาตั้งต้น) จะน้อยกว่าค่า timer
    // คำสั่งที่ต้องการให้ทำจะถูกทำซ้ำในลูปนี้ในระหว่างรอ
    track5sensor();
  }
  // หลังจากออกจากลูป while, แสดงว่าเวลา (millis() - Timesince) มีค่ามากกว่าหรือเท่ากับ timer
  // คุณสามารถทำคำสั่งที่ต้องการหลังจากการรอที่กำหนดในลูป while ได้ทันที
}
/* *********************************************************************************************************** */
void trackstop() {                               //ฟังก์ชันวิ่งแทร็กเส้นจนกว่าจะเจอเส้นตัดสีดำแล้วหยุด
  while (true) {                                 //วนซ้ำจนกว่าเงื่อนไขจะเป็นจริง
    if (ADC(0) < reff[0] && ADC(4) < reff[4]) {  //ถ้่า 0 และ 4 เจอดำพร้อมกัน ให้มอเตอร์ทั้งหมดหยุดหมุน 0.2วินาทีแล้วหลุดออกจาก While Loop ด้วยคำสั่ง Break;
      motorBreak(0);
      delay(200);
      break;
    } else  //ถ้าเงื่อนไขยังไม่เป็นจริงให้วิ่งแทร็กเส้น
    {
      track5sensor();
    }
  }
}
/* *********************************************************************************************************** */
void track5sensor() {      //ฟังก์ชันเดินตามเส้นสำหรับ 5 sensor
  if (ADC(0) < reff[0]) {  //ถ้า s0 เจอดำ หมุนซ้าย
    motor(1, -20);
    motor(2, 20);
  } else if (ADC(1) < reff[1]) {  //ถ้า s1 เจอดำ หมุนซ้าย
    motor(1, 0);
    motor(2, 20);
  } else if (ADC(2) < reff[2]) {  //ถ้า s2 เจอดำ ตรงไป
    motor(1, 20);
    motor(2, 20);
  } else if (ADC(3) < reff[3]) {  //ถ้า s3 เจอดำ หมุนขวา
    motor(1, 20);
    motor(2, 0);
  } else if (ADC(4) < reff[4]) {  //ถ้า s4 เจอดำ หมุนขวา
    motor(1, 20);
    motor(2, -20);
  }
}
/* *********************************************************************************************************** */
void track2sensor() {      //ฟังก์ชันสำหรับเดินตามเส้น2เซนเซอร์
 // ตรวจสอบสภาพเส้นทาง
  if (ADC(0) > reff[0] && ADC[4] > reff[4]) {
    // สองเซนเซอร์อยู่บนพื้นขาว (เส้นดำ)
    // เดินตรงไปข้างหน้า
    motor(1,20);
    motor(2,20);
  } else if (ADC(0) < reff[0]) {
    // เซนเซอร์ด้านซ้ายอยู่บนเส้น (ดำ)
    // หมุนไปทางซ้าย
    motor(1,-20);
    motor(2,20);
  } else if (ADC[4] < reff[4]) {
    // เซนเซอร์ด้านขวาอยู่บนเส้น (ดำ)
    // หมุนไปทางขวา
    motor(1,20);
    motor(2,-20);
  } else {
    // ไม่มีเงื่อนไขถูกต้องที่เซนเซอร์ได้รับสัญญาณ (อาจหมายถึงหุ่นยนต์หลงทาง)
    // หยุดหุ่นยนต์
    motor(1,0);
    motor(2,0);
  } 
} 
/* *********************************************************************************************************** */
void catch_the_can() {  //ฟังก์ชันสำหรับหนีบมือจับเข้า
  motorBreak(0);
  delay(50);
  servoRun(1, Servo_degreeA1);
  delay(1000);
  motorBreak(0);
  delay(50);
}
/* *********************************************************************************************************** */
void release_can() {  //ฟังก์ชันสำหรับกางมือจับออก
  motorBreak(0);
  delay(50);
  servoRun(1, Servo_degreeA2);
  delay(1000);
  motorBreak(0);
  delay(50);
}
/* *********************************************************************************************************** */
void put_hand_up() {  //ฟังก์ชันสำหรับยกแขนขึ้น
  motorBreak(0);
  delay(50);
  servoRun(1, Servo_degreeB1);
  delay(1000);
  motorBreak(0);
  delay(50);
}
/* *********************************************************************************************************** */
void put_hand_down() {  //ฟังก์ชันสำหรับกางแขนออก
  motorBreak(0);
  delay(50);
  servoRun(1, Servo_degreeB2);
  delay(1000);
  motorBreak(0);
  delay(50);
}
/* *********************************************************************************************************** */