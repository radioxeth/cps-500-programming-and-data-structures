#include <stdio.h>

int main(){
    int n = 5;
    int sum=0;
    for(int i =1;i<=n;++i){
        sum+=i;
    }
    printf("%d",sum);
    return 0;
}