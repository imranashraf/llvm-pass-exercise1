LLVM_CONFIG=llvm-config

CXX=clang++
CXXFLAGS=`$(LLVM_CONFIG) --cppflags` -fPIC -fno-rtti -std=c++11
LDFLAGS=`$(LLVM_CONFIG) --ldflags`

all: mypass.so

mypass.so: mypass.o
	$(CXX) -shared mypass.o -o mypass.so $(LDFLAGS)
			 
mypass.o: mypass.cpp
	$(CXX) -c mypass.cpp -o mypass.o $(CXXFLAGS)
			 
clean:
	rm -f *.o mypass.so *~ hello.bc

hello.bc: hello.c
	clang -c -emit-llvm hello.c -o hello.bc	

run: hello.bc
	opt -load ./mypass.so -mypass1 ./hello.bc -disable-output
	
