# This is my first LLVM PASS exercise #

my codes are modified from `llvm-3.2.src/lib/Transforms/Hello/Hello.cpp`


## build ##

### Makefile ###

    $ make
    clang -c mypass.cpp -o mypass.o `llvm-config --cppflags` -fPIC -fno-rtti
    clang -shared mypass.o -o mypass.so `llvm-config --ldflags`


## test ##

a test loop example

`$ cat hello.c`
    
    #include <stdio.h>
    #include <stdlib.h>
    
    void myfun (void) {
        puts("enter myfunc()");
        for (int i = 0; i < 10; i++) {
            printf("QQ XD Orz %d\n", i);
        }
        puts("leave myfunc()");
    }
    int main (void) {
        puts("in main");
        myfun();
        puts("after myfunc()");
        return 0;
    }



compile to llvm bitcode

`$ clang -c -emit-llvm hello.c -o hello.bc`

the behavior of hello.c

`$ lli hello.bc`

    in main
    enter myfunc()
    QQ XD Orz 0
    QQ XD Orz 1
    QQ XD Orz 2
    QQ XD Orz 3
    QQ XD Orz 4
    QQ XD Orz 5
    QQ XD Orz 6
    QQ XD Orz 7
    QQ XD Orz 8
    QQ XD Orz 9
    leave myfunc()
    after myfunc()



- use mypass to analysis it 

`$ opt -load ./mypass.so - mypass1 ./hello.bc -disable-output`

    my pass: (runOn) 'myfun'  
    my pass: (runOn) 'main'



- use mypass2 to analysis it!

`$ opt -load ./mypass.so -mypass2 ./hello.bc -disable-output`

    my pass2: (doInit)myfun
    my pass2: (runOn), myParent = myfun
    my pass2: (runOn), myParent = myfun
    my pass2: (runOn), myParent = myfun
    my pass2: (runOn), myParent = myfun
    my pass2: (runOn), myParent = myfun
    my pass2: (doFin)myfun
    my pass2: (doInit)main
    my pass2: (runOn), myParent = main
    my pass2: (doFin)main

