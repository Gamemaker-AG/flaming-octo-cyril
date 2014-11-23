SRCDIR = src
BUILDDIR = build
BINDIR = bin
DATADIR = data
OUT = $(BINDIR)/engine.exe
SRCFILES = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/**/*.cpp)


CC = g++
LIB = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGLEW -lGL
LDFLAGS = -L/usr/lib $(LIB)
CFLAGS = -std=c++11

all: clean build

run: all
	$(OUT)

build: compile link
	mkdir $(BINDIR)/data
	cp -r $(DATADIR)/* $(BINDIR)/data

compile:
	mkdir $(BUILDDIR)
	$(CC) $(CFLAGS) -c $(SRCFILES)
	mv *.o $(BUILDDIR)

link:
	mkdir $(BINDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $(BUILDDIR)/*.o -o $(OUT)

clean:
	rm -rf $(BUILDDIR) $(BINDIR)
