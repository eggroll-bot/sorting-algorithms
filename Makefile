SOURCEFILES = bubble.c queue.c quick.c set.c shell.c sorting_comparison.c sorting_statistics.c stack.c
OBJECTFILES = bubble.o queue.o quick.o set.o shell.o sorting_comparison.o sorting_statistics.o stack.o
OUTPUT = sorting_comparison

CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -Ofast
LDFLAGS = -flto -Ofast

.PHONY: all debug clean format

all: $(OUTPUT)

$(OUTPUT): $(OBJECTFILES)
	$(CC) $(LDFLAGS) -o $(OUTPUT) $(OBJECTFILES)

$(OBJECTFILES): $(SOURCEFILES)
	$(CC) $(CFLAGS) -c $(SOURCEFILES)

debug: CFLAGS += -g -O0
debug: CFLAGS := $(filter-out -Ofast, $(CFLAGS))
debug: LDFLAGS += -O0
debug: LDFLAGS := $(filter-out -flto -Ofast, $(LDFLAGS))
debug: all

clean:
	rm -f $(OUTPUT) $(OBJECTFILES)

format:
	clang-format -i -style=file *.[ch]
