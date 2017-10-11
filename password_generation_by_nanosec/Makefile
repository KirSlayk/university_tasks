CC = g++
TARGET = progd
COMPILE = -std=c++11
CFLAGS = -std=c++11 -w -g -c

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET) clean

$(TARGET): *.cpp 
	$(CC) *.cpp $(COMPILE) -o $(TARGET)

clean:
	rm -rf *.o