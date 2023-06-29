CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic 

all: encode decode 

encode: encode.o huffman.o io.o code.o pq.o stack.o node.o
	$(CC) -o $@ $^ 

decode: decode.o huffman.o io.o code.o pq.o stack.o node.o
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f encode decode *.o


format:
	clang-format -i -style=file *.[ch]
