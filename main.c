/*
File:   main.c
Author: Abdullah Wasiq 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER 1

// quick reference
// parts of the shell needed
// parser
// --> lexer
//      > get input characters and tokenize them
// --> parser
// executer

struct termios original;

const char *getattr_error = "Unable to get terminal attributes.\n";
const char *setattr_error = "Unable to set terminal attributes.\n";
const char *shell_prompt = "[qsh ~]$ ";

void enterRawMode(void) {
    if (tcgetattr(STDIN_FILENO, &original) == -1) {
        write(STDERR_FILENO, getattr_error, strlen(getattr_error)); 
        return;
    }

    struct termios raw;

    if (tcgetattr(STDIN_FILENO, &raw) == -1) {
        write(STDERR_FILENO, getattr_error, strlen(getattr_error));
        return;
    }
        
    raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag &= ~(CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        write(STDERR_FILENO, setattr_error, strlen(setattr_error));
        return;
    }

}

void restoreOriginalMode(void) {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &original) == -1) {
        write(STDERR_FILENO, setattr_error, strlen(setattr_error)); 
    }
}

void welcomeUserMessage(void) {
    const char *prefix = "\033[35m\r\n[qshell] Welcome, ";
    const char *suffix = "\033[0m!\r\n";
    const char *username = getenv("USER");
    
    if (!username) {
        username = "user";
    }

    write(STDOUT_FILENO, prefix, strlen(prefix));
    write(STDOUT_FILENO, username, strlen(username));
    write(STDOUT_FILENO, suffix, strlen(suffix));
}

int main(int argc, char *argv[]) {
    enterRawMode();

    const char *newline = "\r\n";
    int fd = open("shell_art.txt", O_RDONLY);

    if (fd == -1) {
        return 1;
    }

    char buf[BUFFER];
    ssize_t bytes;
    
    restoreOriginalMode();

    while (bytes = read(fd, &buf, BUFFER) > 0) {
        if (buf[0] == '\n') {
            write(STDOUT_FILENO, newline, strlen(newline));
        } else {
            write(STDOUT_FILENO, &buf, BUFFER);
        }
    }

    welcomeUserMessage();
    enterRawMode();

    write(STDOUT_FILENO, newline, strlen(newline)); 
    write(STDOUT_FILENO, shell_prompt, strlen(shell_prompt));

    while (bytes = read(STDIN_FILENO, &buf, BUFFER) > 0) {
        if (buf[0] == '\r') { 
            write(STDOUT_FILENO, newline, strlen(newline));
            write(STDOUT_FILENO, shell_prompt, strlen(shell_prompt));
        } else {
            write(STDOUT_FILENO, &buf, BUFFER);
        }
    }

    atexit(&restoreOriginalMode);

    return 0;
}




