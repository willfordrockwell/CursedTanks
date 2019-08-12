CPPC = g++

CPPCFLAGS = -g
CPPCFLAGS += -I include
CPPCFLAGS += -pipe
CPPCFLAGS += -Wall
CPPCFLAGS += -lpthread

PHONY_N = player clean create assem_lib clean_lib objects

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

all: player server

player: Cursed_Tanks.o
	$(CPPC) obj/Cursed_Tanks.o -o bin/CursedTanks $(SFML_LIBRARIES) -L./lib -lcursedtanks -lpthread

server: Server.o
	$(CPPC) obj/Server.o -o bin/Server $(CPPCFLAGS) -L./lib -lcursedtanks $(SFML_LIBRARIES)

Cursed_Tanks.o: sources/Cursed_Tanks.cpp
	$(CPPC) -c sources/Cursed_Tanks.cpp -o obj/Cursed_Tanks.o $(CPPCFLAGS)

Server.o: sources/Server.cpp
	$(CPPC) -c sources/Server.cpp -o obj/Server.o $(CPPCFLAGS)

assem_lib: objects
	ar -rc lib/libcursedtanks.a $(LIBRARY_O)
	rm *.o

objects:
#	$(CC) $(LIBRARY_C_S) -c $(CCFLAGS)
	$(CPPC) $(LIBRARY_CPP_S) -c $(CPPCFLAGS)

clean_lib:
	rm lib/*.a

create:
	mkdir -p obj bin

clean:
	rm -rdf bin obj *.o
