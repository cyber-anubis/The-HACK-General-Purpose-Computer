// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.


// Listens to the keyboard via the KBD register
(LISTEN)
@KBD
D = M
// If (KBD == 0) then the screen should be white, otherwise go blacken the screen
@WHITE
D;JEQ
@BLACK
0;JMP



// White loop header; declaring the loop counter and n = 256*512 (resolution of the screen)
(WHITE)
@i 
M = 0
@8192
D = A
@n
M = D

// If (n-i == 0) then end the loop 
(WHITE LOOP)
@i 
D = M 
@n
D = M-D
@WHITE END
D;JEQ

// White loop body; make every pixel white
@i 
D = M 
@SCREEN
A = A + D
M = 0

//Loop counter increment 
@i 
M = M+1 
@WHITE LOOP
0;JMP

(WHITE END)
@LISTEN
0;JMP


// Black loop header; declaring the loop counter and n = 256*512 (resolution of the screen)
(BLACK)
@i 
M = 0
@8192
D = A
@n
M = D

// If (n-i == 0) then end the loop 
(BLACK LOOP)
@i 
D = M 
@n
D = M-D
@BLACK END
D;JEQ

// Black loop body; make every pixel black
@i 
D = M 
@SCREEN
A = A + D
M = -1

//Loop counter increment 
@i 
M = M+1 
@BLACK LOOP
0;JMP

(BLACK END)
@LISTEN
0;JMP
