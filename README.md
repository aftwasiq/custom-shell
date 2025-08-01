# qshell (IN PROGRESS)
A very simple custom UNIX-like shell written completely from scratch in C, however, it relies entirely on just system calls. The features are currently limited to built-in commands, tokenization & parsing, with plans to include piping, I/O redirection, command history and more. 


<img width="1417" height="700" alt="SHELL_IMAGE" src="https://github.com/user-attachments/assets/cd24446d-5743-4c95-b330-76f33cce71bd" />

# Supported Commands

| Command                 	| Usage        	| Description                                                              	|
|-------------------------	|--------------	|--------------------------------------------------------------------------	|
| Change Directory        	| cd [dir]     	| Changes the present user to the directory specified                      	|
| List                    	| ls           	| Lists all contents present under the current directory                   	|
| Make Directory          	| mkdir [name] 	| Creates a new directory under the current directory by the name provided 	|
| Help                    	| help         	| Lists all commands & their usage                                         	|
| Print Working Directory 	| pwd          	| Prints the current directory the user is present in                      	|
| Exit Shell              	| exit         	| Leaves qshell and returns to previous terminal settings                  	|

not finished
