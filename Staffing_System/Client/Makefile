CC = gcc
CFLAGS = -c -o
CFLAGSs = -o

OBJS = Staff.o Connect.o User.o
TARGET = Staff

$(TARGET):$(OBJS)
	$(CC) $(OBJS) $(CFLAGSs) $(TARGET)

%.o:%.C
	$(CC) $(OBJS) $(CFLAGS) $^ $@

.PHONY:clean
clean:
	rm $(OBJS) $(TARGET)
