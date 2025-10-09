all: main test_unit test_e2e

main:
	gcc main.c -o main.exe

test_unit:
	gcc tests/test_unit.c -o tests/test_unit.exe

test_e2e:
	gcc tests/test_e2e.c -o tests/test_e2e.exe

run_main: main
	./main.exe

run_unit: test_unit
	./tests/test_unit.exe

run_e2e: test_e2e
	./tests/test_e2e.exe

clean:
	rm -f main.exe tests/test_unit.exe tests/test_e2e.exe
