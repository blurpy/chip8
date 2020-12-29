# CHIP-8 emulator

Fully functional emulator for CHIP-8 roms built with C++17 and SDL2.

Less common opcodes are not implemented (yet):

* 0NNN - Call RCA 1802 program at address NNN
* BNNN - Jumps to the address NNN plus V0
* FX0A - A key press is awaited, and then stored in VX


## Requirements

* cmake
* g++
* libsdl2-devel


## Build and run

```
$ mkdir build
$ cd build
$ cmake -G "CodeBlocks - Unix Makefiles" ..
$ make
$ ./chip8 <rom file>
```

## Links

Links I used to learn about CHIP-8.


#### Articles

* https://en.wikipedia.org/wiki/CHIP-8
* http://www.multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/
* https://austinmorlan.com/posts/chip8_emulator/
* http://www.emulator101.com/introduction-to-chip-8.html
* http://mattmik.com/files/chip8/mastering/chip8.html
* http://devernay.free.fr/hacks/chip8/C8TECH10.HTM


#### Videos

* [GynvaelEN - Hacking Livestream #34: CHIP-8 VM](https://www.youtube.com/watch?v=BQRX3owv2JI)

See also the next few videos in the series for more CHIP-8.


#### Roms

* https://github.com/stianeklund/chip8/tree/master/roms
* https://github.com/dmatlack/chip8/tree/master/roms
* https://github.com/loktar00/chip8/tree/master/roms
