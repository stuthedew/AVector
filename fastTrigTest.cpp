#include <iostream>
#include <stdio.h>

#include "fastTrig.h"
#include <math.h>

#define TEST_VAL 0.995

#define TRIAL_NUM 10000
typedef struct result_t{
    clock_t
        runTime,
        totalTime;

    double
        val;

    result_t():totalTime(0){}

}result_t;

typedef struct divisor_t{
    const int
        numerator,
        shift;

    divisor_t(int n, int sh):shift(sh),numerator(n){}
}divisor_t;


double tVal = 0;
    clock_t totalTime = clock();
    clock_t t;
    uint64_t rSq = 0;

using namespace std;


int main(int argc, char *argv[]) {
    result_t acosOld, acosFast;
    double testVal;



    for(int i = 0; i < 1000; i++){

        testVal = i;
        testVal /= 1000;

        t = clock();
        for(int j = 0; j < TRIAL_NUM; j++){
            acosOld.val = acos(testVal) *57.3;

        }
          acosOld.runTime = clock() - t;
                acosOld.totalTime += acosOld.runTime;

        t = clock();
        for(int j = 0; j < TRIAL_NUM; j++){

                    acosFast.val = fast_acos(testVal);

                }
                acosFast.runTime = clock() - t;
                        acosFast.totalTime += acosFast.runTime;

    cout << testVal << endl;
    cout << "acos result: " << acosOld.val << endl << "acos time: "<< acosOld.runTime <<endl << endl;
    cout << "fast acos result: " << acosFast.val << endl << "fast acos time: "<< acosFast.runTime <<endl << endl << endl;

    }
    cout << "Old time: " << acosOld.totalTime << endl;
    cout << "New Time: " << acosFast.totalTime << endl;

}
