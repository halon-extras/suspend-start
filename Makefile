all: suspend-start

suspend-start:
	clang++ -I/opt/halon/include/ -I/usr/local/include/ -fPIC -shared suspend-start.cpp -o suspend-start.so
