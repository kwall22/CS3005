
all: ascii_image questions_3 hello

ascii_image: ascii_image.o image.o controllers.o image_drawing.o image_output.o user_io.o
	g++ -std=c++11 -o ascii_image ascii_image.o image.o controllers.o image_drawing.o image_output.o user_io.o

image.o: image.cpp Image.h
	g++ -std=c++11 -c image.cpp

ascii_image.o: ascii_image.cpp image_menu.h
	g++ -std=c++11 -c ascii_image.cpp

image_drawing.o: image_drawing.cpp image_menu.h Image.h
	g++ -std=c++11 -c image_drawing.cpp

image_output.o: image_output.cpp image_menu.h Image.h
	g++ -std=c++11 -c image_output.cpp	

questions_3: questions_3.o controllers.o user_io.o image_drawing.o image_output.o image.o
	g++ -std=c++11 -o questions_3 questions_3.o controllers.o user_io.o image_drawing.o image_output.o image.o

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

#removes .o files and the text file versions of cpp's 
clean:
	-rm -f *.o
	-rm -f hello
	-rm -f questions_3
	-rm -f ascii_image