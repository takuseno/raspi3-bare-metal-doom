# Bare Metal Doom for Raspberry Pi 3

This project is aiming to run Doom on Raspberry Pi 3 with bare metal programming.

- `libc`: The original (and heavily simplified) standard C library for this bare metal programming.
- `src`: Raspberry Pi 3-related codes based on [raspi3-tutorial](https://github.com/bztsrc/raspi3-tutorial).
- `doom`: Custom Doom codes based on [doomgeneric](https://github.com/ozkl/doomgeneric).

Keyboard inputs are mapped to UART interface.
- `\n`: Enter.
- `a`: Left.
- `d`: Right.
- `s`: Down.
- `w`: Up.
- `f`: Fire.
- `u`: Use.
- `o`: Escape.

## Development with QEMU
### Preparation
This Docker container installs dependencies necessary to cross-compile programs for 64bit ARM.
```
# build Docker container for development
bin/build-docker

# download DOOM game data
bin/download-doom1-wad
```

### Build and execute Doom
Once the program is built successfully, you should be able to see QEMU window as follows:
```
bin/run
```
![image](https://github.com/user-attachments/assets/397f1f97-31ec-4243-a03a-00cb195b8e73)

### Clean
Clean up object files and binaries.
```
bin/clean
```

## Run with Raspberry Pi 3
:warning: Currently, there is an issue with the real hardware even though it works perfectly on the simulator. Issues are:
- During a demo, when the player gets an armor, the game hangs.
- When keyboard inputs are detected, the game hangs.

These require additional investigation to make things work. But, at least, you can see that the program runs on the real hardware.

### Prepare micro SD card
You need to format a micro SD card as FAT32.

### Download firmware
You can download minimal firmware as follows:
```
bin/download-firmware
```
You will see downloaded files under `firmware` directory.

### Copy everything to the micro SD card
Copy the following files to the root place of the micro SD card:
- bootcode.bin
- start.elf
- fixup.dat
- kernel8.img (this needs to be created by executing `bin/run`)

### Boot Raspberry Pi 3
Now, you can boot Raspberry Pi 3 by connecting a power cable.
