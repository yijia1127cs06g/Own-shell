#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

extern int EUID;
extern int EGID;

void shell(void);
char *read_cmd(void);
char *gets_line(char *, int);
char **args_parse(char *);
int count_args(char **);
int execute_cmd(int, char**);

int main(int argc, char **argv){
    EUID = atoi(argv[1]);
    EGID = atoi(argv[2]);
    setuid(EUID);
    setgid(EGID);
    while(1)
        shell();

}

void shell(void){
    char *cmd;
    char **args;
    int args_count;
    int status;

    fprintf(stdout, "$ ");
    fflush(stdout);
    cmd = read_cmd();
    args = args_parse(cmd);
    args_count = count_args(args);
    status = execute_cmd(args_count, args);
    
    free(cmd);
    free(args);
}
char *read_cmd(void){
    char *buffer; 

    if ((buffer=(char *) malloc(sizeof(char)*BUFSIZE))==NULL){
        fprintf(stderr, "Error: Unable to allocate required memory\n");
        exit(EXIT_FAILURE);
    }
    gets_line(buffer, BUFSIZE);
    
    return buffer;
}

char **args_parse(char* cmd){
    char **args;
    char *arg;
    char *delim = " ";
    int count = 0;
    if((args=(char **)malloc(ARGSIZE* sizeof(char))) == NULL){
        fprintf(stderr, "Error: Unable to allocate required memory\n");
        exit(EXIT_FAILURE);
    }

    arg = strtok(cmd,delim);
    while(arg != NULL){
        args[count] = arg;
        count++;
        arg = strtok(NULL, delim);
    }
    args[count] = NULL;
    return args;
}

int count_args(char **args){
    int count = 0;
    char **p = args;

    while(*p){
        count++;
        p++;
    }

    return count;

}

int execute_cmd(int args_count,char **argv){
    int i ;
    
    if(args_count<1)
        return -1;
    
    for(i=0;i< cmd_count();i++)
        if(strcmp(argv[0],cmd_list[i])==0){
            return (*cmd_func[i])(args_count, argv);
    }
    fprintf(stderr ,"%s: command not found\n",argv[0]);
    return -1;
}

char * gets_line(char *st, int n){
    char *line;
    int i=0;
    
    line = fgets(st, n, stdin);
    
    if(line){
        while (st[i] != '\n' && st[i] != '\0')
            i++;
        if (st[i] == '\n')
            st[i]='\0';
        else
            while(getc(stdin)!='\n')
                continue;
    }
    return line;
}

