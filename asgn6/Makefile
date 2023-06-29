CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic 


all: banhammer

banhammer: banhammer.o parser.o ht.o ll.o node.o bf.o bv.o city.o
	$(CC) -o $@ $^ 


%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f banhammer *.o


format:
	clang-format -i -style=file *.[ch]
