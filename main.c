#include <stdio.h>
#include <string.h>
#include <math.h>
#include "drawing.h"
#include "storage.h"

void PercToText(float x, char str[20]) {
	   sprintf(str, "%.0f", x);
}

void barra(Drawer * drawer, Chart * chart, Rectangle base) {
	 Color rcolor;
	
	 
	 int i;
	 char str[20] = "";
  for(i = 0; chart->content[i] != 0; ++i) {
		float perc = chart->content[i]->percentage;
		PercToText(perc*100,str);
	 
		RandColor(&rcolor);
	   Rectangle rect = {base.width/9 + base.width/6*i, //x
            	      	2*base.height/3, //y
            	      	120,//width
                        -perc*rect.y/2, //Percentage
                  	 0.0, // borderWidth
                     {rcolor.r/10000000, rcolor.g/10000000, rcolor.b/10000000, 1.0}, // Color Bg
                     {1.0,1.0,1.0, 1.0} // Color border
};		
		
		
		TextPlus(str, "%");
	 	Text text = {
		  	 
	 		 20,
			 base.width/9 + base.width/6*i + 60,
			 2*base.height/3,
		  	 chart->content[i]->label ,
			 str,
		  	 1,
		    25,
			 100,
			 -90,
			 190 + 200 - perc*200,
			 1,
			 0,
			 rect.bg,
			 {1.0,1.0,1.0,1.0},
			 rect.bg
};
	
		
		  DrawerDrawRectangle(drawer, rect);
		  DrawerDrawText(drawer, text, base);
		  
	}
	Axis axisx = {
	base.width/11,
	base.height/3 -50,
	base.width/11,
	2*base.height/3 + 20,	
	2,
	{0.0,0.0,0.0,1.0}
};
	Axis axisy = {
	base.width/11- 20,
	base.height/3 +208,
	3*base.width/2 - 500,
	base.height/3 +208,
	2,
	{0.0,0.0,0.0,1.0}
};
  	DrawerDrawAxis(drawer, axisx, base);
	DrawerDrawAxis(drawer, axisy, base);
}		
void pizza(Drawer * drawer, Chart * chart, Rectangle base) {
	Color rcolor;
   float initAngle = 0.0;
	int i;
	char str[20] = "";

  for(i = 0; chart->content[i] != 0; ++i) {

		float perc = chart->content[i]->percentage;
	 
		RandColor(&rcolor);
		PercToText(perc*100,str);
	   Arc arc = {base.width/4, //x
                  base.height/2, //y
                  initAngle, //initAngle
                  perc*2*M_PI+initAngle, //endAngle
                  150,   //radius
                  0.5, // borderWidth
                 {rcolor.r/10000000, rcolor.g/10000000, rcolor.b/10000000, 1.0}, // Color Bg
                 {1.0,1.0,1.0, 1.0} // Color border
        };
		
		
		TextPlus(str, "%");

	 	Text text = {
		  	 
	 		 20,
			 2*base.width/3,
			 base.height/3,
		  	 chart->content[i]->label ,
			 str,
		  	 1,
		    35*i,
			 100,
			 2*base.width/3,
			 base.height/3,
	   	 0,
	       1,
		  	 {1.0,1.0,1.0,1.0},
		  	 {rcolor.r/10000000, rcolor.g/10000000, rcolor.b/10000000, 1.0},
		    {1.0,1.0,1.0,1.0}
};
	Rectangle rectPerc = {2*base.width/3 + 95, //x
            	      		base.height/3 - (3)*text.fontSize/(4) + text.spaceLegend, //y
            	      		(5)*text.fontSize/(2),//width
                        	(3)*text.fontSize/2, //Percentage
                  	 		1.0, // borderWidth
                     	  {rcolor.r/10000000, rcolor.g/10000000, rcolor.b/10000000, 1.0}, // Color Bg
                     	  {1.0,1.0,1.0, 1.0}// Color border
};		
	DrawerDrawRectangle(drawer, rectPerc);

		  if(perc == 1.0) {
	      arc.border.a = 0.0;
		  }
        DrawerDrawArc(drawer, arc);
		  DrawerDrawText(drawer, text, base);
        initAngle += chart->content[i]->percentage*2*M_PI;
		
	}
}
		  
		 


int main() {
	
	Chart * chart = ChartCreate("test.json");
	Drawer * cairo = DrawerInit(800, 600, chart->fileType, chart->filePath);
	
	Title title = {30.0,
						chart->chartName,
						{0.0,0.0,0.0,1.0}
};
	Rectangle base = {0, //x
					  0, //y
					  800, //width
					  600, //height
					  0.0, // borderWidth
					  {1.0, 1.0, 1.0, 1.0},// Color Bg
					  {0.0, 0.0, 0.0, 0.0}// Color border (borderless)
	};
	DrawerDrawRectangle(cairo, base);
	Rectangle baseBg = {10, //x
					  10, //y
					  780, //width
					  580, //height
					  1.0, // borderWidth
					  {0.9,0.9, 0.9, 1.0},// Color Bg
					  {0.3, 0.3, 0.3, 1.0}// Color border (borderless)
	};
	DrawerDrawRectangle(cairo, baseBg);
	DrawerDrawTextTitle(cairo, title, base);
	if(strcmp(chart->chartType,"pizza") == 0) { 
		pizza(cairo, chart, base);
	}else if(strcmp(chart->chartType,"bars") == 0){
		barra(cairo,chart, base);
	}
	DrawerSave(cairo, chart->fileType, chart->filePath);
	DrawerDestroy(cairo);
	return 0;
}
