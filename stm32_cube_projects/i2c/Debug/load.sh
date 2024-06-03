arm-linux-gnueabi-objcopy -O binary  i2c.elf i2c.bin
st-flash write i2c.bin 0x8000000

