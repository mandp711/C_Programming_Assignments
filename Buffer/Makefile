CC = clang
CFLAGS = -Wall -Wextra -Wstrict-prototypes -Werror -pedantic

# Ensure that executable sipports debugging 
CFLAGS+=-gdwarf-4

.PHONY: all 
all: xd

.PHONY: format
format: 
		clang-format -i -style=file *.[ch]

.PHONY: clean 
clean: 
		rm -f *.o
		rm xd

