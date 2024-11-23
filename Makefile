CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a53+nosimd

all: clean kernel8.img

start.o: src/start.S
	clang --target=aarch64-elf $(CFLAGS) -c src/start.S -o start.o

kernel8.img: start.o
	ld.lld -m aarch64elf -nostdlib start.o -T src/link.ld -o kernel8.elf
	llvm-objcopy -O binary kernel8.elf kernel8.img

clean:
	rm kernel8.elf *.o >/dev/null 2>/dev/null || true

run: kernel8.img
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -d in_asm
