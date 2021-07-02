all: suspend-start

suspend-start:
	g++ -I/opt/halon/include/ -I/usr/local/include/ -fPIC -shared suspend-start.cpp -o suspend-start.so
