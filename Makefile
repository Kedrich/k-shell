CC = gcc
CFLAGS = -Wall -Iinclude
TARGET = k-shell

SRCS = src/main.c src/builtins.c

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)