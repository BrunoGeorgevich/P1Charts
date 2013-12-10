#include <cairo/cairo.h>
#include <math.h>
#include "drawing.h"

int main() {
	/***********************************
    * 1 - Criar papel e caneta cairo *
 	*********************************
 	Drawer * cairo = DrawerInit(800, 600, 0, "result.pdf");

	/****************
 	* 2 - Desenhar *
 	****************
 	Rectangle base = {0, //x
					  0, //y
					  800, //width
					  600, //height
					  0.0, // borderWidth
					  {1.0, 1.0, 1.0, 1.0},// Color Bg
					  {0.0, 0.0, 0.0, 0.0}// Color border (borderless)
	};
	DrawerDrawRectangle(cairo, base);

 	/*cairo_rectangle (cairo->context, 0, 0, 800, 600);
	cairo_set_source_rgb(cairo->context, 1.0, 1.0, 1.0);
	cairo_fill(cairo->context);*
	Arc arc = {400, //x
              300, //y
              0, //initAngle
              2*M_PI, //endAngle
              200,   //radius
              5.0, // borderWidth
              {0.5, 0.5, 1.0, 1.0}, // Color Bg
              {0.5, 1.0, 0.0, 1.0} // Color border
	};

	/*Rectangle rect = {400-arc.radius, //x - altura/2
					  300-arc.radius, //y - largura/2
					  2*arc.radius, //width
					  2*arc.radius, //height
					  10.0, // borderWidth
					  {1.0, 0.0, 0.5, 1.0}, // Color Bg
					  {0.0, 1.0, 0.0, 1.0} // Color border
	};
	DrawerDrawRectangle(cairo, rect);*/

	/*cairo_rectangle (cairo->context, 400 - 50, 300 - 50, 100, 100);
	cairo_set_source_rgb(cairo->context, 1.0, 0.0, 0.0);
	cairo_fill_preserve(cairo->context);
 	cairo_set_source_rgba(cairo->context, 1.0, 1.0, 0.0, 1.0);
 	cairo_stroke(cairo->context);*

 	/*cairo_set_source_rgb(cairo->context, 0.0, 0.0, 0.0);
	cairo_arc (cairo->context, 400, 300, 2, 0, 2* M_PI);
	cairo_fill(cairo->context);*
	
   DrawerDrawArc(cairo, arc);

	Text text = {
	 5*arc.borderWidth,
	"Hello",
	 "oi",
	 1,
	15,
	{0.0,0.0,0.0,1.0},
	{1.0,0.0,0.0,1.0}
};

	 DrawerDrawText(cairo, text, base);

	/*************************
 	* 3 - Salvar em arquivo *
 	*************************
	cairo_surface_write_to_png(cairo->surface, "test.png");

	/******************************
 	* 4 - Deletar caneta e papel *
 	******************************
    DrawerDestroy(cairo);
	cairo = 0;
	return 0;*/
}
