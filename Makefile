build:
	gcc *.c -o tema1 -std=c11
run:
	./tema1
clear:
	rm tema1
valgrind:
	valgrind --leak-check=yes --track-origins=yes ./tema1