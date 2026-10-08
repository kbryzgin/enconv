# Build config

CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -Iinclude

TARGET = enconv

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) src/*.o

.PHONY: all clean
