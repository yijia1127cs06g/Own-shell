#define BUFSIZE 1024
#define ARGSIZE 64

int EUID;
int GUID;

int cmd_cat(int , char **);
int cmd_cd(int, char **);
int cmd_exit(int , char **);
int cmd_echo(int, char **);
int cmd_pwd(int, char **);

char * cmd_list[] = {
    "cat",
    "cd",
    "echo",
    "exit",
    "pwd"
};

int (*cmd_func[])(int argc, char **argv) = {
    &cmd_cat,
    &cmd_cd,
    &cmd_echo,
    &cmd_exit,
    &cmd_pwd
};

int cmd_count(){return sizeof(cmd_list)/ sizeof(char*); }


