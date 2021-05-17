CXX := g++

CXXFLAGS := -lGL -lglut -lGLU
# CXXFLAGS += -DDEBUG


HDRS := $(wildcard *.h)

SRCS := $(wildcard *.cpp)

OBJS := $(SRCS:.cpp=.o)

EXEC := output

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CXX) -o $@ $(OBJS) $(CXXFLAGS)

clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
