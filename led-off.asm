.org 0
  rjmp init
.org 0x68
init:
  ldi r16, 0b00100000
  sts 0x24, r16
  ldi r16, 0
  sts 0x25, r16
  rjmp init
