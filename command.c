#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>


extern int EUID;
extern int GUID;

int cmd_cat(int argc, char **argv){
    FILE * fp;
    char ch;

    if(argc != 2){
        fprintf(stderr,"Usage: cat filename\n");
        return -1;
    }
    if((fp = fopen(argv[1],"r")) == NULL){
        fprintf(stderr, "cat: %s: No such file or directory\n",argv[1]);
        return -1;
    }
    while((ch = getc(fp)) != EOF){
        putc(ch, stdout);
    }

    if(fclose(fp) != 0){
        fprintf(stderr, "cat: %s: Error in closing file\n", argv[1]);
        return -1;
    }
    return 0;
}



int cmd_echo(int argc, char **argv){
    FILE *fp;
    
    if (argc == 2){
        fprintf(stdout, "%s\n", argv[1]);
        return 0;
    }
    else if (argc == 3){
        if ((fp=fopen(argv[2], "a")) == NULL){
            fprintf(stderr, "echo: %s: Can't open the file\n", argv[2]);
            return -1;
        }
        fputs(argv[1], fp);
        fputs("\n", fp);
        fclose(fp);
        return 0;
    }
    else{
        fprintf(stderr, "Usage: echo string [filename]\n");
        return -1;
    }

}

int cmd_exit(int argc, char **argv){
    if (argc != 1){
        fprintf(stderr, "Usage: exit\n");
        return -1;
    }
    exit(0);
}


int cmd_pwd(int argc, char **argv){
    char * dir;
    if (argc != 1){
        fprintf(stderr, "Usage: pwd\n");
        return -1;
    }
    
    if((dir = (char *)malloc(sizeof(char)*1024)) == NULL){
        fprintf(stderr, "Error: Unable to allocate required memory\n");
        exit(EXIT_FAILURE);
    }
    
    getcwd(dir, 1024);
    fprintf(stdout,"%s\n", dir);
    free(dir);
    return 0;
}


int cmd_cd(int argc, char **argv){
    
    if(argc > 2){
        fprintf(stderr, "Usage: cd dir\n");
        return -1;
    }
    
    chdir(argv[1]);
    return 0;
}

/*
int cmd_find(int argc, char **argv){
    char *dir_string;
    DIR dir;
    struct 

    if (argc>2){
        fprintf(stderr, "Usage: find [dir]\n");
        return -1;
    }
    else if (argc==1){
        if ((dir=(char *)malloc(sizeof(char)*1024)) == NULL){
            fprintf(stderr, "Error: Unable to allocate required memory\n");
            exit(EXIT_FAILURE);
        }
        getcwd(dir, 1024);
        
    }
}
*/
