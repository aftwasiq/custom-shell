#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <fcntl.h>

#define SHELL_BUFFER 1
#define PATH_MAX 4096
#define MAGENTA "\033[35m"
#define DEFAULT "\033[0m"

struct termios original;

const char *getattr_error = "Unable to get terminal attributes.\n";
const char *setattr_error = "Unable to set terminal attributes.\n";
const char *qsh = "$ ";

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

void welcomeMessage(void) {
    const char *welcome = "\n[qsh] Welcome! Use 'help' for assistance";
    const char *user = "\n[qsh] User: ";
    const char *name = getenv("USER");

    if (!name) {
        name = "UNKNOWN";
    }

    write(STDOUT_FILENO, welcome, strlen(welcome));
    write(STDOUT_FILENO, user, strlen(user));
    write(STDOUT_FILENO, name, strlen(name));
    write(STDOUT_FILENO, "\n", 1);
}

void shellPrompt(void) {
    char home[100];
    const char *name = getenv("USER");
    snprintf(home, sizeof(home), "/home/%s/", name);

    char current_directory[PATH_MAX];

    if (getcwd(current_directory, sizeof(current_directory)) != NULL) {
        if (strncmp(current_directory, home, strlen(home)) == 0) {
            char *msg = (current_directory + strlen(home));

            write(STDOUT_FILENO, MAGENTA, strlen(MAGENTA));
            write(STDOUT_FILENO, name, strlen(name));
            write(STDOUT_FILENO, DEFAULT, strlen(DEFAULT));
            write(STDOUT_FILENO, "@", 1);
            write(STDOUT_FILENO, MAGENTA, strlen(MAGENTA));

            write(STDOUT_FILENO, "~", 1);
            write(STDOUT_FILENO, "/", 1);

            write(STDOUT_FILENO, msg, strlen(msg)); 
            write(STDOUT_FILENO, DEFAULT, strlen(DEFAULT));
            write(STDOUT_FILENO, qsh, strlen(qsh));
        }
    } else {
        return;
    }
}

int main() {
    enterRawMode();
    atexit(&restoreOriginalMode);

    const char *cmd_fail = "Unable to execute command.\n";
    const char *newline = "\r\n";
    int fd = open("shell_art.txt", O_RDONLY);

    if (fd == -1) {
        return 1;
    }

    char buf[SHELL_BUFFER];
    ssize_t bytes;
    
    restoreOriginalMode();

    while ((bytes = read(fd, &buf, SHELL_BUFFER)) > 0) {
        if (buf[0] == '\n') {
            write(STDOUT_FILENO, newline, strlen(newline));
        } else {
            write(STDOUT_FILENO, &buf, SHELL_BUFFER);
        }
    }
    
    welcomeMessage();
    enterRawMode();

    write(STDOUT_FILENO, newline, strlen(newline)); 

    shellPrompt();
    char items[64];
    size_t count = 0;

    while ((bytes = read(STDIN_FILENO, &buf, SHELL_BUFFER)) > 0) {
        if (buf[0] == '\r') {
            if (count == 0) {
                write(STDOUT_FILENO, newline, strlen(newline));
                shellPrompt();
            } else {
                // LEXER->PARSE->EXECUTE CYCLE
                TOKEN *tokens = tokenize(items, &count);
                COMMAND *cmd = parse(tokens, count);
                
                write(STDOUT_FILENO, newline, strlen(newline));

                if (execute(cmd) != 0) {
                    write(STDERR_FILENO, cmd_fail, strlen(cmd_fail));
                }

                for (size_t i = 0; i < count; i++) {
                    items[i] = '\0';
                }

                count = 0;
                shellPrompt();
            }
        } else {
            write(STDOUT_FILENO, &buf, SHELL_BUFFER);
            if (count < (sizeof(items) - 1)) {
                items[count] = buf[0];
                count++;
            }
        }

        if (buf[0] == '\b') {
            write(STDOUT_FILENO, newline, strlen(newline));
            printf("%s", items);

        }
    }

    return 0;
}







