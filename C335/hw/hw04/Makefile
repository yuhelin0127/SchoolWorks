hw04.o : hw04.c
	gcc -c hw04.c
	gcc hw04.o -o disassember

test: hw04.o
	arm-none-eabi-as simple_asm_test_file.asm -o test.o
	arm-none-eabi-objcopy test.o -O binary --only-section=.text test.bin
	hexdump -x test.bin |sed -e 's/^[^ ]*//' > test.hex
	./disassember < test.hex > test.out
	diff test.asm test.out > test.diff

