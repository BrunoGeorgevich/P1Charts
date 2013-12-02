#include <stdio.h>
#include "storage.h"

int main() {
	printf("Hello storage!\n");
	Chart * test = ChartCreate("../test.json");
	return 0;
}
