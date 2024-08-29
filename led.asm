; avr-as -mmcu=atmega328p -o led.o led.asm
; avr-ld -m avr5 --section-start=.text=0x0000 -o led.bin led.o
; avr-objcopy -O ihex -R .eeprom led.bin led.hex
; avrdude -F -V -c arduino -p ATMEGA328P -P COM6 -b 115200 -U flash:w:led.hex

	.global main
	.text
main:
	; DDRB |= (1 << DDB5)

	sbi  0x4, 5

loop:
	; PORTB |=  (1 << PORTB5);

	sbi  0x5, 5

	; _delay_ms(1000)

	ldi  r16, .exb 3199999 0
	ldi  r17, .exb 3199999 1
	ldi  r18, .exb 3199999 2
1:	subi r16, 1
	sbci r17, 0
	sbci r18, 0
	brne 1b
	rjmp .
	nop

	; PORTB &= ~(1 << PORTB5);

	cbi  0x5, 5

	; _delay_ms(1000);

	ldi  r16, .exb 3199999 0
	ldi  r17, .exb 3199999 1
	ldi  r18, .exb 3199999 2
1:	subi r16, 1
	sbci r17, 0
	sbci r18, 0
	brne 1b
	rjmp .
	nop

	rjmp loop
