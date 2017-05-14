#include <stdio.h>




int main(){
int *pt;
int x;
x = 3;
pt = x;
    printf("%d\n", x);

func1(pt);

    printf("%d\n", x);



    
    
    return 0;
}

void func1(int x){

    x = 4;
    printf("%d\n", x);



}
