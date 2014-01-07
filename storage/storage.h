#include <jansson.h>
#include <stdio.h>
#include <string.h>

enum {PNG, PDF};

struct _datum {//Definindo Struct responsável pela Porcentagem e Rótulo dos Parâmetros do .json
	double percentage;
	const char * label;
};
typedef struct _datum Datum;

struct _chart {//Definindo Struct responsável pelos Parâmetros do gráfico
	const char * filePath;
	char fileType;
	const char * chartName;
	int width;
	int height;
	const char * chartType;
	int DatumSize;
	float Sum_Percentages;
	Datum ** content;
};
typedef struct _chart Chart;

char * createFilePath(const char * fileName, const char *fileType);
void type(char * string, char * type);
int compare(char * one, char * two);
float sort(float * array, Chart * chart);
Chart * ChartCreate(char * filePath);
int SpaceValue(int x);

