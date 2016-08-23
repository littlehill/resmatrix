#include <stdio.h>

int main() {
    
    
    for (int gnd=0;gnd<6;gnd+=1) {
            for (int sig=0;sig<6;sig+=1) {
            printf("N%1d 2700 S%1d\n",gnd,sig);
            }
    }
    
    
    
    
 return 0;   
}
