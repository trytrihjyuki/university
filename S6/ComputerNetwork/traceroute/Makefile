CC = gcc
CFLAGS = -Wextra -Wall -std=gnu17
OBJFILES = receive.o send.o traceroute.o
TARGET = traceroute


all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) *~

distclean:
	rm -f $(OBJFILES) $(TARGET) *~