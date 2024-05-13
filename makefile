CC = gcc
CFLAGS = -Wall -Wextra -std=c99
EXECUTABLE = mySA
SRC = main.c functions.c
OBJ = $(SRC:.c=.o)
BUILDDIR = build

all: $(BUILDDIR) $(EXECUTABLE)

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

$(EXECUTABLE): $(addprefix $(BUILDDIR)/, $(OBJ))
	$(CC) -o $@ $^

$(BUILDDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE)
	rm -rf $(BUILDDIR)