main:
	g++ -O2 -c LED_strip.cpp -o LED_strip.o
	g++ -O2 -c main_example.cpp -o main_example.o
	g++ -O2 LED_strip.o main_example.o -o main_example
clean:
	rm -rf ./main_example
	rm -rf ./*.o
