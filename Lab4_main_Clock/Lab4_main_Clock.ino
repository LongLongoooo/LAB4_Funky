#include <scheduler.h>
#define LED_PIN 48
#define D3 6
#define D4 7
#define D5 8
#define D6 9
#define D7 10
#define D8 17
#define D9 18
#define D10 21

// Color encoding using two pins (binary):
// 00: off
// 01: yellow
// 10: green
// 11: red
int light = 0;
int secondsperLight = 5;

int counters = secondsperLight;
// Task function implementing a simple state machine
void task() {
  switch(light){
    case 0:
    digitalWrite(D3, LOW);
    digitalWrite(D4, HIGH);
    if(counters > 1){
      counters--;
    } else{
      counters = secondsperLight;
      light++;
    }
    break;

    case 1:
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH);
    if(counters > 1){
      counters--;
    } else{
      counters = secondsperLight;
      light++;
      
    }
    break;

    case 2:
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);
    digitalWrite(D5, HIGH);
    digitalWrite(D6, HIGH);
    if(counters > 1){
      counters--;
    } else{
      counters = secondsperLight;
      light++;
    }
    break;

    case 3:
    digitalWrite(D5, LOW);
    digitalWrite(D6, HIGH);
    if(counters > 1){
      counters--;
    } else{
      counters = secondsperLight;
      light++;
    }
    break;

    case 4:
    digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);
    if(counters > 1){
      counters--;
    } else{
      counters = secondsperLight;
      light++;
    }
    break;

    case 5:
    digitalWrite(D5, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(D7, HIGH);
    digitalWrite(D8, HIGH);
    if(counters > 1){
      counters--;
    } else{
      counters = secondsperLight;
      light++;
    }
    break;

    case 6:
    digitalWrite(D7, LOW);
    digitalWrite(D8, HIGH);
    if(counters > 1){
      counters--;
    } else{
      counters = secondsperLight;
      light++;
    }
    break;

    case 7:
    digitalWrite(D7, HIGH);
    digitalWrite(D8, LOW);
    if(counters > 1){
      counters--;
    } else{
      counters = secondsperLight;
      light++;
    }
    break;

    case 8:
    digitalWrite(D7, LOW);
    digitalWrite(D8, LOW);
    digitalWrite(D9, HIGH);
    digitalWrite(D10, LOW);
    if(counters > 1){
      counters--;
    } else{
      counters = secondsperLight;
      light++;
    }
    break;

    case 9:
    digitalWrite(D9, LOW);
    digitalWrite(D10, HIGH);
    if(counters > 1){
      counters--;
    } else{
      counters = secondsperLight;
      light++;
    }
    break;

    case 10:
    digitalWrite(D9, HIGH);
    digitalWrite(D10, HIGH);
    if(counters > 1){
      counters--;
    } else{
      counters = secondsperLight;
      light++;
    }
    break;

    case 11:
    digitalWrite(D9, LOW);
    digitalWrite(D10, LOW);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, LOW);
    if(counters > 1){
      counters--;
    } else{
      counters = secondsperLight;
      light = 0;
    }
    break;

    default:
    light = 0;
    counters = secondsperLight;
    
  }
}

void TIMER_ISR(void *pvParameters) {
  while(1) {
    SCH_Update();
    vTaskDelay(10);
  }
}

void setup() {
  // Initialize the digital pins.
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(D9, OUTPUT);
  pinMode(D10, OUTPUT);
  // Uncomment if you decide to use LED_PIN for other purposes.
  // pinMode(LED_PIN, OUTPUT);

  // Create the task that updates the scheduler (simulated timer ISR).
  xTaskCreate(TIMER_ISR, "TIMER_ISR", 2048, NULL, 2, NULL);

  // Initialize and add the main task to the scheduler.
  SCH_Init();
  SCH_Add_Task(task, 0, 100);
}

void loop() {
  // Dispatch scheduled tasks.
  SCH_Dispatch_Tasks();
}
