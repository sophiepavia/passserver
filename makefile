all: sproj5.x proj5.x

proj5.x: proj5.o passserver.o hashtable.h
	g++ -o proj5.x proj5.o passserver.o -std=c++11 -lcrypt
sproj5.x: sproj5.o passserver.o hashtable.h
	g++ -o sproj5.x sproj5.o passserver.o -std=c++11 -lcrypt
sproj5.o: sproj5.cpp passserver.h hashtable.h
	g++ -c sproj5.cpp -std=c++11 -lcrypt
proj5.o: proj5.cpp passserver.h hashtable.h
	g++ -c proj5.cpp -std=c++11 -lcrypt
passserver.o: passserver.cpp passserver.h
	g++ -c passserver.cpp -std=c++11 -lcrypt
clean:
	rm *.o
