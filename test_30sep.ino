#include <puppybot.h>
#define ref0 512
#define ref1 512
#define ref2 512
#define ref3 512
#define ref4 512
void setup() {
  puppybot_setup(); 
  wait_SW1();
  //





  
  //ตัวอย่างฟังก์ชัน
  //trackT_go(50); วิ่งจนกว่าจะเจอแยก + แล้วหยุดกลางแยก
  //trackT_stop(50); วิ่งจนกว่าจะเจอแยก + แล้วหยุดที่เซนเซอร์ด้านหน้า
  //turn_left(40); สั่งเลี้ยวซ้าย
  //turn_right(40); สั่งเลี้ยวขวา
}

void loop() {
}
void trackT_go(int power) {  //ฟังก์ชันถ้าเซนเซอร์ 0 และ 4 เจอดำพร้อมกันให้เดินหน้า 0.2 วิแล้วจบฟังก์ชัน ถ้ายังไม่เจอให้วิ่งแทร็กเส้น
  while (true) {
    if (ADC(0) < ref0 && ADC(4) < ref4) {  //ถ้่า 0 และ 4 เจอดำพร้อมกันให้ตอบสนองด้วยการเดินหน้านิดหน่อยและจบการทำงานฟังก์ชันนี้
      motor(1,30);motor(2,30);
      delay(120);
      break;
    } else {
      track(power);
    }
  }
}
void trackT_stop(int power) {  //ฟังก์ชันถ้าเซนเซอร์ 0 และ 4 เจอดำพร้อมกันให้หยุด 0.2 วิแล้วจบฟังก์ชัน ถ้ายังไม่เจอให้วิ่งแทร็กเส้น
  while (true) {
    if (ADC(0) < ref0 && ADC(4) < ref4) {  //ถ้่า 0 และ 4 เจอดำพร้อมกันให้ตอบสนองด้วยการหยุดและจบการทำงานฟังก์ชันนี้
      motor(1,0);motor(2,0);
      delay(200);
      break;
    } else {
      track(power);
    }
  }
}
void track(int power) {
  if (ADC(0) < ref0) {  // ถ้า 0 เจอเส้นดำให้ตอบสนองโดยการหมุนซ้าย
    motor(1, -power);
    motor(2, power);
  }
  if (ADC(1) < ref1) {  // ถ้า 1 เจอดำให้ตอบสนองด้วยการสั่งมอเตอร์ 1 หยุด แล้วมอเตอร์ 2 หมุนเท่าเดิม
    motor(1, 0);
    motor(2, power);
  }
  if (ADC(3) < ref3) {  // ถ้า 2 เจอดำให้ตอบสนองด้วยการสั่งมอเตอร์ 2 หยุด แล้วมอเตอร์ 1 หมุนเท่าเดิม
    motor(1, power);
    motor(2, 0);
  }
  if (ADC(4) < ref4) {  // ถ้า 4 เจอเส้นดำให้ตอบสนองโดยการหมุนขวา
    motor(1, power);
    motor(2, -power);
  } else {  //ถ้าไม่ใช่ให้เดินตรงไป
    motor(1, power);
    motor(2, power);
  }
}
void turn_right(int power) {  //ฟังก์ชันสำหรับการเลี้ยวขวา 90 องศา โดยใช้เซนเซอร์ตรวจจับ
  do {
    motor(1, power);
    motor(2, -power);
    // รหัสที่คุณต้องการให้ทำซ้ำ
  } while (ADC(4) > ref4 /*เงื่อนไข*/);
  do {
    motor(1, power);
    motor(2, -power);
    // รหัสที่คุณต้องการให้ทำซ้ำ
  } while (ADC(2) > ref2 /*เงื่อนไข*/);
}
void turn_left(int power) {  //ฟังก์ชันสำหรับการเลี้ยวซ้าย 90 องศา โดยใช้เซนเซอร์ตรวจจับ
  do {
    motor(1, -power);
    motor(2, power);
    // รหัสที่คุณต้องการให้ทำซ้ำ
  } while (ADC(4) > ref4 /*เงื่อนไข*/);
  do {
    motor(1, -power);
    motor(2, power);
    // รหัสที่คุณต้องการให้ทำซ้ำ
  } while (ADC(2) > ref2 /*เงื่อนไข*/);
}