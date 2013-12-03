#include "drawing.h"

Drawer * DrawerInit(int width, int height, char fileTypePDF, const char * filePath) {
	Drawer * self = malloc(sizeof(Drawer));
	if(fileTypePDF) {
		self->surface = cairo_pdf_surface_create(filePath, width, height);
	} else {
		self->surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	}
    self->context = cairo_create(self->surface);
    cairo_set_antialias(self->context, CAIRO_ANTIALIAS_BEST);
    return self;
}

void DrawerDestroy(Drawer * self){
	cairo_destroy(self->context);
    cairo_surface_destroy(self->surface);
    free(self);
}

void DrawerDrawRectangle(Drawer * self, Rectangle rect) {
	cairo_save(self->context);
	cairo_set_line_width(self->context, rect.borderWidth);
	cairo_rectangle (self->context, rect.x, rect.y, rect.width, rect.height);
	cairo_set_source_rgba(self->context,
						  rect.bg.r,
						  rect.bg.g,
						  rect.bg.b,
						  rect.bg.a);
	cairo_fill_preserve(self->context);
 	cairo_set_source_rgba(self->context,
 						  rect.border.r,
 						  rect.border.g,
 						  rect.border.b,
 						  rect.border.a);
 	cairo_stroke(self->context);
 	cairo_restore(self->context);
}

void DrawerDrawArc(Drawer * self, Arc arc) {
    cairo_save(self->context);
    cairo_set_line_width(self->context, arc.borderWidth);
    cairo_arc (self->context,
               arc.x,
               arc.y,
               arc.radius,
               arc.initAngle,
               arc.endAngle);
    cairo_line_to(self->context, arc.x, arc.y);
    cairo_arc (self->context,
               arc.x,
               arc.y,
               arc.radius,
               arc.initAngle,
               arc.initAngle);
    cairo_line_to(self->context, arc.x, arc.y);
    cairo_set_source_rgba(self->context,
						  arc.bg.r,
						  arc.bg.g,
						  arc.bg.b,
						  arc.bg.a);
	cairo_fill_preserve(self->context);
 	cairo_set_source_rgba(self->context,
 						  arc.border.r,
 						  arc.border.g,
 						  arc.border.b,
 						  arc.border.a);
 	cairo_stroke(self->context);
    cairo_restore(self->context);
}

void DrawerSave(Drawer * self, char fileTypePDF, const char * filePath) {
	if(fileTypePDF) {
		cairo_show_page(self->context);
	} else {
		cairo_surface_write_to_png(self->surface, filePath);
	}
}
