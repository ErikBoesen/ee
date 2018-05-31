all: clean nn

nn:
	g++ -o nn main.cpp net.cpp neuron.cpp reader.cpp

clean:
	rm -f nn data_generator
	rm -f *.txt
