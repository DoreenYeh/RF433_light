#include <RCSwitch.h>
int delayval = 500;
int btn1 = 0;
int btn2 = 0;
int btn3 = 0;
int prestatu1 = 0;
int prestatu2 = 0;
int prestatu3 = 0;
RCSwitch mySwitch = RCSwitch();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);


  // Transmitter is connected to Arduino Pin #10
  mySwitch.enableTransmit(1);
}

void loop() {
  // put your main code here, to run repeatedly:
  // btn1
  btn1 = digitalRead(10); //開關
  btn2 = digitalRead(11); //顏色變化
  btn3 = digitalRead(12); //燈光效果
  if (btn1 == HIGH) {
    delay(20);
    if (btn1 == HIGH) {
      prestatu1 = 1;
    }
  }
  if (btn1 == 0 and prestatu1 == 1) { // 按鈕放開 and 前一個有按按鈕->執行
    Serial.println("btn1 Click");
    mySwitch.send("101000000000000000000100");
    delay(100);
    prestatu1 = 0;
  }

  // btn2
  if (btn2 == HIGH) {
    delay(20);
    if (btn2 == HIGH) {
      prestatu2 = 1;
    }
  }
  if (btn2 == 0 and prestatu2 == 1) { // 按鈕放開 and 前一個有按按鈕->執行
    Serial.println("btn2 Click");
    mySwitch.send("101000000000000000000010");
    delay(100);
    prestatu2 = 0;
  }

  // btn3
  if (btn3 == HIGH) {
    delay(20);
    if (btn3 == HIGH) {
      prestatu3 = 1;
    }
  }
  if (btn3 == 0 and prestatu3 == 1) { // 按鈕放開 and 前一個有按按鈕->執行
    Serial.println("btn3 Click");
    mySwitch.send("101000000000000000000001");
    delay(100);
    prestatu3 = 0;
  }
  //mySwitch.send("101000000000000000000100");
  //mySwitch.send("101000000000000000000010");
  //mySwitch.send("101000000000000000000001");


}
