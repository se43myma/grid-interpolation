FLAGS = -O3 -Wall -Winline -Wshadow -std=c++17

intug: main.o unstructured_grid.o intermediate_grid.o interpolation.o
	g++ $(FLAGS) -o intug main.o unstructured_grid.o intermediate_grid.o interpolation.o
intug_bonus: main_bonus.o unstructured_grid.o intermediate_grid.o interpolation.o
	g++ $(FLAGS) -o intug_bonus main_bonus.o unstructured_grid.o intermediate_grid.o interpolation.o
main.o: ../03.source/main.cpp ../02.include/unstructured_grid.h
	g++ $(FLAGS) -c ../03.source/main.cpp
main_bonus.o: ../03.source/main_bonus.cpp ../02.include/unstructured_grid.h
	g++ $(FLAGS) -c ../03.source/main_bonus.cpp
unstructured_grid.o: ../03.source/unstructured_grid.cpp ../02.include/unstructured_grid.h
	g++ $(FLAGS) -c ../03.source/unstructured_grid.cpp
intermediate_grid.o: ../03.source/intermediate_grid.cpp ../02.include/intermediate_grid.h
	g++ $(FLAGS) -c ../03.source/intermediate_grid.cpp
interpolation.o: ../03.source/interpolation.cpp ../02.include/interpolation.h
	g++ $(FLAGS) -c ../03.source/interpolation.cpp
clean:
	rm -rf *.o intug intug_bonus ../05.outputs/*.vtk
