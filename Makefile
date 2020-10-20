compilethis: main.cpp
	 g++ -std=c++11 main.cpp -I /opt/X11/include -I /usr/local/include -L /opt/X11/lib -lX11 -ljpeg -lpng -lz 	

run:
	./a.out

clean:
	rm a.out

