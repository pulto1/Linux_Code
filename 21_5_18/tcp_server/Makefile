
FLAG=-std=c++11 -lpthread

.PHONY:all
all:tcpClient tcpServer

tcpClient:tcpClient.cc
	g++ -o $@ $^ $(FLAG) -static
tcpServer:tcpServer.cc
	g++ -o $@ $^ $(FLAG) -g

.PHONY:clean
clean:
	rm -f tcpClient tcpServer
