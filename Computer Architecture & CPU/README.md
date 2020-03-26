# Project 5:
Let's recap the last four projects: we've built some elementary logic gates (project 1), and then used them to build an ALU (project 2) and a RAM (project 3). We then played with low-level programming (project 4), assuming that the overall computer is actually available. In this project we assemble all these building blocks into a general-purpose 16-bit computer called Hack. We will start by building the Hack Central Processing Unit (CPU), and we will then integrate the CPU with the RAM, creating a full-blown computer system capable of executing programs written in the Hack machine language.

### The Hack Hardware Platform Specification

![image](https://user-images.githubusercontent.com/33065305/77665538-7c4edd00-6f88-11ea-93c8-13694be5dc54.png)

The Hack platform is a 16-bit von Neumann machine, consisting of a CPU, two separate memory modules serving as instruction memory and data memory, and two memory-mapped I/O devices: a screen and a keyboard.
The Hack computer executes programs that reside in its instruction memory. The instruction memory is a read-only device, and thus programs are loaded into it using some exogenous means. For example, the instruction memory can be implemented in a ROM chip that is preburned with the required program. Loading a new program can be done by replacing the entire ROM chip. In order to simulate this operation, hardware simulators of the Hack platform must provide a means for loading the instruction memory from a text file containing a program written in the Hack machine language.

## CPU Abstraction
The CPU of the Hack platform is designed to execute 16-bit instructions according to the Hack machine language specified in chapter 4. It expects to be connected to two separate memory modules: an instruction memory, from which it fetches instructions for execution, and a data memory, from which it can read, and into which it can write, data values.

![image](https://user-images.githubusercontent.com/33065305/77665683-aa342180-6f88-11ea-8ede-3e37342757fd.png)

## CPU Implementation
The CPU implementation objective is to create a logic gate architecture capable of
executing a given Hack instruction and fetching the next instruction to be executed.Naturally, the CPU will include an ALU capable of executing Hack instructions, a
set of registers, and some control logic designed to fetch and decode instructions.
Since almost all these hardware elements were already built in previous chapters, the
key question here is how to connect them in order to effect the desired CPU operation.
The key element missing in figure 5.9 is the CPU’s control logic, designed to perform
the following tasks:
* **Instruction decoding:** Figure out what the instruction means (a function of the
instruction).
* **Instruction execution:** Signal the various parts of the computer what they should
do in order to execute the instruction (a function of the instruction).
* **Next instruction fetching:** Figure out which instruction to execute next (a function
of the instruction and the ALU output).

![image](https://user-images.githubusercontent.com/33065305/77665776-c6d05980-6f88-11ea-9b9e-e98862fd12c9.png)

## RAM Unit
### Instruction Memory
The Hack instruction memory is implemented in a direct-access Read-Only Memory device, also called ROM. The Hack ROM consists of 32K addressable 16-bit registers.
### Data Memory
Hack’s data memory chip has the interface of a typical RAM device, like that built in project 3. To read the contents of register n, we put n in the memory’s address input and probe the memory’s out output. This is a combinational operation, independent of the clock. To write a value v into register n, we put v in the in input, n in the address input, and assert the memory’s load bit. This is a sequential operation, and so register n will commit to the new value v in the next clock cycle.
In addition to serving as the computer’s general-purpose data store, the data memory also interfaces between the CPU and the computer’s input/output devices,using memory maps.

![image](https://user-images.githubusercontent.com/33065305/77665891-eebfbd00-6f88-11ea-9a85-62042afc872b.png)


## Computer Architecture
Once the CPU and the Memory chips have been implemented and tested, the construction
of the overall computer is straightforward
![image](https://user-images.githubusercontent.com/33065305/77666059-23cc0f80-6f89-11ea-835e-e41001237c3e.png)


