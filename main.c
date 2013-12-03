#include <stdio.h>
#include <string.h>

#include "drawing.h"
#include "storage.h"

void pizza(Drawer * drawer, Chart * chart) {
    float initAngle = 0.0;
    for(int i = 0; chart->content[i] != 0; ++i) {
        Arc arc = {400, //x
                  300, //y
                  initAngle, //initAngle
                  initAngle + chart->content[i]->percentage*2*M_PI, //endAngle
                  50,   //radius
                  1.0, // borderWidth
                  {i*0.1, 1.0, i*0.1, 1.0}, // Color Bg
                  {i*0.3, 0, i*0.3, 1.0} // Color border
        };
        DrawerDrawArc(drawer, arc);
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

	Rectangle rect = {400-50, //x
					  300-50, //y
					  100, //width
					  100, //height
					  10.0, // borderWidth
					  {1.0, 0.0, 1.0, 1.0}, // Color Bg
					  {0.0, 1.0, 0.0, 1.0} // Color border
	};
	DrawerDrawRectangle(cairo, rect);
	pizza(cairo, chart);
	DrawerSave(cairo, chart->fileType, chart->filePath);
	DrawerDestroy(cairo);
	return 0;
}
