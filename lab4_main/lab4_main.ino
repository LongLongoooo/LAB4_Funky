#include <scheduler.h>
#define LED_PIN 48
#define D3 6
#define D4 7
#define D5 8
#define D6 9

// Color encoding using two pins (binary):
// 00: off
// 01: yellow
// 10: green
// 11: red

void red_green() {
  // First LED: red (11), Second LED: green (10)
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D6, LOW);
}

void red_yellow() {
  // First LED: red (11), Second LED: yellow (01)
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D5, LOW);
  digitalWrite(D6, HIGH);
}

void green_red() {
  // First LED: green (10), Second LED: red (11)
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
}

void yellow_red() {
  // First LED: yellow (01), Second LED: red (11)
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
}

int state = 0;
int counter_fixed = 8;

int counters = counter_fixed;
// Task function implementing a simple state machine
void task() {
  switch(state) {
    case 0:
      red_green();
      if(counters > 1) {
        counters--;
      } else {
        counters = 2;  // Set duration for the next state
        state++;       // Move to the next state
      }
      break;
    case 1:
      red_yellow();
      if(counters > 1) {
        counters--;
      } else {
        counters = counter_fixed;  // Duration for this state
        state++;       
      }
      break;
    case 2:
      green_red();
      if(counters > 1) {
        counters--;
      } else {
        counters = 2;
        state++;       
      }
      break;
    case 3:
      yellow_red();
      if(counters > 1) {
        counters--;
      } else {
        counters = counter_fixed;
        // Instead of incrementing further, wrap the state back to 0
        state = 0;
      }
      break;
    default:
      // Safety: reset state if out of range
      state = 0;
      counters = counter_fixed;
      break;
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
