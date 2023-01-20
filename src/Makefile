all: questions_3 hello

questions_3: questions_3.o controllers.o user_io.o
	g++ -std=c++11 -o questions_3 questions_3.o controllers.o user_io.o

questions_3.o: questions_3.cpp image_menu.h
	g++ -std=c++11 -c questions_3.cpp

controllers.o: controllers.cpp image_menu.h
	g++ -std=c++11 -c controllers.cpp

user_io.o: user_io.cpp image_menu.h
	g++ -std=c++11 -c user_io.cpp

hello: hello.o
	g++ -std=c++11 -o hello hello.o
hello.o: hello.cpp
	g++ -std=c++11 -c hello.cpp