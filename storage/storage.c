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

const char * JsonGetStringAttribute(json_t *root, const char * attName) {
	json_t * jAtt = json_object_get(root, attName);
    const char * result = json_string_value(jAtt);
    free(jAtt);
    return result;
}

int JsonGetIntAttribute(json_t *root, const char * attName) {
	json_t * jAtt = json_object_get(root, attName);
    int result = json_integer_value(jAtt);
    free(jAtt);
    return result;
}

float JsonGetFloatAttribute(json_t *root, const char * attName) {
	json_t * jAtt = json_object_get(root, attName);
    float result = json_real_value(jAtt);
    free(jAtt);
    return result;
}

char * createFilePath(const char * fileName, const char *fileType) {
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
	 chart->chartType = JsonGetStringAttribute(root, "chartType");
	 chart->chartName = JsonGetStringAttribute(root, "chartName");
	 json_t * jcontent = json_object_get(root, "content");
	 chart->content = malloc(sizeof(Datum *)*json_array_size(jcontent) + 1);
	 int i;
	for(i = 0; i < json_array_size(jcontent); ++i){
        json_t *jDatum = json_array_get(jcontent, i);
        chart->content[i] = malloc(sizeof(Datum));
		chart->content[i]->label = JsonGetStringAttribute(jDatum, "label");
		chart->content[i]->percentage = JsonGetFloatAttribute(jDatum, "percentage");
	}
	chart->content[i] = 0;
	ChartPrint(chart);
    return chart;
}
