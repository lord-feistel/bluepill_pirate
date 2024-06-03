#compilers
AS  = arm-linux-gnueabi-as
LD  = arm-linux-gnueabi-ld
BIN = arm-linux-gnueabi-objcopy

#comands related with openocd and debug
OPOCD = openocd
GDB = gdb-multiarch app.elf -x gdb_commands
TERMINATE = pgrep openocd | xargs kill

# comand related with st-link
STL = st-flash

# make the bin to be loaded
all: 
	$(AS) -g -mthumb io.s -o  io.out
	$(LD) -T link.ld -o io.elf io.out
	$(BIN) -O binary io.elf io.bin

#start debug
start:
	$(OPOCD) -f stlink-v2.cfg -f stm32f1x.cfg& 

# gdb
debug:	
	$(OPOCD) -f stlink-v2.cfg -f stm32f1x.cfg& 
	$(GDB)

#stop debug 
stop:
	$(TERMINATE)

# clean everything
clean:
	rm -f *.o *.elf *.bin *.out

# write binary to the flash
flash: io.bin
	$(STL) write io.bin 0x8000000

#erase microcontroller memory
erase:
	$(STL) erase
