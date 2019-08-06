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

base: main.o
	g++ obj/main.o -o bin/CursedTanks.bin -g -lsfml-graphics -lsfml-window -lsfml-system -L./lib -l cursedtanks

main.o: sources/main.cpp
	gcc sources/main.cpp -o obj/main.o -c -I include

assem_lib: obj_lib
	ar -rc lib/libcursedtanks.a $(LIBRARIES)
	rm *.o

obj_lib:
	gcc lib/src/*.c -c -I include

create: clean
	mkdir obj
	mkdir bin
clean:
	rm -rdf bin
	rm -rdf obj
