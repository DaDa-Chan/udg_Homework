# README

## How to use

1. Open your terminal 
2. `cd` to the directory
3. Type `make`
4.  ==running== 
   - Type `./pdadd YYYY-MM-DD` to add a new diary
   - Type`./pdremove YYYY-MM-DD` to remove  specified diary
   - Type`./pdlist [YYYY-MM-DD] [YYYY-MM-DD]` to list diarys in specified range.The last two arguments are optional
   - Type`./pdshow YYYY-MM-DD` to see the specified diary
5. Type `make clean` 



**Rmk:** when you type `./pdlist` without any argument , it will list all the date. And `./pdlist YYYY-MM-DD` is invalid command.