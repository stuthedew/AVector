#include <AVector.h>
#include <Time.h>
#include "printf.h"

//AVector testVector( 10, 30 ) ;



#define X_1 940
#define X_2 970

#define MULT_VAL     273
#define SHIFT_VAL    13
#define CLOCKS_PER_SEC 1000000

const int num_tests = 100;

typedef unsigned long clock_t;

unsigned long clock(){
  return micros();
}

void setup(){
  Serial.begin(9600);
  printf_begin();
  printf("printf test");
testVal(X_1, X_2);


}


void loop(){



}

void testVal( int X1, int X2 ){
  const int x1 = X1;
  const int x2 = X2;

  for(int j = 0; j < 5; j++){
    long TEST_VAL = random() % 1000 + 2000;

    long shiftVal;
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

    t3 = (t1 - t2);
    t3 *= 100;
    Serial.println(TEST_VAL);
    Serial.println(actualVal);
    Serial.println(t1);
    Serial.println(shiftVal);
    Serial.println(t2);
/*
    printf ("Test Value: %i\tActual: %i \t Shift: %i \n",TEST_VAL, actualVal, shiftVal);
    printf ("Float took %d clicks (%f seconds).\n",t1,(t1)/CLOCKS_PER_SEC);
    printf ("Mult/Shift took %d clicks (%f seconds).\n",t2,(t2)/CLOCKS_PER_SEC);

    printf ("Speed boost: %f %% .\n",t3/t1);
    */
  }

}
