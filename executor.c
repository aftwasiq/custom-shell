#include "parser.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

#define PATH_MAX 4096
#define DIRECTORY_BUFFER 1024

typedef struct {
    unsigned long long d_ino;
    unsigned long long d_off;
    unsigned short d_reclen;
    unsigned char d_type;
    char d_name[];
        
} LINUX_DIRENT64;

void restoreOriginalMode(void);

int execute(COMMAND *cmd) {
    const char *pwd_failure = "Unable to list items.\n\r"; 
    const char *cd_failure = "The provided directories do not exist.\n\r";
    const char *mkdir_failure = "Unable to create new directory.\n\r";
    const char *exists = "Directory already exists.\n\r";

    char current_directory[PATH_MAX];
    
    if (strcmp("cd", cmd->arg) == 0) {
        if (syscall(SYS_chdir, cmd->argv[1]) == -1) {
            write(STDERR_FILENO, cd_failure, strlen(cd_failure));
        }   
    } 

    if (strcmp("ls", cmd->arg) == 0) {
        /*
        int dir = open(".", O_RDONLY | O_DIRECTORY);
        if (dir == -1) {
            write(STDERR_FILENO, pwd_failure, strlen(pwd_failure));
            return -1; 
        }
        
        LINUX_DIRENT64 *dirc;
        char buf[DIRECTORY_BUFFER];
        char items[PATH_MAX];
        int read;

        while ((read = syscall(SYS_getdents64, dir, buf, sizeof(buf))) > 0) {
            for (int i = 0; i < read;) {
                dirc = (LINUX_DIRENT64*)(buf + i);

                if (strcmp(dirc->d_name, ".") == 0 || strcmp(dirc->d_name, "..") == 0) {
                    i += dirc->d_reclen;
                    continue;
                }

                snprintf(items, sizeof(items), "%s", dirc->d_name);
                write(STDOUT_FILENO, items, strlen(items));
                write(STDOUT_FILENO, "\n", 1);

                if (dirc->d_type == DT_DIR) {
                    COMMAND *new = malloc(sizeof(COMMAND));
                    if (!new) {
                        i += dirc->d_reclen;
                        continue;
                    }

                    new->argv = malloc(sizeof(char*) * 3);
                    if (!new->argv) {
                        free(new);
                        i += dirc->d_reclen;
                        continue;
                    }

                    new->arg = "ls";
                    new->argv[0] = "ls";
                    new->argv[1] = strdup(dirc->d_name);
                    new->argv[2] = NULL;
                    new->argc = 2;

                    execute(new, tokens);

                    free(new->argv[1]);
                    free(new->argv);
                    free(new);
                }
                
                i += dirc->d_reclen;
            }
        }

        close(dir);
    */
    }

    if (strcmp("help", cmd->arg) == 0) {
        const char *helper = "Commands:\n\rls\n\rcd [path]\n\rmkdir [name]\n\rexit\n\rpwd\r";

        write(STDOUT_FILENO, helper, strlen(helper));
    }

    if (strcmp("mkdir", cmd->arg) == 0) {
        if (syscall(SYS_mkdir, cmd->argv[1]) == -1) {
            if (errno != EEXIST) {
                write(STDERR_FILENO, mkdir_failure, strlen(mkdir_failure));
            } else {
                write(STDERR_FILENO, exists, strlen(exists));
            }
        }
    }

    if (strcmp("exit", cmd->arg) == 0) {
        restoreOriginalMode();
        exit(0);
    }

    if (strcmp("pwd", cmd->arg) == 0) {
        if (getcwd(current_directory, sizeof(current_directory)) != NULL) {
            write(STDOUT_FILENO, current_directory, strlen(current_directory));
            write(STDOUT_FILENO, "\r\n", 2);
        } else {
            write(STDERR_FILENO, pwd_failure, strlen(pwd_failure));
        }
    }
    
    free_commands(cmd);
    return 0;
}

