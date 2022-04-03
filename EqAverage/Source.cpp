#include "TestLibrary.h"



int  main(int args,char* argv[]) {
	int array[] = { 1,2,3 };
	int n = sizeof(array) / sizeof(int);
	verifier::Verifier v(array, n);
	v.showArrayValue();
	printf("%d\n", v.verify());
	//testLibrary::test();
	return 0;
}