# Custom Shell

A simple custom UNIX-based shell written in low-level C for personal use, built from scratch. It features its own relatively simple lexer & parser for command input.

Disclaimer: i'm still actively working on this so it is very buggy & not finalized

<img width="1711" height="995" alt="Screenshot 2025-09-05 000219" src="https://github.com/user-attachments/assets/aac941b2-60dc-48cc-8404-e59ad20c13e5" />



# Supported Commands (at the moment)

| Command                 	| Usage        	| Description                                                              	|
|-------------------------	|--------------	|--------------------------------------------------------------------------	|
| Change Directory        	| cd [dir]     	| Changes the present user to the directory specified                      	|
| List                    	| ls           	| Lists all contents present under the current directory                   	|
| Make Directory          	| mkdir [name] 	| Creates a new directory under the current directory by the name provided 	|
| Help                    	| help         	| Lists all commands & their usage                                         	|
| Print Working Directory 	| pwd          	| Prints the current directory the user is present in                      	|
| Exit Shell              	| exit         	| Leaves qshell and returns to previous terminal settings                  	|

not finished

# Checklist

- [x] Raw Input Mode
- [x] Basic I/O
- [x] Basic Lexer 
- [x] Basic Parser
- [x] Command Generation
- [ ] Job Control
- [ ] Pipelining
- [ ] I/O Redirection
- [ ] Command History
- [ ] Signal Handling
- [ ] Scripting

