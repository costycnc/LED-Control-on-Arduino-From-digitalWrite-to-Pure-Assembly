# 🔧 LED Control on Arduino — From `digitalWrite()` to Pure Assembly  
*A step-by-step guide to turn on/off the Arduino onboard LED using high-level Arduino code, direct register access, and pure AVR assembly.*

---

## 💡 Goal

This tutorial demonstrates:

- Controlling the onboard LED via:
  - `digitalWrite()` (standard Arduino)
  - Direct register manipulation
  - Pure AVR assembly (via web compiler)
- How each level gives more control and performance
- Using [costycnc.it/avr1](https://costycnc.it/avr1) to upload code **without software**

---

## 🚦 Step 1 — Arduino Style (`digitalWrite`)

```
void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH); // LED ON
}
```
Then:

```
void loop() {
  digitalWrite(13, LOW); // LED OFF
}
```
⚙️ Step 2 — Register Access in C
```
void setup() {
  _SFR_MEM8(0x24) = 0b00100000; // DDRB = 0x24 → set PB5 as output
}

void loop() {
  _SFR_MEM8(0x25) = 0b00100000; // PORTB = 0x25 → PB5 high (LED ON)
}
```
Then:
```
void loop() {
  _SFR_MEM8(0x25) = 0b00000000; // PB5 low → LED OFF
}
```
📌 Explanation:
Arduino is like a closet full of registers. Address 0x25 controls PORTB, where bit 5 (PB5) is linked to the onboard LED. Writing 1 turns it on, 0 turns it off.

🧠 Step 3 — Pure Assembly (AVR) via Browser
Open 👉 https://costycnc.it/avr1

🔋 LED ON

```
.org 0
  rjmp init
.org 0x68
init:
  ldi r16, 0b00100000 ; bit for PB5
  sts 0x24, r16       ; DDRB
  sts 0x25, r16       ; PORTB
  rjmp init
```
💡 LED OFF
```
.org 0
  rjmp init
.org 0x68
init:
  ldi r16, 0b00100000
  sts 0x24, r16
  ldi r16, 0
  sts 0x25, r16
  rjmp init
```
☑️ Compile and upload directly from the browser.
⚠️ Disconnect Arduino from serial monitor if the upload fails.

🎥 Demo Video


📎 Resources
🔗 costycnc.it/avr1 — Online compiler/uploader

📘 ATmega328P Datasheet (PDF)

🧠 AVR Register Map (AVR libc)

📜 License
MIT License. Feel free to fork, share, and contribute!
