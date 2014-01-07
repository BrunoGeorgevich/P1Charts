#include "storage.h"

Chart * ChartInit() {
	Chart * chartDetails = malloc(sizeof(Chart));
	return chartDetails;
}

void DatumPrint(Datum * datum) {
	printf("##### Datum %p\n", datum);
	printf("### Label: %s\n", datum->label);
	printf("### Percentage: %.2lf\n", datum->percentage);
	printf("#########################\n");
}

void ChartPrint(Chart * chart) {
	printf("#########################\n");
	printf("### Chart %p\n", chart);
	printf("#------------------------\n");
	printf("# FilePath: %s\n", chart->filePath);
	printf("# FileType: %s\n", (chart->fileType == 0 ? "png" : "pdf"));
	printf("# Width: %d\n", chart->width);
	printf("# Height: %d\n", chart->height);
	printf("#########################\n");
	int i;
	for(i = 0; chart->content[i] != 0; ++i) {
		DatumPrint(chart->content[i]);
	}
}

const char * JsonGetStringAttribute(json_t *root, const char * attName) {//Função da Biblioteca Jansson que extrai 																										  strings dos arquivos .json
	json_t * jAtt = json_object_get(root, attName);
    const char * result = json_string_value(jAtt);
    free(jAtt);
    return result;
}

int JsonGetIntAttribute(json_t *root, const char * attName) {//Função da Biblioteca Jansson que extrai 																						  Inteiros dos arquivos .json
	json_t * jAtt = json_object_get(root, attName);
    int result = json_integer_value(jAtt);
    free(jAtt);
    return result;
}

float JsonGetFloatAttribute(json_t *root, const char * attName) {//Função da Biblioteca Jansson que extrai 																								Números do Tipo Ponto Flutuante dos arquivos .json
	json_t * jAtt = json_object_get(root, attName);
    float result = json_real_value(jAtt);
    free(jAtt);
    return result;
}

char * createFilePath(const char * fileName, const char *fileType) {//Função que uni o Nome do Arquivo com 																									 Seu tipo	(.Tipo)
	char * filePath = malloc(strlen(fileName) + strlen(fileType) + 3);
	sprintf(filePath, "%s.%s", fileName, fileType);
	return filePath;
}

Chart *ChartCreate(char * filePath) {
	Chart *chart = ChartInit();
	json_t *root;
    json_error_t error;
    root = json_load_file(filePath, 0, &error);
    if(!root){
        fprintf(stderr, "P1Charts:Storage:ChartCreate:Error:%s\n", error.text);
        exit(1);
    }
    const char *fileType = JsonGetStringAttribute(root, "fileType");
    chart->fileType = (strcmp("png",fileType) == 0 ? 0: 1);
    chart->filePath = createFilePath(JsonGetStringAttribute(root, "fileName"),
									 fileType);
    chart->width = JsonGetIntAttribute(root, "width");
    chart->height = JsonGetIntAttribute(root, "height");
	 chart->chartType = JsonGetStringAttribute(root, "type");
	 chart->chartName = JsonGetStringAttribute(root, "name");
	 json_t * jcontent = json_object_get(root, "content");
	 chart->content = malloc(sizeof(Datum *)*json_array_size(jcontent) + 1);
	 chart->DatumSize = json_array_size(jcontent);
	 chart->Sum_Percentages = 0;
	 int i;
	for(i = 0; i < chart->DatumSize; ++i){
        json_t *jDatum = json_array_get(jcontent, i);
        chart->content[i] = malloc(sizeof(Datum));
		chart->content[i]->label = JsonGetStringAttribute(jDatum, "label");
		chart->content[i]->percentage = JsonGetFloatAttribute(jDatum, "percentage");
		chart->Sum_Percentages += chart->content[i]->percentage;
	}
	chart->content[i] = 0;
	ChartPrint(chart);
    return chart;
}
	void type(char * string, char * type) {//Função que extrai o tipo dos parâmetros de entrada
		int cont;
		for(cont = 0; ;cont++) {
		 if(string[cont] == '.') {
		  break;
		 }
}
		int length = strlen(string);
		int aux, aux2;
		for(aux = cont,aux2 = 0; aux <= length ; aux++, aux2++) {
		type[aux2] = string[aux];
		  
		}
}
	int compare(char * one, char * two) {//Função que compara os arquivos com o .json
		return strcmp(one, two);
}
	float sort(float * array, Chart * chart) {//Função que ordena em ordem crescente os parâmetros do Datum, de acordo com 																  sua porcentagem
		int cont, aux2;
		float aux;
		int i = chart -> DatumSize;
		for(cont = 1;cont < i ; cont++) {
		 if(array[cont-1] > array[cont]) {
		aux = array[cont];
		array[cont] = array[cont-1];
		array[cont-1] = aux;
	}
}
	
		for(aux2 = 1;aux2 < i ; aux2++) {
		 if(array[aux2-1] > array[aux2]) {
		 sort(array, chart);
		}
	return array[cont-1];
	}
}
	int SpaceValue(int x) {//Função que regula o espaço entre as barras do Gráfico de barras
		switch(x) {
		 case 1:
			return 1;
		 	break;
		 case 2:
			return 33;
		 	break;
		 case 3:
			return 22;
		 	break;
		 case 4:
			return 16;
		 	break;
		 case 5:
			return 13;
		 	break;
	}
}
