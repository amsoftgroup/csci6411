OBJS=main.o trampoline.S thread.o  scheduler.o test.o
CFLAGS=-g -I. -Wall -Wextra -lpthread -ggdb3 -O3 -m32 #-masm=intel
#DEFINES=-DTHINK_TIME
BIN=hw2
CC=gcc

%.o:%.c
	$(CC) $(CFLAGS) $(DEFINES) -o $@ -c $<

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(DEFINES) -o $(BIN) $^

clean:
	rm $(BIN) $(OBJS)