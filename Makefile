CC = gcc

CFLAGS = -Wall -Iinclude

TARGET = k-shell

SRCS = src/main.c

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)