

all:
	g++ -I/usr/include/opencv testopencv.cpp -o testopencv `pkg-config opencv --libs`-lstdc++

clean:
	rm -f testopencv


