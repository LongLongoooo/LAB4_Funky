#include <scheduler.h>
#define LED_PIN 48
#define D3 6
#define D4 7
#define D5 8
#define D6 9

// 00: off
// 01: yellow
// 10: green
// 11: red

void red_green(){
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);

  digitalWrite(D5, HIGH);
  digitalWrite(D6, LOW);
}

void red_yellow(){
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);

  digitalWrite(D5, LOW);
  digitalWrite(D6, HIGH);
}

void green_red(){
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);

  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
}

void yellow_red(){
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);

  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
}
void TIMER_ISR(void *pvParameters) {
  
  while(1) {
    SCH_Update();
    vTaskDelay(10);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);

  xTaskCreate(TIMER_ISR, "TIMER_ISR", 2048, NULL, 2, NULL);

  SCH_Init();
  SCH_Add_Task(red_green, 0,    1000);  // Execute at 0 ticks, then every 1000 ticks.
  SCH_Add_Task(red_yellow, 300, 1000);    // Execute at 300 ticks, then every 1000 ticks.
  SCH_Add_Task(green_red, 500, 1000);       // Execute at 500 ticks, then every 1000 ticks.
  SCH_Add_Task(yellow_red, 800, 1000);      // Execute at 800 ticks, then every 1000 ticks.
}

void loop() {
  SCH_Dispatch_Tasks();
}