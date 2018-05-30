all: clean data_generator nn

data_generator:
	g++ -o data_generator data_generator.cpp

nn:
	g++ -o nn main.cpp net.cpp neuron.cpp reader.cpp

clean:
	rm -f nn data_generator
	rm -f *.txt
