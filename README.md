# The-HACK-General-Purpose-Computer

> **What I hear, I forget; What I see, I remember; What I do, I understand.
—Confucius, 551–479 BC**

The Nand to Tetris project is about going into fascinating voyage of discovery in which I go all the way from Boolean algebra and elementary logic gates to building a <ins>**Central Processing Unit**</ins>, a memory system, and a hardware platform, leading up to a <ins>****general-purpose computer****</ins> that can run any program that you fancy.
This is typically the hardware part of the overall project which relies on many sub-projects waiting to be assembled togther. 

There is no need for physical materials, since I build the computer on my own PC, using a software-based hardware simulator, just like real computers are designed by computer engineers in the field.

In the second part of the overall project: we build a modern <ins>**software hierarchy**</ins>, designed to enable the translation and execution of object-based, high-level languages on a bare-bone computer hardware platform.

In particular, I will implement a <ins>**virtual machine**</ins> and a <ins>**compiler**</ins> for a simple, Java-like programming language, and I will develop a basic <ins>**operating system**</ins> that closes gaps between the high-level language and the underlying hardware platform.

During the process, gaining a deep, hands-on understanding of numerous topics in applied computer science, <ins>e.g. stack processing, parsing, code generation, and classical algorithms and data structures for memory management, vector graphics, input-output handling</ins>, and various other topics that lie at the very core of every modern computer system.

## What is going on here in a nutshell?

![overview](https://user-images.githubusercontent.com/33065305/77091388-25d62180-6a11-11ea-841e-331e6df59f40.png)
* **Hardware:** Logic gates, Boolean arithmetic, multiplexors, flip-flops, registers,
RAM units, counters, Hardware Description Language (HDL), chip simulation and
testing.
* **Architecture:** ALU/CPU design and implementation, machine code, assembly
language programming, addressing modes, memory-mapped input/output (I/O).
* **Operating systems:** Memory management, math library, basic I/O drivers,
screen management, file I/O, high-level language support.
* **Programming languages:** Object-based design and programming, abstract data
types, scoping rules, syntax and semantics, references.
* **Compilers:** Lexical analysis, top-down parsing, symbol tables, virtual stackbased
machine, code generation, implementation of arrays and objects.
* **Data structures and algorithms:** Stacks, hash tables, lists, recursion, arithmetic
algorithms, geometric algorithms, running time considerations.
* **Software engineering:** Modular design, the interface/implementation paradigm,
API design and documentation, proactive test planning, programming at the large,
quality assurance.


## Todo list:
Sub-projects in real-time progress.
### Computer Hardware & Architecture
* 1-**Elementary Logic Gates:**:heavy_check_mark: Building elementary logic gates like And, Or, Not, Multiplexor, and more 
* 2-**Adders Family & ALU:**:heavy_check_mark: Building a family of adder chips, culminating in the construction of an Arithmetic Logic Unit (ALU)  
* 3-**Memory Units:**:heavy_check_mark: Building registers and memory units, culminating in the construction of a Random Access Memory (RAM)  
* 4-**HACK Machine Language:**:heavy_check_mark: Learning a machine language and using it to write some illustrative low-level programs 
* 5-**Computer Architecture & CPU:**:heavy_check_mark: Using the chipset built in projects 1-3 to build a Central Processing Unit (CPU) and a hardware platform capable of executing programs written in the machine language introduced in project 4.
### Computer Software Hierarchy
* 6-**HACK Assembler:**:heavy_check_mark: Developing an assembler, i.e. a capability to translate programs written in symbolic machine language into binary, executable code.
* 7-**Virtual Machine I: (Stack Arithmetic)**:heavy_check_mark: Building a stack-based virtual machine. This implementation, in turn, will serve as the backend module of the two-tier compiler that will be developed later. In this first part, stack-based arithmetic operations & memory access operations will be handled.
* 8-**Virtual Machine II: (Program Control)**:heavy_check_mark:  In this project I'll complete the VM translator by implementing the remaining VM language's branching and function-calling commands. Implementing concepts like: program flow (if statments), loops (while), function calling (stack frame saving & retrieving) ...etc.
* 9-**High-Level Language:**:heavy_check_mark: Designing and creating the JACK high level programming language; object-based Java-like language. Implemented concepts: procedural programming, object-based programming, classes, methods, functions, constructors, list processing, recursion, developing interactive applications (**Hell Arena Game**), graphics optimization.
* 10-**Compiler I: (Syntax Analysis)**:heavy_check_mark: Creating the two-tier complier for the JACK high level language. Syntax analysis consists of two sub-stages: lexical analysis (also called tokenizing), and parsing. The result will be a Jack analyzer - a program that unveils the syntax of Jack programs without generating executable code. Key concepts: tokenizing, grammars, parsing, parse trees, XML / mark-up, compilation.
* 11-**Compiler II: (Code Generation)**:hourglass_flowing_sand: Finalizing the compiler for the JACK high level language. I'll morph the previous analyzer into a full-scale Jack compiler. Generating VM code that translates procedural programs into VM programs, and how to generate VM code for constructing and manipulating arrays and objects. Key concepts: compiling procedural code, compiling the construction and manipulation of arrays and objects, code generation techniques, recursive compilation engine, symbol tables, memory management.
* 12-**More fun to go?:** Implementing full but simple Operating system for the HACK computer.
