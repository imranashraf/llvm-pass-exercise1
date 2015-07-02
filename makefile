LLVM_SRC_PATH := /data/repositories/llvmRepo/llvm
LLVM_BUILD_PATH := /data/repositories/llvmRepo/build

CLANG_INCLUDES := \
	-I$(LLVM_SRC_PATH)/tools/clang/include \
	-I$(LLVM_BUILD_PATH)/tools/clang/include

# List of Clang libraries to link. The proper -L will be provided by the
# call to llvm-config
# Note that I'm using -Wl,--{start|end}-group around the Clang libs; this is
# because there are circular dependencies that make the correct order difficult
# to specify and maintain. The linker group options make the linking somewhat
# slower, but IMHO they're still perfectly fine for tools that link with Clang.
CLANG_LIBS := \
	-Wl,--start-group \
	-lclangAST \
	-lclangAnalysis \
	-lclangBasic \
	-lclangDriver \
	-lclangEdit \
	-lclangFrontend \
	-lclangFrontendTool \
	-lclangLex \
	-lclangParse \
	-lclangSema \
	-lclangEdit \
	-lclangASTMatchers \
	-lclangRewrite \
	-lclangRewriteFrontend \
	-lclangStaticAnalyzerFrontend \
	-lclangStaticAnalyzerCheckers \
	-lclangStaticAnalyzerCore \
	-lclangSerialization \
	-lclangToolingCore \
	-lclangTooling \
	-Wl,--end-group

LLVM_CONFIG=llvm-config

CXX=clang++
CXXFLAGS=`$(LLVM_CONFIG) --cppflags` -fPIC -fno-rtti -std=c++11 $(CLANG_INCLUDES)
LDFLAGS= $(CLANG_LIBS) `$(LLVM_CONFIG) --ldflags`

all: mypass.so

mypass.so: mypass.o
	$(CXX) -shared mypass.o -o mypass.so $(LDFLAGS)
			 
mypass.o: mypass.cpp
	$(CXX) -c mypass.cpp -o mypass.o $(CXXFLAGS)
			 
clean:
	rm -f *.o mypass.so *~ test.bc

test.bc: test.c
	clang -c -emit-llvm test.c -o test.bc	

test.ll:test.c
	clang -S -emit-llvm test.c 

run: mypass.so test.bc
	opt -load ./mypass.so -mypass6 ./test.bc -disable-output
	
