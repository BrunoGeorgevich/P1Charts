#include "storage.h"

ChartDetails * ChartDetailsInit() {
	ChartDetails * chartDetails = malloc(sizeof(ChartDetails));
	return chartDetails;
}

void DatumPrint(Datum * datum) {
	printf("##### Datum %p\n", datum);
	printf("### Label: %s\n", datum->label);
	printf("### Percentage: %.2lf\n", datum->percentage);
	printf("#########################\n");
}

void ChartDetailsPrint(ChartDetails * chart) {
	printf("#########################\n");
	printf("### Chart %p\n", chart);
	printf("#------------------------\n");
	printf("# FileName: %s\n", chart->fileName);
	printf("# FileType: %s\n", chart->fileType);
	printf("# Width: %d\n", chart->width);
	printf("# Height: %d\n", chart->height);
	printf("#########################\n");
	for(int i = 0; chart->content[i] != 0; ++i) {
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
	//printf("JsonGetFloatAttribute:Is real? %d\n", json_is_real(jAtt));
    float result = json_real_value(jAtt);
    free(jAtt);
    return result;
}

ChartDetails *ChartDetailsCreate(char * filePath) {
	ChartDetails *chart = ChartDetailsInit();
	json_t *root;
    json_error_t error;
    root = json_load_file("../test.json", 0, &error);
    if(!root){
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        return 0;
    }
    chart->fileName = JsonGetStringAttribute(root, "fileName");
    chart->fileType = JsonGetStringAttribute(root, "fileType");
    chart->width = JsonGetIntAttribute(root, "width");
    chart->height = JsonGetIntAttribute(root, "height");

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
	ChartDetailsPrint(chart);
    return chart;
}
