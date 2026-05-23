CC = gcc
CFLAGS = -Wall
OBJ = main.o mpeg.o
TARGET = mpg_split_size

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c mpeg.h
	$(CC) $(CFLAGS) -c main.c

mpeg.o: mpeg.c mpeg.h
	$(CC) $(CFLAGS) -c mpeg.c

clean:
	rm -f $(TARGET) $(OBJ) video_parte_*.mpg