#include <stdio.h>
#include "MathFuncs.h"

using namespace std;

int main()
{
	MyMathFuncs *m = new MyMathFuncs();
	double c = m->Add(10.1, 20.2);

	printf("Result is %f\n", c);
	free(m);
	return 0;
}