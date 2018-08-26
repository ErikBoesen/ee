all: clean nn

nn:
	g++ -std=c++11 -o nn main.cpp net.cpp neuron.cpp reader.cpp

debug:
	g++ -g -std=c++11 -o nn main.cpp net.cpp neuron.cpp reader.cpp

clean:
	rm -f nn
