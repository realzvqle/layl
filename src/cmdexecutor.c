#include "cmdexecutor.h"





void execute_commands(int index, data* data){
    switch(index){
        case 0:
            if(!data->arg) break;
            printf("%s\n", data->arg);
            break;
        case 1:
            if(!data->arg) break;
            int result = chdir(data->arg);
            if(result == -1){
                perror("cd failed");
            }
            break;
        case 2:
            _exit(0);
            break;
        default:
            printf("%s has been found, but no implemnation has been found\n", data->cmd);
            break;
    }
}