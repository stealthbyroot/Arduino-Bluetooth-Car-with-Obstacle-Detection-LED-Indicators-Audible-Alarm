/*
 * Arduino-Bluetooth-Car-with-Obstacle-Detection-LED-Indicators-Audible-Alarm
 * https://github.com/stealthbyroot/Arduino-Bluetooth-Car-with-Obstacle-Detection-LED-Indicators-Audible-Alarm
 */

// Motor pins
int IN1 = 7;      // Left motor control 1
int IN2 = 8;      // Left motor control 2
int IN3 = 12;     // Right motor control 1
int IN4 = 13;     // Right motor control 2
int ENA = 5;      // Left motor speed (PWM - safe)
int ENB = 6;      // Right motor speed (PWM - safe)

// Sensor pins
#define FRONT_TRIG 4
#define FRONT_ECHO 2
#define REAR_TRIG 9
#define REAR_ECHO 10

// LED pins
#define LED_FRONT 11
#define LED_REAR A2
#define LED_CLEAR A0

// BUZZER pin
#define BUZZER A1

int SAFE_DISTANCE = 15;
int WARNING_DISTANCE = 30;

bool movingForward = false;
bool movingBackward = false;

void setup() {
  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  // Sensor pins
  pinMode(FRONT_TRIG, OUTPUT);
  pinMode(FRONT_ECHO, INPUT);
  pinMode(REAR_TRIG, OUTPUT);
  pinMode(REAR_ECHO, INPUT);
  
  // LED pins
  pinMode(LED_FRONT, OUTPUT);
  pinMode(LED_REAR, OUTPUT);
  pinMode(LED_CLEAR, OUTPUT);
  
  // Buzzer pin
  pinMode(BUZZER, OUTPUT);
  
  // Set motor speed
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  
  Serial.begin(9600);
  Serial.println("FINAL VERSION - Car moves AND beeps!");
  
  // Test buzzer
  tone(BUZZER, 1000, 500);
  delay(500);
}

void loop() {
  int frontDist = getDistance(FRONT_TRIG, FRONT_ECHO);
  int rearDist = getDistance(REAR_TRIG, REAR_ECHO);
  
  // Update LEDs
  digitalWrite(LED_FRONT, (frontDist < SAFE_DISTANCE && frontDist > 0));
  digitalWrite(LED_REAR, (rearDist < SAFE_DISTANCE && rearDist > 0));
  
  bool allClear = (frontDist > WARNING_DISTANCE || frontDist <= 0) && 
                  (rearDist > WARNING_DISTANCE || rearDist <= 0);
  digitalWrite(LED_CLEAR, allClear);
  
  // Check Bluetooth
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    
    // Command beep - short
    tone(BUZZER, 1200, 50);
    
    switch(cmd) {
      case 'F':
        if (frontDist >= SAFE_DISTANCE) {
          forward();
          movingForward = true;
          movingBackward = false;
          Serial.println("FORWARD");
        } else {
          stopCar();
          Serial.println("FORWARD BLOCKED");
        }
        break;
        
      case 'B':
        if (rearDist >= SAFE_DISTANCE) {
          backward();
          movingForward = false;
          movingBackward = true;
          Serial.println("BACKWARD");
        } else {
          stopCar();
          Serial.println("BACKWARD BLOCKED");
        }
        break;
        
      case 'L':
        left();
        movingForward = false;
        movingBackward = false;
        Serial.println("LEFT");
        break;
        
      case 'R':
        right();
        movingForward = false;
        movingBackward = false;
        Serial.println("RIGHT");
        break;
        
      case 'S':
        stopCar();
        movingForward = false;
        movingBackward = false;
        Serial.println("STOP");
        break;
    }
  }
  
  // Obstacle detection
  if (movingForward && frontDist < SAFE_DISTANCE && frontDist > 0) {
    stopCar();
    movingForward = false;
    Serial.println("OBSTACLE - STOP");
    // Triple beep
    tone(BUZZER, 800, 200);
    delay(250);
    tone(BUZZER, 800, 200);
    delay(250);
    tone(BUZZER, 800, 200);
  }
  
  if (movingBackward && rearDist < SAFE_DISTANCE && rearDist > 0) {
    stopCar();
    movingBackward = false;
    Serial.println("OBSTACLE - STOP");
    tone(BUZZER, 800, 200);
    delay(250);
    tone(BUZZER, 800, 200);
    delay(250);
    tone(BUZZER, 800, 200);
  }
  
  // Warning beeps
  static unsigned long lastBeep = 0;
  
  if (movingForward && frontDist < WARNING_DISTANCE && frontDist > SAFE_DISTANCE) {
    if (millis() - lastBeep > 500) {
      tone(BUZZER, 2000, 100);
      lastBeep = millis();
      Serial.println("WARNING BEEP");
    }
  }
  
  if (movingBackward && rearDist < WARNING_DISTANCE && rearDist > SAFE_DISTANCE) {
    if (millis() - lastBeep > 500) {
      tone(BUZZER, 2000, 100);
      lastBeep = millis();
      Serial.println("WARNING BEEP");
    }
  }
  
  delay(10);
}

int getDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH, 10000);
  if (duration == 0) return 999;
  return duration * 0.034 / 2;
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}