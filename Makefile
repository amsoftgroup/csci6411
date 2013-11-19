OBJS=main.o dispatcher.S thread.o test.o
CFLAGS=-g -I. -Wall -Wextra -lpthread -ggdb3 #-masm=intel 
#DEFINES=-DTHINK_TIME
BIN=hw2
CC=gcc

%.o:%.c
	$(CC) $(CFLAGS) $(DEFINES) -o $@ -c $<

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(DEFINES) -o $(BIN) $^

clean:
	rm $(BIN) $(OBJS)