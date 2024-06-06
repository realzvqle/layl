#include "cmdprocessor.h"
#include "cmdexecutor.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>



static char* cmds[] = {"echo", "cd", "exit"};





void process_commands(data* data){
    int cmdSize = sizeof(cmds)/sizeof(cmds[0]);
    
    for(int i = 0; i < cmdSize; i++){
        if(strcmp(data->cmd, cmds[i]) == 0){
            execute_commands(i, data);
            return;
        }
    }
    
    char* args[4096];
    int argc = 0;
    char* token = strtok(data->arg, " ");
    while (token != NULL && argc < 4095) {
        args[argc++] = token;
        token = strtok(NULL, " ");
    }
    args[argc] = NULL;

    char* argv[argc + 2];
    argv[0] = data->cmd;
    for (int i = 0; i <= argc; ++i) {
        argv[i + 1] = args[i];
    }

    int result = fork();
    if(result == 0){
        execvp(data->cmd, argv);
        perror("Failed executing process");
        _exit(-1);
    }
    else if(result == -1){
        perror("couldn't fork process");

    }
    else{
        int status;
        waitpid(result, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            printf("%s was not found\n", data->cmd);
        }
    }
}