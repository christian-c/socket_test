CFLAGS =
INCLUDES = -I/usr/include/ -I/usr/local/include
LIBS = -L/usr/lib  -lmsgpack
% : %.cpp
	g++ -fopenmp $(CFLAGS) $(INCLUDES) -o $@ $< $(LIBS) -std=c++0x
