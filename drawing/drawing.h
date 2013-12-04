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

struct _color {
	float r, g, b, a;
};

typedef struct _color Color;

struct _rectangle {
	int x;
	int y;
	float width;
	float height;
	float borderWidth;
	Color bg;
	Color border;
};

typedef struct _rectangle Rectangle;

struct _arc {
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

struct _text {
	float fontSize;
	int textX;
	int textY;
	const char * label;
	float borderWidth;
	int spaceLegend;
	Color bg;
	Color border;
};


typedef struct _text Text;

Drawer * DrawerInit(int width, int height, char fileTypePDF, const char * filePath);
void DrawerDestroy(Drawer * self);
void DrawerDrawRectangle(Drawer * self, Rectangle rect);
void DrawerDrawArc(Drawer * self, Arc arc);
void DrawerDrawTextArc(Drawer * self, Text text, Arc arc, Rectangle rect);
void DrawerDrawTextRect(Drawer * self, Text text, Rectangle rect2, Rectangle rect);
void DrawerSave(Drawer * self, char fileTypePDF, const char * filePath);
