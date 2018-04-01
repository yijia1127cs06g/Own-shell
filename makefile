# Compiler
CC = /usr/bin/gcc

# Name of program
PROG = shell

# The name of the object files
OBJS = command.o shell.o

# All the header and c files
SRCS = shell.c command.c
HDRS = shell.h

# Add -I to the dir the curl include files are in
CFLAGS = -g -std=c99 -Wall

# Build the executable file
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

# Seperately compile each .c file
shell.o: shell.c shell.h
	$(CC) $(CFLAGS) -c shell.c

command.o: command.c shell.h
	$(CC) $(CFLAGS) -c command.c

# Clean up crew
clean: 
	rm -fv core* $(PROG) $(OBJS)

cleaner: clean
	rm -fv #* *~
