CC = gcc
CFLAGS = -c -o
CFLAGSs = -o

OBJS = Staff.o Connect.o Sqlite.o Operation.o
TARGET = Staff

$(TARGET):$(OBJS)
	$(CC) $(OBJS) $(CFLAGSs) $(TARGET) -lpthread -lsqlite3

%.o:%.C
	$(CC) $(OBJS) $(CFLAGS) $^ $@

.PHONY:clean
clean:
	rm $(OBJS) $(TARGET)