# Bare Metal Doom for Raspberry Pi 3

This project is aiming to run Doom on Raspberry Pi 3 with bare metal programming.

- `libc`: The original (and heavily simplified) standard C library for this bare metal programming.
- `src`: Raspberry Pi 3-related codes based on [raspi3-tutorial](https://github.com/bztsrc/raspi3-tutorial).
- `doom`: Custom Doom codes based on [doomgeneric](https://github.com/ozkl/doomgeneric).

⚠️ Currently, there is no controller/keyboard support to play the game. I don't have much interest to support this because my goal was to learn bare metal programming. If you want, the easiest way would be to wire UART and Doom's keyboard handler.

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
