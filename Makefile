PROGRAM = street_crosser
CC      = gcc
CFLAGS  = -g -Wall
LDFLAGS = -lGL -lGLU -lglut -lm
OBJFILES  = main.o functions.o gameover.o

all: $(PROGRAM)

$(PROGRAM): $(OBJFILES)
	$(CC) -o $(PROGRAM) $(OBJFILES) $(LDFLAGS)


.PHONY: clean dist

clean: 
	-rm -f $(OBJFILES) $(PROGRAM) *~

