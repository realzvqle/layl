#include "startshell.h"
#include "cmdprocessor.h"




static inline void parse_buffer(data* data, char* buffer){
    data->cmd = strtok(buffer, " ");
    data->arg = strtok(NULL, "\n");
}


static bool is_empty_or_whitespace(const char* str) {
    while (*str != '\0') {
        if (!isspace((unsigned char)*str)) {
            return false;
        }
        str++;
    }
    return true;
}


static inline void start_file_reader(char* argument){
    FILE* fp = fopen(argument, "r");
    if(!fp){
        perror("Couldn't Open FIle");
        return;
    }
    char buffer[4096*3];
    data data;
    while(fgets(buffer, 4096*3, fp)){
        strtok(buffer, "\n");
        if (is_empty_or_whitespace(buffer)) {
            continue;
        }
        parse_buffer(&data, buffer);
        process_commands(&data);
    }
}


static inline void start_shell(){
    FILE* fp = fopen("~/.config/layl/config.lys", "r");
    if(!fp){
        goto SKIP_CONFIGURATION;
    }
    fclose(fp);

SKIP_CONFIGURATION:
    printf("");
    data data;
    char buffer[4096];
    char cwd[4096];
    
    data.shouldExit = false;
    while(data.shouldExit == false){
        getcwd(cwd, 4096);
        printf("%s/ -> ", cwd);
        fgets(buffer, 4096, stdin);
        strtok(buffer, "\n");
        if (is_empty_or_whitespace(buffer)) {
            continue;
        }
        parse_buffer(&data, buffer);
        process_commands(&data);
    }
}


void check_respective_shell_state(char* argument){
    if(argument == NULL){
        start_shell();
        return;
    }
    
    start_file_reader(argument);
}



