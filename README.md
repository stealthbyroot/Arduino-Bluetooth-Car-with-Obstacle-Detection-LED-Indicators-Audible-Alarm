# Arduino-Bluetooth-Car-with-Obstacle-Detection-LED-Indicators-Audible-Alarm

- Arduino Uno R3
- Active Buzzer
- L298N - motor driver - jumpers removed
- 
IN1 (pin 7)
IN2 (pin 8)
IN3 (pin 12)
IN4 (pin 13)
ENA (pin 5)
ENB (pin 6)
Front TRIG (pin 4)
Front ECHO (pin 2)
Rear TRIG (pin 9)
Rear ECHO (pin 10)
LED FRONT (pin 11)
LED REAR (pin A2)
LED GREEN (pin A0)
BUZZER (pin A1)

FRONT SENSOR:
VCC pin → Arduino 5V
GND pin → Arduino GND
TRIG pin → Arduino pin 4
ECHO pin → Arduino pin 2

REAR SENSOR:
VCC pin → Arduino 5V - SAME 5V as front
GND pin → Arduino GND - SAME GND as front
TRIG pin → Arduino pin 9
ECHO pin → Arduino pin 10

POWER:
[ ] Arduino has its own 2x18650 (7.4V) on VIN
[ ] Motors have their own 2x18650 (7.4V) on L298N
[ ] ALL GROUNDS connected: L298N GND ↔ Arduino GND

Distance readings every 2 seconds
"⚠️ Warning beep" at 30-16cm
Car stops and triple beep at 15cm
