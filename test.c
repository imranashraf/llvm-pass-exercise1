#include <stdio.h>
#include <stdlib.h>

struct Book{
    int pages;
    char name[10];
};

int aFunc(int par)
{
    int sum=0;
    struct Book books[25];

    puts("aFunc()");
    for (int i = 0; i < 10; i++)
    {
        int fact=par*2;
        sum=sum+i+fact;
        books[i].pages=i;
    }
    printf("%d",sum);
    return sum;
}


void myfun(void)
{
    int sum=0;
    int *Arr = malloc( 100*sizeof(int) );

    puts("enter myfunc()");
    for (int i = 0; i < 10; i++)
    {
        printf("QQ XD Orz %d\n", i);
        sum = aFunc(i);
    }

    for (int i = 0; i < 10; i++)
    {
        short fact =2;
        for (int j = 0; j < 10; j++)
        {
            Arr[i] = i*fact;
        }
    }

    printf(" sum %d\n", sum);

    puts("leave myfunc()");
}


int main (void)
{
    puts("in main");
    myfun();
    puts("after myfunc()");
    return 0;
}
