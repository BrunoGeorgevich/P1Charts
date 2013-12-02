#include <cairo/cairo.h>
#include <cairo/cairo-pdf.h>
#include <stdlib.h>

struct _cairo_definition {
	cairo_surface_t *surface;
    cairo_t * context;
};

typedef struct _cairo_definition CairoDef;

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

CairoDef * CairoDefInit(int width, int height, char fileTypePDF, const char * filePath);
void CairoDefDestroy(CairoDef * self);
void CairoDefDrawRectangle(CairoDef * self, Rectangle rect);
void CairoDefSave(CairoDef * self, char fileTypePDF, const char * filePath);
