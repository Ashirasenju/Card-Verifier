CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2

TARGET = cardcheck
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

re: clean all
