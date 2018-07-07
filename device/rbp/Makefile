FLAGS=-pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm -std=c++11 -O2 -lm -lwiringPi -lssl
COMPILLER=g++

all: start

start: basfunctions.o actions.o main.o
	$(COMPILLER) $(FLAGS) -o phm-device basfunctions.o actions.o main.o

main.o: main.cpp
	$(COMPILLER) -c $(FLAGS) main.cpp

actions.o: actions.cpp
	$(COMPILLER) -c $(FLAGS) actions.cpp

basfunctions.o: basfunctions.cpp
	$(COMPILLER) -c $(FLAGS) basfunctions.cpp

clean:
	@-rm -f *.o *.gch *.dat watcher
	@echo "Clean success"
