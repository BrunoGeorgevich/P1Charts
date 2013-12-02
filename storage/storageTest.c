#include <stdio.h>
#include "storage.h"

int main() {
	printf("Hello storage!\n");
	ChartDetails * test = ChartDetailsCreate("../test.json");
	return 0;
}
