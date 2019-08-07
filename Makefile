PHONY_N = base clean create obj_lib create_in_lib

LIBRARIES = Get_Map_From_Pix.o
LIBRARIES += Validate_Bullet.o
LIBRARIES += Validate_Tank.o
LIBRARIES += Init_Server.o
LIBRARIES += Connect_To_Client.o
LIBRARIES += Connect_To_Server.o
LIBRARIES += Send.o
LIBRARIES += Recv.o

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
	gcc lib/src/*.c -g -c -std=c99 -I include
	g++ lib/src/*.cpp -g -c -I include

clean_lib:
	rm lib/*.a

create: clean
	mkdir obj
	mkdir bin
clean:
	rm -rdf bin
	rm -rdf obj
