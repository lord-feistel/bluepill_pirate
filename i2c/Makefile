CC  = arm-linux-gnueabi-gcc
AS  = arm-linux-gnueabi-as
LD  = arm-linux-gnueabi-ld
BIN = arm-linux-gnueabi-objcopy
STL = st-flash
CFLAGS = -mthumb -mcpu=cortex-m3
all: app.bin
crt.o: crt.s
	$(AS) -o crt.o -g crt.s
main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o -g main.c
app.elf: linker.ld crt.o main.o
	$(LD) -T linker.ld -o app.elf crt.o main.o
app.bin: app.elf
	$(BIN) -O binary app.elf app.bin
	$(STL) write app.bin 0x8000000
clean:
	rm -f *.o *.elf *.bin
flash: app.bin
	$(STL) write app.bin 0x8000000
erase:
	$(STL) erase
