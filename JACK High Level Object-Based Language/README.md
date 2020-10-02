# Project 9
## Hell Arena Game


The purpose of this project is to develop a full application using JACK language capabilities in order to gain a full understanding of the language syntax and use. That's because this makes the process of implementing the compiler much easier. You must understand the language syntax, grammar, expression evaluation, procedural units, control flow, and so on in order to write a compiler that can parse this high-level text and translate them. 

![hell01](https://user-images.githubusercontent.com/33065305/94924618-2a01f200-04be-11eb-85f8-c871be27d644.png)

As this simple welcome menu says, the mission of this game is to survive not to fight.

![hell02](https://user-images.githubusercontent.com/33065305/94924640-38500e00-04be-11eb-9c64-377aa4d3bfbc.png)

The characters and graphics build in this game were constructed using a simple bitmap object. Each object is 16x16 bits in memory which is just 16 words. Tweaking these words with the proper value will result in creating the desired graphics.

![hell03](https://user-images.githubusercontent.com/33065305/94925059-ea87d580-04be-11eb-91f5-56c3ecc77c84.png)

### Game implementation:
The game consists of 3 modules and main module as follows:
* 1-**Main:**: Responsible for constructing main objects and running the game.  
* 2-**Menu**: Responsible for creating the menu window to welcome the player and stating the game rules.
* 3-**Character**: Responsible for the attributes and functionality of the characters of the game such as moving and so on.
* 4-**Dungeon**: Responsible for creating the arena walls and texture.
