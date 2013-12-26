#include <cairo/cairo.h>
#include <cairo/cairo-pdf.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>

struct _drawer {
	cairo_surface_t *surface;
    cairo_t * context;
};

typedef struct _drawer Drawer;

struct _color {//Definindo a Struct responsável pelas cores
	float r, g, b, a;
};

typedef struct _color Color;

struct _rectangle {//Definindo a Struct responsável pelos Retângulos
	int x;
	int y;
	float width;
	float height;
	float borderWidth;
	Color bg;
	Color border;
};

typedef struct _rectangle Rectangle;

struct _arc {//Definindo a Struct responsável pelos Arcos
    int x;
    int y;
	double initAngle;
	double endAngle;
	float radius;
	float borderWidth;
	Color bg;
	Color border;
};

typedef struct _arc Arc;

struct _arrow {//Definindo a Struct responsável pelas Setas
	int x0r;
	int y0r;
	int x0l;
	int y0l;
	int x;
	int y;
	float arrowWidth;
	Color bg;
};

typedef struct _arrow Arrow;

struct _axis {//Definindo a Struct responsável pelos Eixos
	int x0;
	int y0;
	int x;
	int y;	
	float axisWidth;
	Color bg;
};

typedef struct _axis Axis;

struct _text {//Definindo a Struct responsável pelos Textos
	float fontSize;
	int x;
	int y;
	const char * label;
	const char * percentage;
	float borderWidth;
	int spaceLegend;
	int spacePercentage;
	int percx;
	int percy;
	int rect;
	int arc;
	Color bg;
	Color border;	
	Color Percbg;
};


typedef struct _text Text;

struct _title {//Definindo a Struct responsável pelo Título
	float fontSize;
	const char * title;
	Color bg;
};

typedef struct _title Title;

Drawer * DrawerInit(int width, int height, char fileTypePDF, const char * filePath);
void DrawerDrawArrow (Drawer * self, Axis axis, Arrow arrow);
void DrawerDestroy(Drawer * self);
void DrawerDrawRectangle(Drawer * self, Rectangle rect);
void DrawerDrawArc(Drawer * self, Arc arc);
void DrawerDrawText(Drawer * self, Text text, Rectangle rect);
void DrawerSave(Drawer * self, char fileTypePDF, const char * filePath);
void randColor(Color * color);
void DrawerDrawTextTitle(Drawer * self, Title title,  Rectangle rect);
void DrawerDrawAxis(Drawer * self, Axis axis, Rectangle rect);
