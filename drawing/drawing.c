#include "drawing.h"

Drawer * DrawerInit(int width, int height, char fileTypePDF, const char * filePath) {
	Drawer * self = malloc(sizeof(Drawer));
	if(fileTypePDF) {
		self->surface = cairo_pdf_surface_create(filePath, width, height);
	} else {
		self->surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	}
    self->context = cairo_create(self->surface);
    return self;
}

void DrawerDestroy(Drawer * self){
	cairo_destroy(self->context);
    cairo_surface_destroy(self->surface);
    free(self);
}
void RandColor(Color * color) {
	color->r = (rand()%9999999);
	color->g = (rand()%9999999);
	color->b = (rand()%9999999);
}

void TextPlus(char str[100], char aux[100]) {
		strcat(str,aux);
}

void DrawerDrawAxis(Drawer * self, Axis axis, Rectangle rect) {
	cairo_save(self->context);
	cairo_set_line_width(self->context, axis.axisWidth);
	cairo_move_to(self->context, axis.x0, axis.y0);
	cairo_line_to(self->context, axis.x, axis.y);
	cairo_set_source_rgba(self->context,
						  axis.bg.r,
						  axis.bg.g,
						  axis.bg.b,
						  axis.bg.a);
	cairo_fill_preserve(self->context);
	cairo_stroke(self->context);
	cairo_restore(self->context);
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


void DrawerDrawText(Drawer * self, Text text,  Rectangle rect) {
	float x, y;	
	cairo_save(self->context);	
	cairo_text_extents_t extents;
	cairo_select_font_face (self->context, "Arial", CAIRO_FONT_SLANT_NORMAL,
                               CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size (self->context, text.fontSize);
	cairo_set_source_rgba(self->context, 
													text.bg.r,
													text.bg.g,
													text.bg.b,
													text.bg.a);
   cairo_text_extents (self->context,text.label, &extents);	
	x = text.x-(extents.width/2 + extents.x_bearing);
	y = text.y-(extents.height/2 + extents.y_bearing);
   cairo_line_to(self->context, x, y+text.spaceLegend);
	cairo_text_path (self->context,text.label);
	cairo_fill_preserve(self->context);
	cairo_set_source_rgba(self->context, 
													text.border.r,
													text.border.g,
													text.border.b,
													text.border.a);
	cairo_set_line_width(self->context, text.borderWidth);
	cairo_stroke(self->context);
	cairo_select_font_face (self->context, "Arial", CAIRO_FONT_SLANT_NORMAL,
                               CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size (self->context, text.fontSize);
	cairo_set_source_rgba(self->context, 
													text.Percbg.r,
													text.Percbg.g,
													text.Percbg.b,
													text.Percbg.a);
	x = text.percx-(extents.height/2 + extents.y_bearing)*text.rect;
	y = text.percy-(extents.height/2 + extents.y_bearing)*text.arc;
   cairo_move_to(self->context, x+text.spacePercentage, y+text.spaceLegend);
	cairo_text_path (self->context,text.percentage);
	
	cairo_fill_preserve(self->context);
	cairo_stroke(self->context);
	cairo_restore(self->context);
}
void DrawerDrawTextTitle(Drawer * self, Title title,  Rectangle rect) {
	float x, y;	
	cairo_save(self->context);	
	cairo_text_extents_t extents;
	cairo_select_font_face (self->context, "Sans", CAIRO_FONT_SLANT_NORMAL,
                               CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size (self->context, title.fontSize);
	cairo_set_source_rgba(self->context, 
													title.bg.r,
													title.bg.g,
													title.bg.b,
													title.bg.a);
   cairo_text_extents (self->context,title.title, &extents);	
	x = rect.width/2-(extents.width/2 + extents.x_bearing);
	y = rect.height/10-(extents.height/2 + extents.y_bearing);
   cairo_line_to(self->context, x, y);
	cairo_text_path (self->context,title.title);
	cairo_fill_preserve(self->context);
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
