# Arduino-Bluetooth-Car-with-Obstacle-Detection-LED-Indicators-Audible-Alarm

- Arduino Uno R3
- 1x Active Buzzer
- 1x L298N - motor driver - jumpers removed
- 2x HC-SR04 - ultrasonic sensor
- 2x Red LED
- 1x Green LED
- 4x 18650 battery
- HC-06 - bluetooth modules
PINS USED:
- IN1 (pin 7)
- IN2 (pin 8)
- IN3 (pin 12)
- IN4 (pin 13)
- ENA (pin 5)
- ENB (pin 6)
- Front TRIG (pin 4)
- Front ECHO (pin 2)
- Rear TRIG (pin 9)
- Rear ECHO (pin 10)
- LED FRONT (pin 11)
- LED REAR (pin A2)
- LED GREEN (pin A0)
- BUZZER (pin A1)

ARDUINO                        EXTERNAL COMPONENTS
=======                        ===================

5V  ──┬───────────────────────┬── VCC (both sensors)
       │                       │
       ├───────────────────────┼── Buzzer positive (if active)
       │
GND ──┼──┬────────────────────┼── GND (both sensors)
       │  │                    │
       │  ├────────────────────┼── Buzzer negative
       │  │                    │
       │  ├────[220Ω]──────────┼── Red LED Front (cathode-)
       │  │                    │
       │  ├────[220Ω]──────────┼── Red LED Rear (cathode-)
       │  │                    │
       │  └────[220Ω]──────────┼── Green LED (cathode-)
       │
Pin 4  ────────────────────────┼── Front Sensor TRIG
Pin 2  ────────────────────────┼── Front Sensor ECHO
Pin 9  ────────────────────────┼── Rear Sensor TRIG
Pin 10 ────────────────────────┼── Rear Sensor ECHO
Pin 11 ────────────────────────┼── Red LED Front (anode+)
Pin A2 ────────────────────────┼── Red LED Rear (anode+)
Pin A0 ────────────────────────┼── Green LED (anode+)
Pin A1 ────────────────────────┼── Buzzer control

FRONT SENSOR HC-SR04:
- VCC pin → Arduino 5V
- GND pin → Arduino GND
- TRIG pin → Arduino pin 4
- ECHO pin → Arduino pin 2

REAR SENSOR HC-SR04:
- VCC pin → Arduino 5V - SAME 5V as front
- GND pin → Arduino GND - SAME GND as front
- TRIG pin → Arduino pin 9
- ECHO pin → Arduino pin 10

POWER:
- Arduino has its own 2x18650 (7.4V) on VIN
- Motors have their own 2x18650 (7.4V) on L298N
- ALL GROUNDS connected: L298N GND ↔ Arduino GND

Active Buzzer (2-pin type):
- Positive (+) → Arduino pin A1
- Negative (-) → Arduino GND

- Distance readings every 2 seconds
- "⚠️ Warning beep" at 30-16cm
- Car stops and triple beep at 15cm
- LED lights up at 15cm or less
- Buzzer beeps at different rates:
  - 30-16cm: Beep every 500ms
  - 15-0cm: Beep every 200ms

Understanding the Distance Zones
#Distance	                What Happens
#> 30cm	                  Safe - no beeps
#16cm - 30cm	           ⚠️ WARNING ZONE - Beeps every 400ms
#< 15cm	                 🛑 STOP ZONE - Car stops, triple beep

Features:
- Bluetooth control	HC-06 with 'F','B','L','R','S' commands
- Obstacle detection	Front & rear HC-SR04, stops at 15cm
- Warning zone, beeps when an obstacle is at 30cm
- Red LEDs, light up when an obstacle is at 15cm
- Green LED, lights when the path is clear
- One beep at startup
- One short beep each time you press a button

Feature	                     How It Works
- LEDs	                       Red solid = STOP distance, Red blinking = warning distance, Green = all clear
- Buzzer	                     Fast beep when approaching obstacle, slow beep when stopped near obstacle
- Turn signals	               Short beep when turning
- Blocked movement	           Double beep when command is blocked
