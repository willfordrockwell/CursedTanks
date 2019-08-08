CC = gcc
CPPC = g++

CPPCFLAGS = -g
CPPCFLAGS += -c
CPPCFLAGS += -I include
CPPCFLAGS += -pipe

CCFLAGS = $(CPPCFLAGS)
CCFLAGS += -std=c99

PHONY_N = player clean create assem_lib clean_lib objects

#.c sources
LIBRARY_C_S := $(wildcard lib/src/*.c)

#.cpp sources Cursed_Tanks
LIBRARY_CPP_S := $(wildcard lib/src/*.cpp)

LIBRARY_O := $(LIBRARY_C_S:%.c=%.o)
LIBRARY_O += $(LIBRARY_CPP_S:%.cpp=%.o)
LIBRARY_O := $(LIBRARY_O:lib/src/%=%)

SFML_LIBRARIES = sfml-graphics
SFML_LIBRARIES += sfml-window
SFML_LIBRARIES += sfml-system
SFML_LIBRARIES := $(addprefix -l, $(SFML_LIBRARIES))

.PHONY: $(PHONY_N)

all: player server test

player: Cursed_Tanks.o
	$(CPPC) obj/Cursed_Tanks.o -o bin/CursedTanks -g $(SFML_LIBRARIES) -L./lib -lcursedtanks

server: Server.o
	$(CC) obj/Server.o -o bin/Server -g -L./lib -lcursedtanks

test: test.o
	$(CC) obj/test.o -o bin/test -g -L./lib -lcursedtanks

Cursed_Tanks.o: sources/Cursed_Tanks.cpp
	$(CPPC) sources/Cursed_Tanks.cpp -o obj/Cursed_Tanks.o $(CPPCFLAGS)

Server.o: sources/Server.c
	$(CC) sources/Server.c -o obj/Server.o $(CCFLAGS)

test.o: sources/test.c
	$(CC) sources/test.c -o obj/test.o $(CCFLAGS)

assem_lib: objects
	ar -rc lib/libcursedtanks.a $(LIBRARY_O)

objects:
	$(CC) $(LIBRARY_C_S) $(CCFLAGS)
	$(CPPC) $(LIBRARY_CPP_S) $(CPPCFLAGS)

clean_lib:
	rm lib/*.a

create:
	mkdir -p obj bin

clean:
	rm -rdf bin obj *.o
