#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>


#define X1 940
#define X2 970

#define MULT_VAL     273
#define SHIFT_VAL    13

const long num_tests = 10000000;


using namespace std;
int main(int argc, char *argv[]) {
    const int x1 = X1;
    const int x2 = X2;
   
    
    
   for(int j = 0; j < 5; j++){ 
    int TEST_VAL = rand() % 10000 + 2000;
    
    int shiftVal;
        float actualVal;
        clock_t t1, t2, ct;
        long t3;
    
    t1 = clock();
    for(int i = 0; i < num_tests; i++){
    actualVal = round((float)TEST_VAL / (x2 - x1));
    }
    
    t1 = clock() - t1;
    t2 = clock();
        for(int i = 0; i < num_tests; i++){
            shiftVal = (TEST_VAL * MULT_VAL );
            shiftVal += (1 << (SHIFT_VAL)) >> 1;
            shiftVal >>= SHIFT_VAL;
        }
        
        t2 = clock() - t2;
        
        t3 = (float)(t1 - t2);
        t3 *= 100;
       
    
    printf ("Test Value: %i\tActual: %f \t Shift: %i \n",TEST_VAL, actualVal, shiftVal);
    printf ("Float took %d clicks (%f seconds).\n",t1,((float)t1)/CLOCKS_PER_SEC);
    printf ("Mult/Shift took %d clicks (%f seconds).\n",t2,((float)t2)/CLOCKS_PER_SEC);
    
    printf ("Speed boost: %f %% .\n",(float)t3/t1);
}
    
}