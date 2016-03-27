CPPFLAGS=$(shell sdl2-config --cflags) $(EXTRA_CPPFLAGS)
LDLIBS=$(shell sdl2-config --libs) -lGLEW $(EXTRA_LDLIBS)
EXTRA_LDLIBS?=-lGL -lGLU -lglut
all: homework2
clean:
	rm -f *.o homework2
.PHONY: all clean

