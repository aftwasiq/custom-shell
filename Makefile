CC=gcc
CCFLAGS= -Wall -Westra -g
TARGET= qshell
SRC =  main.c

$(TARGET): $(SRC)
		$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean: 
	rm -f $(TARGET)
