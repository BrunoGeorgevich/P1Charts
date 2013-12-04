#include <stdio.h>
#include <string.h>
#include <math.h>
#include "drawing.h"
#include "storage.h"
void barra(Drawer * drawer, Chart * chart, Rectangle base) {
	 int i;
	 float randColorR,randColorG,randColorB;
	 for(i = 0; chart->content[i] != 0; ++i) {
		 randColorR = (rand()%9999999);
		 randColorG = (rand()%9999999);
		 randColorB = (rand()%9999999);
		 double perc = chart->content[i]->percentage;

	Rectangle rect = {base.width/10 + base.width/25*i, //x
            	      base.height/2, //y
           		      base.width/20,//width
                  	-perc*rect.y, //Percentage
                  	5.0, // borderWidth
                    {randColorR/10000000, randColorG/10000000, randColorB/10000000, 			             														 1.0}, // Color Bg
                    {1.0,1.0,1.0, 1.0} // Color border
};	
	Text text = {
		  	 
	 		 3*rect.borderWidth,
		  	 rect.x,
		  	 rect.y,
		  	 chart->content[i]->label ,
		  	 1,
		    15*i,
		  	 rect.border,
		  	 rect.bg
};
		  DrawerDrawRectangle(drawer, rect);
		  DrawerDrawTextRect(drawer, text, rect, base);
	}

}		
void pizza(Drawer * drawer, Chart * chart, Rectangle base) {
    float initAngle = 0.0;
	 int i;
	 float randColorR,randColorG,randColorB;
    for(i = 0; chart->content[i] != 0; ++i) {

	    double perc = chart->content[i]->percentage;
		 randColorR = (rand()%9999999);
		 randColorG = (rand()%9999999);
		 randColorB = (rand()%9999999);
       Arc arc = {base.width/2, //x
                  base.height/2, //y
                  initAngle, //initAngle
                  perc*2*M_PI+initAngle, //endAngle
                  150,   //radius
                  5.0, // borderWidth
                  {randColorR/10000000, randColorG/10000000, randColorB/10000000, 			             														 1.0}, // Color Bg
                  {1.0,1.0,1.0, 1.0} // Color border
        };
	     
			
		  Text text = {
		  	 
	 		 3*arc.borderWidth,
		  	 arc.x,
		  	 arc.y,
		  	 chart->content[i]->label ,
		  	 1,
		    15*i,
		  	 arc.border,
		  	 arc.bg
};		 
		if(perc == 1.0) {
	      arc.border.a = 0.0;
		  }
        DrawerDrawArc(drawer, arc);
		  DrawerDrawTextArc(drawer, text, arc, base);
        initAngle += chart->content[i]->percentage*2*M_PI;
		
	}
}

int main() {
	Chart * chart = ChartCreate("test.json");
	Drawer * cairo = DrawerInit(800, 600, chart->fileType, chart->filePath);
	Rectangle base = {0, //x
					  0, //y
					  800, //width
					  600, //height
					  0.0, // borderWidth
					  {1.0, 1.0, 1.0, 1.0},// Color Bg
					  {0.0, 0.0, 0.0, 0.0}// Color border (borderless)
	};
	DrawerDrawRectangle(cairo, base);
	
	if(strcmp(chart->chartType,"pizza") == 0) { 
		pizza(cairo, chart, base);
	}else{
		barra(cairo,chart, base);
	}
	DrawerSave(cairo, chart->fileType, chart->filePath);
	DrawerDestroy(cairo);
	return 0;
}
