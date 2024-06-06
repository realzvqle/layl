#include "cmdprocessor.h"
#include "cmdexecutor.h"




static char* cmds[] = {"echo"};





void process_commands(data* data){
    int cmdSize = sizeof(cmds)/sizeof(cmds[0]);
    
    for(int i = 0; i < cmdSize; i++){
        if(strcmp(data->cmd, cmds[i]) == 0){
            execute_commands(i, data);
            return;
        }
    }
    printf("%s was not found\n", data->cmd);
}