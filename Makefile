PHONY_N = base clean create obj_lib create_in_lib
LIBRARIES = map.o
.PHONY: $(PHONY_N)

all: base

base: create Cursed_Tanks.o
	g++ obj/Cursed_Tanks.o -o bin/CursedTanks -g -lsfml-graphics -lsfml-window -lsfml-system -L./lib -l cursedtanks

Cursed_Tanks.o: sources/Cursed_Tanks.cpp
	gcc sources/Cursed_Tanks.cpp -o obj/Cursed_Tanks.o -g -c -I include

assem_lib: obj_lib
	ar -rc lib/libcursedtanks.a $(LIBRARIES)
	rm *.o

obj_lib:
	gcc lib/src/*.c -g -c -I include
	g++ lib/src/*.cpp -g -c -I include

clean_lib:
	rm lib/*.a

create: clean
	mkdir obj
	mkdir bin
clean:
	rm -rdf bin
	rm -rdf obj
