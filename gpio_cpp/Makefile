CC  = arm-linux-gnueabi-g++
AS  = arm-linux-gnueabi-as
LD  = arm-linux-gnueabi-ld
BIN = arm-linux-gnueabi-objcopy
STL = st-flash
CFLAGS = -mthumb -mcpu=cortex-m3
all: io.bin
boot.o: boot.s
	$(AS) -o boot.o -g boot.s
main.o: main.cpp
	$(CC) $(CFLAGS) -c -o main.o -g main.cpp
io.elf: linker.ld boot.o main.o
	$(LD) -T linker.ld -o io.elf boot.o main.o
io.bin: io.elf
	$(BIN) -O binary io.elf io.bin
	$(STL) write io.bin 0x8000000
clean:
	rm -f *.o *.elf *.bin
flash: io.bin
	$(STL) write io.bin 0x8000000
erase:
	$(STL) erase
