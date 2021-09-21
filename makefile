CXX=g++
CPPFLAGS = $(sdl2-config --cflags --libs -Wall)
LDFLAGS=-L/usr/local/lib/ -lSDL2
SRCS=game.cpp
OBJS=game.o

$(OBJS): $(SRCS)
	$(CXX) -c $(SRCS) $(CPPFLAGS) 
game: $(OBJS)
	$(CXX) -o game $(OBJS) $(LDFLAGS)