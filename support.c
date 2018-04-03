#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>

char *convert_permission(char *, int mode);
char *convert_date(char *, time_t);
char check_type(int mode);

char* convert_date(char* str, time_t time){
    strftime(str, 64, "%Y-%m-%d %H:%M:%S %Z", localtime(&time));
    return str;
}

char check_type(int mode){
    if (S_ISDIR(mode)) return 'd';
    else if (S_ISREG(mode)) return '-';
    else if (S_ISLNK(mode)) return 'l';
    else if (S_ISCHR(mode)) return 'c';
    else if (S_ISBLK(mode)) return 'b';
    else if (S_ISFIFO(mode)) return 'p';
    else return 's';
}

char *convert_permission(char *buffer, int mode){
    *buffer = check_type(mode);
    *(buffer+1) = mode & S_IRUSR ? 'r' : '-';
    *(buffer+2) = mode & S_IWUSR ? 'w' : '-';
    *(buffer+3) = mode & S_IXUSR ? 'x' : '-';
    *(buffer+4) = mode & S_IRGRP ? 'r' : '-';
    *(buffer+5) = mode & S_IWGRP ? 'w' : '-';
    *(buffer+6) = mode & S_IXGRP ? 'x' : '-';
    *(buffer+7) = mode & S_IROTH ? 'r' : '-';
    *(buffer+8) = mode & S_IWOTH ? 'w' : '-';
    *(buffer+9) = mode & S_IXOTH ? 'x' : '-';
    *(buffer+10) = '\0';
    return buffer;
}

int int_pow(int a, int b){
    int i;
    int total=a;
    if (b==0) return 1;
    for(i=1;i<b;i++)
        total *= a;
    return total;
}
