void setup() {
  _SFR_MEM8(0x24) = 0b00100000; // DDRB = 0x24 → set PB5 as output
}

void loop() {
  _SFR_MEM8(0x25) = 0b0; // PORTB = 0x25 → PB5 high (LED ON)
}
