// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Variables declrations:
// i is the iteration counter in the loop
// n = R0 (number of iterations)
@sum	
M = 0
@i		 
M = 0
@R0
D = M
@n		
M = D	


// Loop header and base case
(LOOP)
@i
D = M
@n 
D = D-M 
@END
D;JEQ	
//jump if (n-i == 0)

// Loop body where we accumulate n times of R1: sum = sum +D
@R1
D = M 
@sum	
M = M + D

// Incrementing the loop counter
@i
D = M 
M = D+1
@LOOP
0;JMP 

(END)	
// storing the sum at R1 then exiting the program
@sum
D = M
@R2
M = D

(TERMINATE)
@TERMINATE
0;JMP