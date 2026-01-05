CC = gcc
CFLAGS = -lcurl
SRC = main.c
TARGET = ORD

all : $(TARGET)

$(TARGET): $(SRC)
	gcc $(SRC) -o $(TARGET) $(CFLAGS)

clean:
	rm -rf $(TARGET)

.PHONY: clean
