#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <utime.h>
extern int EUID;
extern int EGID;
extern char *convert_permission(char *, int st_mode);
extern char *convert_date(char*, time_t);
extern char file_type[];
extern char *file_string[];


int cmd_cat(int argc, char **argv){
    FILE * fp;
    char ch;
    struct stat buffer;
    if(argc != 2){
        fprintf(stderr,"Usage: cat filename\n");
        return -1;
    }
    if(access(argv[1],R_OK)<0){
        perror("cat");
        return -1;
    }
    if((fp = fopen(argv[1],"r")) == NULL){
        perror("cat");
        return -1;
    }
    stat(argv[1],&buffer);
    if(S_ISDIR(buffer.st_mode)){
        fprintf(stderr,"cat: %s is directory\n", argv[1]);
        return -1;
    }
    while((ch = getc(fp)) != EOF)
        putc(ch, stdout);   
        fflush(stdout);

    if(fclose(fp) != 0){
        perror("cat");
        return -1;
    }
    return 0;
}



int cmd_echo(int argc, char **argv){
    FILE *fp;
    struct stat buffer;
    if (argc == 2){
        fprintf(stdout, "%s\n", argv[1]);
        fflush(stdout);
        return 0;
    }
    else if (argc == 3){
        if (stat(argv[2],&buffer)<0){
            perror("echo");
            return -1;
        }
        if (S_ISDIR(buffer.st_mode)){
            fprintf(stderr, "cat: %s is directory\n", argv[2]);
        }
        if(access(argv[2],W_OK) != -1){
            if ((fp=fopen(argv[2], "a")) == NULL){
                perror("echo");
                return -1;
            }
            fputs(argv[1], fp);
            fclose(fp);
            return 0;
        }
        else{
            perror("echo");
            return -1;
        }
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
        perror("Error");
        exit(EXIT_FAILURE);
    }
    
    if(getcwd(dir, 1024)==NULL){
        perror("pwd");
        return -1;
    }
    fprintf(stdout,"%s\n", dir);
    fflush(stdout);
    free(dir);
    return 0;
}


int cmd_cd(int argc, char **argv){
    
    if(argc > 2){
        fprintf(stderr, "Usage: cd dir\n");
        return -1;
    }
    if (access(argv[1], R_OK)<0){
        perror("cd");
        return -1;
    }
    if (chdir(argv[1]) != 0){
        perror("cd");
        return -1;
    }
    return 0;
}


int cmd_find(int argc, char **argv){
    char file_buffer[1024];
    DIR *dir;
    struct dirent *dirpath;
    struct stat buffer;
    char permission[11]={0};

    if (argc>2){
        fprintf(stderr, "Usage: find [dir]\n");
        return -1;
    }
    else if (argc==1){
        dir = opendir(".");
    }
    else{
        if (access(argv[1], R_OK)<0){
            perror("find");
            return -1;
        }
        dir = opendir(argv[1]);
    }
    if ( dir == NULL){
        perror("find");
        closedir(dir);
        return -1;
    }

    while((dirpath=readdir(dir)) != NULL){
        sprintf(file_buffer,"%s/%s", argc>1?argv[1]:".",dirpath->d_name);
        stat(file_buffer, &buffer);
        convert_permission(permission, buffer.st_mode);
        fprintf(stdout,"%s %ld %d %s\n",permission, buffer.st_size
                ,dirpath->d_type,dirpath->d_name);
    }
    fflush(stdout);
    closedir(dir);
    
    return 0;
}

int cmd_mkdir(int argc, char **argv){
    if (argc != 2){
        fprintf(stderr, "Usage: mkdir dir\n");
        return -1;
    }
    if(mkdir(argv[1], 0775)!=0){
        perror("mkdir");
        return -1;
    }
    return 0;

}

int cmd_rmdir(int argc, char **argv){
    if (argc != 2){
        fprintf(stderr, "Usage: rmdir dir\n");
        return -1;
    }
    if (access(argv[1],W_OK)<0){
        perror("rmdir");
        return -1;
    }
    if(rmdir(argv[1]) != 0){
        perror("rmdir");
        return -1;
    }
    return 0;
}

int cmd_stat(int argc, char **argv){
    char permission[11]={0};
    char time_buffer[64];
    int i;
    struct stat buffer;
    if ( argc!= 2){
        fprintf(stderr,"Usage: stat file/dir\n");
        return -1;
    }
    
    if (access(argv[1],R_OK) <0 ){
        perror("stat");
        return -1;
    }
    stat(argv[1],&buffer);
    convert_permission(permission,buffer.st_mode);
    fprintf(stdout, "  File: \'%s\'\n", argv[1]);
    fprintf(stdout, "  Size: %ld\t\tBlocks: %ld\tIO Blocks: %ld\t",
            buffer.st_size, buffer.st_blocks, buffer.st_blksize);
    for(i=0;i<7;i++)
        if (permission[0]==file_type[i]){
            fprintf(stdout,"%s\n",file_string[i]);
            break;
        }
    fprintf(stdout, "Device: %lxh/%lud\tInode: %lu\tLinks: %lu\n",
            buffer.st_dev,buffer.st_dev, buffer.st_ino, buffer.st_nlink);
    fprintf(stdout, "Access: (%.4o/%s)\tUid: %d\tGid: %d\n",
            buffer.st_mode%4096, permission, buffer.st_uid, buffer.st_gid);
    fprintf(stdout, "Access: %s\n",
            convert_date(time_buffer, buffer.st_atime));
    fprintf(stdout, "Modify: %s\n", 
            convert_date(time_buffer, buffer.st_mtime));
    fprintf(stdout, "change: %s\n", 
            convert_date(time_buffer, buffer.st_ctime));
    fflush(stdout);

    return 0;
}

int cmd_id(int argc, char **argv){
    if (argc!=1){
        fprintf(stderr,"Usage: id");
        return -1;
    }
    fprintf(stdout,"euid=%d guid=%d\n", EUID,EGID);
    return 0;
}

int cmd_rm(int argc, char **argv){
    if (argc != 2){
        fprintf(stderr,"Usage: rm file");
        return -1;
    }
    if(access(argv[1],W_OK)<0 && access(argv[1],X_OK)<0){
        perror("rm");
        return -1;
    }
    if(unlink(argv[1])!=0){
        perror("rm");
        return -1;
    }
    return 0;
}

int cmd_umask(int argc, char **argv){
    if(argc!=2){
        fprintf(stderr,"Usage: umask mode");
        return -1;
    }
    umask(strtol(argv[1],NULL,8));
    return 0;
}
int cmd_chmod(int argc, char **argv){
    if (argc!=3){
        fprintf(stderr, "Usage: chmod mode file/dir");
        return -1;
    }
    chmod(argv[2],strtol(argv[1],NULL,8));
    return 0;
}

int cmd_touch(int argc, char**argv){
    if (argc != 2){
        fprintf(stderr,"Usage: touch file");
        return -1;
    }
    if (access(argv[1],F_OK) != -1){
        if ((utime(argv[1],NULL))!=0){
            perror("touch");
            return -1;
        }
    }
    else{
        if(creat(argv[1],(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH))<0) {
        perror("touch");
        return -1;
        }
    }
    return 0;
}
int cmd_help(int argc, char**argv){
    fprintf(stdout,
            "Type some commands\nBelow are the built-in commands:\n\n");
    fprintf(stdout, "cat file\t\tcd dir\n");
    fprintf(stdout, "chmod mode file/dir\techo str [file]\n");
    fprintf(stdout, "exit\t\t\tfind [dir]\n");
    fprintf(stdout, "help\t\t\tid\n");
    fprintf(stdout, "mkdir dir\t\tpwd\n");
    fprintf(stdout, "rm file\t\t\tmdir dir\n");
    fprintf(stdout, "stat file/dir\t\ttouch file\n");
    fprintf(stdout, "umask mode\n");
    fflush(stdout);
    return 0;
}
