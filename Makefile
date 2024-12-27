SRCS = $(wildcard src/*.c)
LIBC_SRCS = $(wildcard libc/*.c)
DOOM_SRCS = $(wildcard doom/*.c)
OBJS = $(SRCS:.c=.o)
LIBC_OBJS = $(LIBC_SRCS:.c=.o)
DOOM_OBJS = $(DOOM_SRCS:.c=.o)
CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles -fno-stack-protector

all: clean kernel8.img

src/start.o: src/start.S
	aarch64-elf-gcc $(CFLAGS) -c src/start.S -o src/start.o

doom1wad.o: doom1.wad
	aarch64-elf-ld -r -b binary -o doom1wad.o doom1.wad

%.o: %.c
	aarch64-elf-gcc $(CFLAGS) -Ilibc -c $< -o $@

kernel8.img: src/start.o doom1wad.o src/link.ld $(OBJS) $(LIBC_OBJS) $(DOOM_OBJS)
	aarch64-elf-ld -nostdlib -nostartfiles src/start.o doom1wad.o $(OBJS) $(LIBC_OBJS) $(DOOM_OBJS) -T src/link.ld -o kernel8.elf
	aarch64-elf-objcopy -O binary kernel8.elf kernel8.img

clean:
	rm kernel8.elf *.o src/*.o libc/*.o doom/*.o >/dev/null 2>/dev/null || true

run: kernel8.img
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial mon:stdio --no-reboot
