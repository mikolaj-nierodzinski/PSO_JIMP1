all:
	gcc ./src/*.c -o ./bin/pso && ./bin/pso ./src/test_map.txt -p 50 -i 200 ./params.txt -n 3