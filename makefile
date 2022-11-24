# distributed under the mit license
# https://opensource.org/licenses/mit-license.php

# http://nuclear.mutantstargoat.com/articles/make/

src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS =

chacha20: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) myprog
