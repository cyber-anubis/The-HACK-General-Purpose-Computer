# Project 4:
![image](https://user-images.githubusercontent.com/33065305/77532669-f8202b00-6e9d-11ea-9ba6-ea1b6e1d0fba.png)

**A critically important aspect of building a new computer system is designing the low-level machine language, or instruction set, with which the computer can be instructed to do various things.
The Hack computer is a von Neumann platform. It is a 16-bit machine, consisting of a CPU, two separate memory modules serving as instruction memory and data memory, and two memory-mapped I/O devices: a screen and a keyboard.**

![image](https://user-images.githubusercontent.com/33065305/77532608-dd4db680-6e9d-11ea-9f2e-b572201de67e.png)

## Memory Address Spaces
The Hack programmer is aware of two distinct address
spaces: an instruction memory and a data memory. Both memories are 16-bit wide and have a 15-bit address space, meaning that the maximum addressable size of each memory is 32K 16-bit words. The CPU can only execute programs that reside in the instruction memory. The instruction memory is a read-only device, and programs are loaded into it using some exogenous means. For example, the instruction memory can be implemented in a ROM chip that is pre-burned with the required program. Loading a new program is done by replacing the entire ROM chip, similar to replacing a cartridge in a game console. In order to simulate this operation, hardware simulators of the Hack platform must provide a means to load the instruction memory from a text file containing a machine language program.

**Registers**  The Hack programmer is aware of two 16-bit registers called D and A. These registers can be manipulated explicitly by arithmetic and logical instructions like A=D-1 or D=!A (where ‘‘!’’ means a 16-bit Not operation). While D is used solely to store data values, A doubles as both a data register and an address register. That is to say, depending on the instruction context, the contents of A can be interpreted either as a data value, or as an address in the data memory, or as an address in the instruction memory, as we now explain.
![image](https://user-images.githubusercontent.com/33065305/77532498-a1b2ec80-6e9d-11ea-90e1-c8e8c424005e.png)

![image](https://user-images.githubusercontent.com/33065305/77530460-0b30fc00-6e9a-11ea-973e-b4d9c3b33f47.png)

![image](https://user-images.githubusercontent.com/33065305/77530671-62cf6780-6e9a-11ea-8533-252e2da8a122.png)

## Input/Output Handling
The Hack platform can be connected to two peripheral devices: a screen and a keyboard. Both devices interact with the computer platform through memory maps. This means that drawing pixels on the screen is achieved by writing binary values into a memory segment associated with the screen. Likewise, listening to the keyboard is done by reading a memory location associated with the keyboard. The physical I/O devices and their memory maps are synchronized via continuous refresh loops.

**Screen** The Hack computer includes a black-and-white screen organized as 256 rows of 512 pixels per row. The screen’s contents are represented by an 8K memory map that starts at RAM address 16384 (0x4000). Each row in the physical screen, starting at the screen’s top left corner, is represented in the RAM by 32 consecutive 16-bit words. Thus the pixel at row r from the top and column c from the left is mapped on the c%16 bit (counting from LSB to MSB) of the word located at RAM[16384 + r * 32 + c/16]. To write or read a pixel of the physical screen, one reads or writes the corresponding bit in the RAM-resident memory map (1 = black, 0 = white). Example:

// Draw a single black dot at the screen's top left corner:
@SCREEN // Set the A register to point to the memory
// word that is mapped to the 16 left-most
// pixels of the top row of the screen.
M=1 // Blacken the left-most pixel.

**Keyboard** The Hack computer interfaces with the physical keyboard via a single-word memory map located in RAM address 24576 (0x6000). Whenever a key is pressed on the physical keyboard, its 16-bit ASCII code appears in RAM[24576]. When no key is pressed, the code 0 appears in this location. In addition to the usual ASCII codes, the Hack keyboard recognizes a lot more keys.

![image](https://user-images.githubusercontent.com/33065305/77532153-face5080-6e9c-11ea-8905-0ef7e722ab71.png)
