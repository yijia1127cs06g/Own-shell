#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 1024
#define ARGSIZE 64

void shell(void);
char *read_cmd(void);
char *gets_line(char *, int);
char **args_parse(char *);

int main(int argc, char *argv[], char *envp[]){
    
    while(1)
        shell();

}

void shell(void){
    char *cmd;
    char **args;
    
    fprintf(stdout, "$ ");
    cmd = read_cmd();
    args = args_parse(cmd);
    free(cmd);
    free(args);
}
char *read_cmd(void){
    char *buffer; 
    int i = 0;

    if ((buffer=(char *) malloc(sizeof(char)*BUFSIZE))==NULL){
        fprintf(stderr, "Error: unable to allocate required memory\n");
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
    char **p;
    if((args=(char **)malloc(ARGSIZE* sizeof(char))) == NULL){
        fprintf(stderr, "Error: unable to allocate required memory\n");
        exit(EXIT_FAILURE);
    }

    arg = strtok(cmd,delim);
    while(arg != NULL){
        args[count] = arg;
        count;
        arg = strtok(NULL, delim);
    }
    args[count] = NULL;

    return args;
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
