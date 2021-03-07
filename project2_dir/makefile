#
# PROGRAM: Mircroshell
# AUTHOR: Cortland Ervins
#

CXXFLAGS = -ansi -pedantic -Wall  -Wextra -std=c++14

main: main.o
	g++ $(CXXFLAGS) -c -o main.o main.cpp
	g++ $(CXXFLAGS) -c -o ls_sys.o ls_sys.cpp
	g++ $(CXXFLAGS) -o z1813736_project2 main.o ls_sys.o
    
clean:
	rm -f *.o main z1813736_project2
