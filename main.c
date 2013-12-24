#include <stdio.h>
#include <string.h>
#include <math.h>
#include "drawing.h"
#include "storage.h"

void percToText(float x, char str[20]) {
	   sprintf(str, "%.0f", x);
}

void barra(Drawer * drawer, Chart * chart, Rectangle base) {
	 Color rcolor;
	
	 
	 int i;
	 char str[20] = "";
  for(i = 0; chart->content[i] != 0; ++i) {
		float perc = chart->content[i]->percentage;
		percToText(perc*100,str);
	 
		randColor(&rcolor);
	   Rectangle rect = {base.width/10 + (SpaceValue(chart->DatumSize)*base.width/80)*(i), //x
            	      	14*base.height/15, //y
            	      	(8*base.width/15)/chart->DatumSize,//width
                        -perc*((11*base.height/15)/chart->Sum_Percentages), //height
                  		 0.0, // borderWidth
                    		{rcolor.r/10000000, rcolor.g/10000000, rcolor.b/10000000, 1.0}, // Color Bg
                     	{1.0,1.0,1.0, 1.0} // Color border
};		
		
		
		textPlus(str, "%");
	 	Text text = {
		  	 
	 		 15,//Font Size
			 rect.x+rect.width/2,//X
			 20*base.height/21,//Y
		  	 chart->content[i]->label ,//Label
			 str,//Percentage(String Form)
		  	 1,//BorderWidth
		    i,//Space Legend
			 0,//Space Percentage
			 1*base.width/60,//Coordenada X da porcentagem
			 19*base.height/20 + rect.height,//Coordenada Y da porcentagem
			 1,//Se 1 = Retangulo
			 0,//Se 1 = Arco
			 rect.bg,//Color Bg
			 {1.0,1.0,1.0,1.0},//Color Border
			 rect.bg//Color of Percentage
};
	
		
		  DrawerDrawRectangle(drawer, rect);
		  DrawerDrawText(drawer, text, base);
		  
	}
	Axis axisy = {
	1*base.width/15,
	3*base.height/15,
	1*base.width/15,
	20*base.height/21,
	2,
	{0.0,0.0,0.0,1.0}
};
	Axis axisx = {
	1*base.width/21,
	14*base.height/15,
	12*base.width/15,
	14*base.height/15,
	2,
	{0.0,0.0,0.0,1.0}
};
	Arrow arrowR = {
	1*base.width/15 - 5,
	3*base.width/18,
	1*base.width/15 + 5,
	3*base.width/18,
	axisy.x0,
	axisy.y0,
	2,
	{0.0,0.0,0.0,1.0}
};
	Arrow arrowL = {
	18*base.width/23,
	14*base.height/15 - 5,
	18*base.width/23 ,
	14*base.height/15 + 5,
	axisx.x,
	axisx.y,
	2,
	{0.0,0.0,0.0,1.0}
};
	
	DrawerDrawArrow(drawer, axisx, arrowR);
	DrawerDrawArrow(drawer, axisx, arrowL);	
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
	 
		randColor(&rcolor);
		percToText(perc*100,str);
	   Arc arc = {base.width/3, //x
                  base.height/2, //y
                  initAngle, //initAngle
                  perc*2*M_PI+initAngle, //endAngle
                  200,   //radius
                  0.5, // borderWidth
                 {rcolor.r/10000000, rcolor.g/10000000, rcolor.b/10000000, 1.0}, // Color Bg
                 {1.0,1.0,1.0, 1.0} // Color border
        };
		
		
		textPlus(str, "%");

	 	Text text = {
		  	 
	 		 20,//Font Size
			 3*base.width/4,//X
			 base.height/2,//Y
		  	 chart->content[i]->label ,//Label
			 str,//Percentage(String Form)
		  	 1,//BorderWidth
		    35*i,//Space Legend
			 5,//Space Percentage
			 2*base.width/3,//Coordenada X da porcentagem
			 base.height/2,//Coordenada Y da porcentagem
	   	 0,//Se 1 = Retangulo
	       1,//Se 1 = Arco
		  	 {1.0,1.0,1.0,1.0},//Color Bg
		  	 {rcolor.r/10000000, rcolor.g/10000000, rcolor.b/10000000, 1.0},//Color Border
		    {1.0,1.0,1.0,1.0}//Color of Percentage
};
	Rectangle rectPerc = {2*base.width/3, //x
            	      	 base.height/2 - (3)*text.fontSize/(4) + text.spaceLegend, //y
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
		  
		 


int main(int argc, char *argv[]) {
      if(argc == 2) {	
	char kind[8];
	char  s2[] = {".json"};
	type(argv[1],kind);
	int result = compare(kind, s2);
	 if(result != 0) {
	   printf("Argumento passado não é do tipo .json!\n");	
	   return 0;
	  }
}
    else if(argc > 2) {
	printf("Mais argumentos do que o necessário!\nPor favor, insira um argumento do tipo .json!\n");
	return 0;
}	
    else if(argc < 2) {
	printf("Menos argumentos do que o necessário!\nPor favor, insira um argumento do tipo .json!\n");
	return 0;
}
	Chart * chart = ChartCreate(argv[1]);
	Drawer * cairo = DrawerInit(800, 600, chart->fileType, chart->filePath);
	
	int num_elementos = chart->DatumSize;
	
	sort(chart->content, chart);
	int cont3;
	for(cont3 = 0; cont3 < num_elementos;cont3++) {
		printf("%f\n", chart->content[cont3]->percentage);
	}
		printf("%f\n", chart->Sum_Percentages);

	
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
