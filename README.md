🔧 LED Control on Arduino — From digitalWrite() to Pure Assembly
A step-by-step guide for beginners, showing how to turn on/off the Arduino onboard LED using different levels of control.

💡 Goal
Show how to:

Control the onboard LED using:

Standard digitalWrite()

Direct register manipulation

Pure AVR assembly uploaded via browser

Understand what's happening under the hood (PORTB, DDRB, etc.)

Use costycnc.it/avr1 to compile and upload assembly without any local software

🚦 Step 1 — Arduino Style (digitalWrite)

            void setup() {
              pinMode(13, OUTPUT);
            }
            
            void loop() {
              digitalWrite(13, HIGH); // LED ON
            }
Then:

cpp
Copia
Modifica
void loop() {
  digitalWrite(13, LOW); // LED OFF
}
⚙️ Step 2 — Direct Register Access in Arduino C
cpp
Copia
Modifica
void setup() {
  _SFR_MEM8(0x24) = 0b00100000; // DDRB = 0x24, set PB5 as output
}

void loop() {
  _SFR_MEM8(0x25) = 0b00100000; // PORTB = 0x25, set PB5 high → LED ON
}
Then:

cpp
Copia
Modifica
void loop() {
  _SFR_MEM8(0x25) = 0b00000000; // LED OFF
}
📌 Explanation: Arduino is like a closet full of registers. Register 0x25 controls the onboard LED on PB5. Writing 1 turns it on, 0 turns it off.

🧠 Step 3 — Pure Assembly with Browser Compiler
Open 👉 costycnc.it/avr1

🔋 LED ON
asm
Copia
Modifica
.org 0
  rjmp init
.org 0x68
init:
  ldi r16, 0b00100000 ; set bit for PB5
  sts 0x24, r16       ; DDRB
  sts 0x25, r16       ; PORTB
  rjmp init
💡 LED OFF
asm
Copia
Modifica
.org 0
  rjmp init
.org 0x68
init:
  ldi r16, 0b00100000
  sts 0x24, r16
  ldi r16, 0
  sts 0x25, r16
  rjmp init
☑️ Compile and upload directly from the browser.
⚠️ Disconnect Arduino from serial monitor if upload doesn't start.

📽️ Demo Video


📎 Resources
costycnc.it/avr1 — Online compiler + uploader

ATmega328 Datasheet (PDF)

Register Map for ATmega328

💬 License
This project is open source under the MIT License. Feel free to reuse, fork, or modify!
