LLVM_CONFIG=llvm-config
 
CXX=clang
CXXFLAGS=`$(LLVM_CONFIG) --cppflags` -fPIC -fno-rtti
LDFLAGS=`$(LLVM_CONFIG) --ldflags`
  
all: mypass.so
	 
mypass.so: mypass.o
	        $(CXX) -shared mypass.o -o mypass.so $(LDFLAGS)
			 
mypass.o: mypass.cpp
	        $(CXX) -c mypass.cpp -o mypass.o $(CXXFLAGS)
			 
clean:
	        rm -f *.o mypass.so
