#include <stdio.h>
#include <string.h>
#include <math.h>
#include "drawing.h"
#include "storage.h"

void percToText(float x, char str[20]) {//Função que transforma as porcentagens em Strings
	   sprintf(str, "%.0f", x);
		strcat(str,"%");
}

void barra(Drawer * drawer, Chart * chart, Rectangle base) {//Função que desenha o Gráfico de Barras
	    
		 Color rcolor;//Declarando um parâmetro rcolor do tipo Color
	
	 
		 int i;
		 char str[20] = "";//Declarando uma string vazia

  for(i = 0; chart->content[i] != 0; ++i) {

		 float perc = chart->content[i]->percentage;

		percToText(perc*100.00,str);//Função que transforma as porcentagens em Strings
		randColor(&rcolor);//Função que randomiza os números responsáveis pelas cores

	   Rectangle rect = {

	 		 base.width/9 + (SpaceValue(chart->DatumSize)*base.width/80)*(i), //x
	 		 14*base.height/15, //y
	 		 (8*base.width/15)/chart->DatumSize,//width
	 		-perc*((11*base.height/15)/chart->Sum_Percentages), //height
	 		 0.0, // borderWidth
	 		{rcolor.r, rcolor.g, rcolor.b, 1.0}, // Color Bg
	 		{1.0,1.0,1.0, 1.0} // Color border
};		
		
		
		
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
	 		 
			 1*base.width/15,// Posição x0
	 		 3*base.height/15,// Posição y0
	 		 1*base.width/15,// Posição x
	 		 39*base.height/40,// Posição y
	 		 2,// Largura do Eixo
	 		 {0.0,0.0,0.0,1.0}// Cor do Eixo
};
		Axis axisx = {
	 		 
			 1*base.width/40,// Posição x0
	 		 14*base.height/15,// Posição y0
	 		 12*base.width/15,// Posição x
	 		 14*base.height/15,// Posição y
	 		 2,// Largura do Eixo
	 		 {0.0,0.0,0.0,1.0}// Cor do Eixo
};
		Arrow arrowY = {

	 		 1*base.width/15 - 5,// Posição X da ponta Direita da Seta
	 		 3*base.width/18,// Posição Y da ponta Direita da Seta
	 		 1*base.width/15 + 5,// Posição X da ponta Esquerda da Seta
	 		 3*base.width/18,// Posição Y da ponta Esquerda da Seta
	 		 axisy.x0,// Posição X de intersecção da ponta Direita com a ponta Esquerda
	 		 axisy.y0,// Posição Y de intersecção da ponta Direita com a ponta Esquerda
	 		 2,// Largura da Seta
	 		 axisy.bg//Cor da Seta
};
		Arrow arrowX = {
	 		 
			 18*base.width/23,// Posição X da ponta Direita da Seta
	 		 14*base.height/15 - 5,// Posição Y da ponta Direita da Seta
	 		 18*base.width/23 ,// Posição X da ponta Esquerda da Seta
	 		 14*base.height/15 + 5,// Posição Y da ponta Esquerda da Seta
	 		 axisx.x,// Posição X de intersecção da ponta Direita com a ponta Esquerda
	 		 axisx.y,// Posição Y de intersecção da ponta Direita com a ponta Esquerda
	 		 2,// Largura da Seta
	 		 axisx.bg//Cor da Seta
};
	
	 		 DrawerDrawArrow(drawer, axisy, arrowX);
	 		 DrawerDrawArrow(drawer, axisx, arrowY);
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
	 
		randColor(&rcolor);//Função que randomiza os números responsáveis pelas cores
		percToText(perc*100,str);//Função que transforma a porcentagem em string

	   Arc arc = {
		
	 		 base.width/3, //x
	 		 base.height/2, //y
	 		 initAngle, //initAngle
	 		 perc*2*M_PI+initAngle, //endAngle
	 		 200,   //radius
	 		 0.5, // borderWidth
	 		 {rcolor.r, rcolor.g, rcolor.b, 1.0}, // Color Bg
	 		 {1.0,1.0,1.0, 1.0} // Color border
};
		
		Rectangle rectPerc = {
			
			 2*base.width/3, //x
	 		 4*base.height/10 + 35*i, //y
	 		 60,//width
	 		 30, //height
	 		 1.0, // borderWidth
	 		 {rcolor.r, rcolor.g, rcolor.b, 1.0}, // Color Bg
	 		 {1.0,1.0,1.0, 1.0}// Color border
};		
		

	 	Text text = {
		  	 
	 		 2*rectPerc.height/3,//Font Size
			 3*base.width/4 ,//X
			 4*base.height/10 + rectPerc.height/2,//Y
		  	 chart->content[i]->label ,//Label
			 str,//Percentage(String Form)
		  	 1,//BorderWidth
		    rectPerc.y - 4*base.height/10,//Space Legend
			 0,//Space Percentage
			 2*base.width/3 + rectPerc.width/4,//Coordenada X da porcentagem
			 4*base.height/10 + rectPerc.height/2,//Coordenada Y da porcentagem
	   	 0,//Se 1 = Retangulo
	       1,//Se 1 = Arco
		  	 {1.0,1.0,1.0,1.0},//Color Bg
		  	 {rcolor.r, rcolor.g, rcolor.b, 1.0},//Color Border
		    {1.0,1.0,1.0,1.0}//Color of Percentage
};
	
	DrawerDrawRectangle(drawer, rectPerc);

		  if(perc == 1.0) {//Se o gráfico de pizza tiver somente um parâmetro (100%), excluir a borda
	      arc.border.a = 0.0;
}
        DrawerDrawArc(drawer, arc);
		  DrawerDrawText(drawer, text, base);
        initAngle += chart->content[i]->percentage*2*M_PI;
		
	}
}
		  
		 


int main(int argc, char *argv[]) {
	 		 if(argc == 2) {//Testando se os parâmetros de entradas são do tipo .json
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
	 		  printf("Mais argumentos do que o necessário!\nPor favor, insira somente um argumento do tipo .json!\n");

	 		  return 0;
}	
	 		 else if(argc < 2) {
	 		  printf("Menos argumentos do que o necessário!\nPor favor, insira um argumento do tipo .json!\n");

			  return 0;
}
			  Chart * chart = ChartCreate(argv[1]);
			  Drawer * cairo = DrawerInit(800, 600, chart->fileType, chart->filePath);
	
			  int num_elementos = chart->DatumSize;//Declarando o número de elementos do Datum
	
			  sort(chart->content, chart);//Função que lista os elementos em ordem crescente

		Title title = {
		    
		    30.0,//Fonte do Título
		    chart->chartName,//String que provém o título
		    {0.0,0.0,0.0,1.0}//Cor do Título
};
		Rectangle base = {
		    
		    0, //x
		    0, //y
		    800, //width
		    600, //height
		    0.0, // borderWidth
		   {1.0, 1.0, 1.0, 1.0},// Color Bg
		   {0.0, 0.0, 0.0, 0.0}// Color border (borderless)
};
		
		DrawerDrawRectangle(cairo, base);
		Rectangle baseBg = {
		    
		    10, //x
		    10, //y
		    780, //width
		    580, //height
		    1.0, // borderWidth
		   {0.9,0.9, 0.9, 1.0},// Color Bg
		   {0.3, 0.3, 0.3, 1.0}// Color border (borderless)
};
		DrawerDrawRectangle(cairo, baseBg);
		DrawerDrawTextTitle(cairo, title, base);

		    if(strcmp(chart->chartType,"pizza") == 0) {//Se for Pizza
		     
		     pizza(cairo, chart, base);
	
		   }else if(strcmp(chart->chartType,"bars") == 0){//Se for Barras
		    
			  barra(cairo,chart, base);
}
			  DrawerSave(cairo, chart->fileType, chart->filePath);
			  DrawerDestroy(cairo);

		return 0;
}
