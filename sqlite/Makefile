# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror

# Source files
SRCS = main.c authentication.c library.c

# Object files
OBJS = main.o authentication.o library.o

# Output executable
TARGET = main

# Default rule to build the project
all: $(TARGET)

# Linking the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile source files into object files
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

authentication.o: authentication.c
	$(CC) $(CFLAGS) -c authentication.c -o authentication.o

library.o: library.c
	$(CC) $(CFLAGS) -c library.c -o library.o

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
