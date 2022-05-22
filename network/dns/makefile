COMPILER = dns_query
SRCS = dns_query.c

OBJES = $(SRCS:.c=.o)

CC = gcc
.c.o:
	$(CC) -c -o $@ $<

all: $(COMPILER)

clean:
	rm $(OBJS) $(COMPILER)

# $(COMPILER) : $(OBJS)
#   $(CC) -o $(COMPILER) $(OBJS)
#
# execute: $(COMPILER) $(src)
# 	./$(COMPILER) compile $(src)
