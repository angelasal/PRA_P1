
bin/testListArray: testListArray.cpp ListArray.h List.h
	mkdir -p bin
	g++ -std=c++17 -Wall -o bin/testListArray testListArray.cpp

bin/testNode: testNode.cpp Node.h
	mkdir -p bin
	g++ -std=c++17 -Wall -o bin/testNode testNode.cpp
	
clean:
	rm -rf bin *.o *.gch


