# Project 6:
## Implementing the cross-assembler

![image](https://user-images.githubusercontent.com/33065305/77856254-3008d480-71f6-11ea-9838-2534abf30b6a.png)

Every computer has a binary machine language, in which instructions are written as series of 0's and 1's, and a symbolic machine language, also known as assembly language, in which instructions are expressed using human-friendly mnemonics. Both languages do exactly the same thing, and are completely equivalent. But, writing programs in assembly is far easier and safer then writing in binary. In order to enjoy this luxury, someone has to translate our symbolic programs into binary code that can execute as-is on the target computer. This translation service is done by an agent called assembler. The assembler can be either a person who carries out the translation manually, or a computer program that automates the process. In this module and final project in the course we learn how to build an assembler. In particular, we'll develop the capability of translating symbolic Hack programs into binary code that can be executed as-is on the Hack platform.
