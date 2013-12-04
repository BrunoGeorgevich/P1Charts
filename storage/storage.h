#include <jansson.h>
#include <stdio.h>
#include <string.h>

enum {PNG, PDF};

struct _datum {
	double percentage;
	const char * label;
};
typedef struct _datum Datum;

struct _chart {
	const char * filePath;
	char fileType;
	int width;
	int height;
	const char * chartType;
	Datum ** content;
};
typedef struct _chart Chart;

char * createFilePath(const char * fileName, const char *fileType);
Chart * ChartCreate(char * filePath);

