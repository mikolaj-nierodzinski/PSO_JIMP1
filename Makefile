all:
	gcc ./src/*.c -lm -o ./bin/pso && ./bin/pso ./src/test_map.txt -p 50 -i 200 -c ./params.txt -n 3
