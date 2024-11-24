SRCS = $(wildcard src/*.c)
LIBC_SRCS = $(wildcard libc/*.c)
DOOM_SRCS = $(wildcard doom/*.c)
OBJS = $(SRCS:.c=.o)
LIBC_OBJS = $(LIBC_SRCS:.c=.o)
DOOM_OBJS = $(DOOM_SRCS:.c=.o)
CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a53+nosimd

all: clean kernel8.img

src/start.o: src/start.S
	clang --target=aarch64-elf $(CFLAGS) -c src/start.S -o src/start.o

data.o: data.txt
	ld.lld -m aarch64elf -r -b binary -o data.o data.txt

%.o: %.c
	clang --target=aarch64-elf $(CFLAGS) -Ilibc -c $< -o $@

kernel8.img: src/start.o data.o $(OBJS) $(LIBC_OBJS) $(DOOM_OBJS)
	ld.lld -m aarch64elf -nostdlib src/start.o data.o $(OBJS) $(LIBC_OBJS) $(DOOM_OBJS) -T link.ld -o kernel8.elf
	llvm-objcopy -O binary kernel8.elf kernel8.img

clean:
	rm kernel8.elf *.o src/*.o libc/*.o doom/*.o >/dev/null 2>/dev/null || true

run: kernel8.img
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial stdio
