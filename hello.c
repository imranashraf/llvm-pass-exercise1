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
