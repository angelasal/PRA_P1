bin/testListArray: testListArray.cpp ListArray.h List.h
	mkdir -p bin
	g++ -o bin/testListArray testListArray.cpp

bin/testNode: testNode.cpp Node.h
	mkdir -p bin
	g++ -o bin/testNode testNode.cpp

bin/testListLinked: testListLinked.cpp ListLinked.h Node.h
	mkdir -p bin
	g++ -o bin/testListLinked testListLinked.cpp
clean:
	rm -r *.o *.gch bin
