#include "cmdexecutor.h"





void execute_commands(int index, data* data){
    switch(index){
        case 0:
            if(!data->arg) break;
            printf("%s\n", data->arg);
            break;
        default:
            printf("%s has been found, but no implemnation has been found\n", data->cmd);
            break;
    }
}