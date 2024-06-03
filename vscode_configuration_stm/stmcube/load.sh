arm-linux-gnueabi-objcopy -O binary  blink.elf blink.bin
st-flash write blink.bin 0x8000000

