# Homework #1
Secure interactive shell with some built-in commands.
Below is the list of commands:
cat			cd	
chmod		echo	
exit			find
help		id
mkdir		pwd
rm			rmdir
stat			touch
umask

## cat
Display content of a file
* Usage: cat file
* Args:
file - relative or absolute path of  a file 
* Output: content of file
* Example:
$ cat 1234.txt
$ cat /usr/1234.txt

## cd
Switch current working directory to a directory
* Usage: cd dir
* Args:
dir - relative or absolute path of a directory
* Output: none
* Example:
$ cd ..
$ cd /bin

## chmod
Change the mode of a file or directory
* Usage: chmod mode file/dir
* Args:
mode - 4 or 3 digits in base-8. E.g. 775, 0777…
file/dir - relative or absolute path of a file or directory
* Output: none
* Example:
$ chmod 665 1234.txt
$ chmod 0775 1234.txt

## echo
Display a string or append string to the file
* Usage: echo str [file]
* Args:
str -  a string without space
[file] - relative or absolute path of a file
* Outputs: if only given str , it will output string. Otherwise, append string to file 
* Example:
$ echo apple
$ echo banana 12345.txt

## exit
Leave the shell
* Usage: exit
* Args: none
* Output: none
* Example:
$ exit

## find
List files and directories in the current working directory or given directory
* Usage: find [dir]
* Args:
[dir] - relative or absolute path of directory
* Output: all files and directories in directory and its information include permission, links, uid, gid, size, filename
e.g. drwxrwxr-x 1 1000 1000 4096 bin
* Example:
$ find
$ find /bin

## help
Display help message
* Usage: help
* Args: none
* Output: information and the list of available commands
* Example:
$ help

## id
Show current euid and egid number which is given by server
* Usage: help
* Args: none
* Output: euid and egid
* Example:
$ id

## mkdir
Create a new directory
* Usage: mkdir dir
* Args:
dir - relative or absolute path of directory
* Output: none
* Example:
$ mkdir apple
$ mkdir /bin /apple

## pwd
Display the current working directory
* Usage: pwd
* Args: none
* Output: the path of current working directory
* Example:
$ pwd

## rm
Remove a file
* Usage: rm file
* Args:
file - relative or absolute path of a file
* Output: none
* Example:
$ rm 1234.txt
$ rm /bin /bash

## rmdir
Remove an empty directory
* Usage: rmdir dir
* Args:
dir - relative or absolute path of a directory
* Output: none
* Example:
$ rmdir temp
$ rmdir /bin /temp

## stat
Display detailed information of the given file or directory
* Usage: stat file/dir
* Args:
file/dir - relative or absolute path of a file or directory
* Output: the detail information of file or directory
e.g.
     File: ‘123.txt’
     Size: 4556			Blocks: 16		IO Blocks: 4096	regular file
Device:802h/2050d	Inode: 547935	Links: 1
Access:(0664/-rw-rw-r--)	Uid: 1000	Gid: 1000
Access: 2018-04-02 17:23:42 UTC
Modify: 2018-04-02 17:23:42 UTC
Change: 2018-04-02 17:23:42 UTC
* Example:
$ stat 1234.txt
$ stat /bin /bash

## touch
Update access and modification timestamp of a file. If given file doesn’t exist, it creates a new file
* Usage: touch file
* Args:
file - relative or absolute path of a file
* Output: none
* Example:
$ touch 1234.txt
$ touch /bin /1234.txt

## umask
Change the umask of the current session
* Usage: umask mode
* Args:
mode - 4 or 3 digits in base-8. E.g. 775, 0777…
* Output: none
* Example:
$ umask 0775
$ umask 665