# Battleship game

Battleship game for two players

## | Installation
```
git clone https://github.com/thecoldstone/lab_program.git
```
## | Usage
Use the make file to build the project.
```bash
make
./main 
```

## | Descriptiption

a) The current version is supposed for two players sharing the same shell interface. The logic of a game is straightforward and based on the following steps:
> ***
> 1. User's input
> 2. Initialization of board and ships
> 3. Game logic itself
> 4. Deallocation of allocated memory 
> ***

### | More detailed
> ***
> - INPUT and INITIALIZATION
>   1. User choose the board size
>   2. User choose the number of ships to place on a board
>   3. User choose the way to insert ships:
>       - Put ships **manually**
>       - Put ships **randomly**
> 
> - GAME LOGIC
>   1. User see the opponent's board and choose the coordinates where to shoot
>   2. If the user hits he is continuing  **the step 1**
>   3. Once the user has destroyed every ship belonged to the opponent the game finishes
> - DEALLOCATION
>   1. The initialized board and ships are destroyed
> ***

## | Modules
```
main.c 
#Game logic
battleship.*
#

```

## | Clean 
```bash
make clean
```

## | Setbacks

``` 
1. Scanner for input does not work well. It accepts only integers. If user type something else intstead of integers, program is crashed. 

2. Error handling

3. Still some memory leaks occur during deallocating of the program
```

