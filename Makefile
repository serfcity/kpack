CFLAGS += -ansi -pedantic -Wall -Wextra

SRC = ${:!ls src/*.c!}
OBJ = $(SRC:%.c=%.o)

all: kpack

.o:
	$(CC) $(CFLAGS) -c $< -o $@

kpack: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $> -o kpack

clean:
	rm src/*.o kpack
