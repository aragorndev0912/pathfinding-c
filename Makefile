APP 		:= path
C 			:= gcc
CFLAGS 	:= -Wall -pedantic -std=c99

ifdef RELEASE
	CFLAGS += -O3
else
	CFLAGS += -g
endif

.PHONY: clean

$(APP): main.o lib.o map.o
	$(C) -o $(APP) main.o lib.o map.o $(CFLAGS)

main.o: main.c
	$(C) -c main.c $(CFLAGS)

lib.o: src/lib.c
	$(C) -c src/lib.c $(CFLAGS)

map.o: src/map.c
	$(C) -c src/map.c $(CFLAGS)

clean:
	rm *.o
	rm $(APP)