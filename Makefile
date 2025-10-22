bin/testListArray: testListArray.cpp ListArray.h List.h
	mkdir -p bin
	g++ -std=c++17 -Wall -o bin/testListArray testListArray.cpp

bin/testNode: testNode.cpp Node.h
	mkdir -p bin
	g++ -std=c++17 -Wall -o bin/testNode testNode.cpp
	
clean:
	rm -rf bin *.o *.gch

Point2D.o: Point2D.h Point2D.cpp
	g++ -c Point2D.cpp

testPoint2D.o: testPoint2D.cpp Point2D.h
	g++ -c testPoint2D.cpp

bin/testPoint2D: testPoint2D.o Point2D.o
	mkdir -p bin
	g++ -o bin/testPoint2D testPoint2D.o Point2D.o

Shape.o: Shape.h Shape.cpp
	g++ -c Shape.cpp


bin/testCircle: testCircle.cpp Circle.o Shape.o Point2D.o
	g++ -c testCircle.cpp
	mkdir -p bin
	g++ -o bin/testCircle testCircle.o Circle.o Shape.o Point2D.o