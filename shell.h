#define BUFSIZE 1024
#define ARGSIZE 64

int EUID;
int EGID;

int cmd_cat(int , char **);
int cmd_cd(int, char **);
int cmd_chmod(int, char **);
int cmd_exit(int , char **);
int cmd_echo(int, char **);
int cmd_find(int, char **);
int cmd_help(int, char**);
int cmd_id(int, char**);
int cmd_mkdir(int, char **);
int cmd_pwd(int, char **);
int cmd_rm(int, char **);
int cmd_rmdir(int, char**);
int cmd_stat(int, char**);
int cmd_touch(int, char **);
int cmd_umask(int, char **);

char * cmd_list[] = {
    "cat",
    "cd",
    "chmod",
    "echo",
    "exit",
    "find",
    "help",
    "id",
    "mkdir",
    "pwd",
    "rm",
    "rmdir",
    "stat",
    "touch",
    "umask"
};

int (*cmd_func[])(int argc, char **argv) = {
    &cmd_cat,
    &cmd_cd,
    &cmd_chmod,
    &cmd_echo,
    &cmd_exit,
    &cmd_find,
    &cmd_help,
    &cmd_id,
    &cmd_mkdir,
    &cmd_pwd,
    &cmd_rm,
    &cmd_rmdir,
    &cmd_stat,
    &cmd_touch,
    &cmd_umask
};

int cmd_count(){return sizeof(cmd_list)/ sizeof(char*); }

char file_type[]={
            'd',
            '-',
            'c',
            'b',
            'l',
            'p',
            's'
};
char *file_string[]={
            "directory file",
            "regular file",
            "character devide file",
            "block file",
            "symbolic link file",
            "pip file",
            "socket file"
};
