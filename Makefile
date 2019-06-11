override CFLAGS+= -std=c99 -D_GNU_SOURCE -DDEBUG -g -Wall
#-fsanitize=address

.PHONY: clean test

test:   binary_search_tree_test
	./binary_search_tree_test

clean:
	rm -rf *.o *.a *_test

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

binary_search_tree_test: test.o binary_search_tree_test.o binary_search_tree.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LIBS)
