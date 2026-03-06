# Arduino-Bluetooth-Car-with-Obstacle-Detection-LED-Indicators-Audible-Alarm

- IMPORTANT  -  !!! Remember to disconnect Bluetooth from pins 0/1 whenever you upload new code.  !!!
- IMPORTANT  -  !!! Always connect grounds together - This is the only critical connection between the two power systems.  !!!
- Recommended App - 

- Arduino Uno R3
- 1x Active Buzzer
- 1x L298N - motor driver - jumpers removed
- 2x HC-SR04 - ultrasonic sensor
- 2x Red LED
- 1x Green LED
- 4x 18650 battery
- HC-06 - Bluetooth modules
- 3x 220Ω resistors
- Small breadboard
- 4x TT Motors (3-6V)

- 
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

- ARDUINO                        EXTERNAL COMPONENTS
- =======                        ===================

<img width="394" height="408" alt="image" src="https://github.com/user-attachments/assets/31fbd2cc-3e1f-4ca4-95bd-a9f300144b70" />


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

HC-06:
- TXD → RX (pin 0)	Data goes from Bluetooth TO Arduino
- RXD → TX (pin 1)	Data goes from Arduino TO Bluetooth
- VCC → Arduino 5V
- GND → Arduino GND

L298N Jumper Settings
- Jumper	                            Correct Setting for Your Setup
- ENA	                                   REMOVED (you have wire to Arduino pin 5)
- ENB          	                     REMOVED (you have wire to Arduino pin 6)
- 5V Enable (near power terminals)	       ON (kept in place) - this powers L298N internal logic

- The ENA and ENB pins on the L298N control whether the motor channels are enabled. When you remove the jumpers:
- The pins are no longer connected to 5V internally
- You connect these pins to Arduino PWM pins (like pins 5 and 6 in our code)
- You can then use analogWrite() to set any speed from 0-255
- This is clearly explained in several sources: with jumpers installed, motors run at maximum speed; with jumpers removed and connected to PWM pins, you get full speed control

- Jumpers ON (default) - Motors run at FULL speed whenever direction pins are set - Simple on/off control, no speed variation
- Jumpers OFF - Motors can run at variable speeds using PWM from Arduino - Speed control, smoother starts/stops, battery saving

Active Buzzer (2-pin type):
- Positive (+) → Arduino pin A1
- Negative (-) → Arduino GND

Motors Connection
- L298N Terminal	            Connection Target	                       How to Connect
- OUT1	                          Left Motor 1 (e.g., front-left)	         Connect to either one of the motor's terminals.
- OUT2	                          Left Motor 1 (e.g., front-left)	         Connect to the motor's other terminal.
- OUT1 (same as above)	     Left Motor 2 (e.g., rear-left)	         Bridge (connect) this terminal to the same terminal on Left Motor 2.
- OUT2 (same as above)	     Left Motor 2 (e.g., rear-left)	         Bridge (connect) this terminal to the same terminal on Left Motor 2.
- OUT3	                          Right Motor 1 (e.g., front-right)	         Connect to either one of the motor's terminals.
- OUT4	                          Right Motor 1 (e.g., front-right)	         Connect to the motor's other terminal.
- OUT3 (same as above)	     Right Motor 2 (e.g., rear-right)	         Bridge (connect) this terminal to the same terminal on Right Motor 2.
- OUT4 (same as above)	     Right Motor 2 (e.g., rear-right)	         Bridge (connect) this terminal to the same terminal on Right Motor 2.

The L298N module is designed with two independent channels, each capable of driving one DC motor . To drive four motors, you simply connect two motors to each channel in parallel. This means the two motors on the left side of your car will share one channel, and the two on the right will share the other.
- Channel A (Left Side): Connects to the two left-side motors.
- Channel B (Right Side): Connects to the two right-side motors.

MOTORS TO L298N:
- Left Motor  ────> OUT1 and OUT2
- Right Motor ────> OUT3 and OUT4

MOTOR POWER (2× 18650):
- [+] ────┬────────────────> L298N 12V terminal
- [-] ────┴────────────────> L298N GND terminal

ARDUINO POWER (2× 18650):
- [+] ─────────────────────> Arduino VIN pin
- [-] ─────────────────────> Arduino GND pin

Component	       Power Source	          Voltage	                 Result
- TT Motors (4x)	2× 18650 in series	   7.4V (8.4V max)	          Slightly overvoltage but very common - motors will run faster with good torque
- Arduino	       2× 18650 in series	   7.4V (8.4V max)	          Perfect for VIN pin (accepts 6-12V)

- Distance readings every 2 seconds
- "⚠️ Warning beep" at 30-16cm
- Car stops and triple beep at 15cm
- LED lights up at 15cm or less
- Buzzer beeps at different rates:
  - 30-16cm: Beep every 500ms
  - 15-0cm: Beep every 200ms

Understanding the Distance Zones
- Distance	                What Happens
- > 30cm	                Safe - no beeps
- 16cm - 30cm	               ⚠️ WARNING ZONE - Beeps every 400ms
- < 15cm	               🛑 STOP ZONE - Car stops, triple beep

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

Behavior Summary
- Situation	                                      Car Reaction
- Clear path forward	                               Moves normally
- Object appears in front while moving	          Immediate stop
- Object behind while reversing	                 Immediate stop
- Trying to move forward into the obstacle	   Won't move
- Turning	                                      Ignores sensors (assumes driver sees path)

Understanding Sensor Readings
- Distance Reading	                         What It Means
- 0-2cm	                                Too close - sensor can't measure accurately
- 3-15cm	                                DANGER ZONE - car will stop
- 16-400cm	                                Safe - car can move
- 999	                                       No obstacle detected (timeout)
