#include "main.h"
#include <windows.h>

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************

    //PutPixel(256, 256, 10, 245, 255);
    tipoCor cor1 = {255, 0, 0};
    tipoCor cor2 = {0, 0, 255};
    tipoCor cor3 = {12, 245, 255};
    tipoCor cor4 = {234, 103, 5};

    tipoPixel p1 = {cor1, 250, 30};
    tipoPixel p2 = {cor3, 100, 350};
    tipoPixel p3 = {cor4, 323, 200};

    PaintTriangle(&p1, &p2, &p3);

    //DrawTriangle(&p1, &p2, &p3);

    //DrawLine(150, 30, 100, 300, &cor1, &cor2);
    /*DrawLine(512, 0, 256, 256, &cor1 , &cor2);
    DrawLine(256, 256 , 0, 0, &cor3, &cor4);
    DrawLine(256, 0, 256, 512, &cor1, &cor3);
    DrawLine(0, 256, 512, 256, &cor1, &cor3);
    DrawLine(0, 512, 256, 256, &cor3, &cor4);
    DrawLine(0, 0, 512, 512, &cor1, &cor2);
    DrawLine(100, 512, 412, 0, &cor2, &cor4);
    DrawLine(190, 0, 322, 512, &cor3, &cor4);
    DrawLine(0, 312, 512, 200, &cor1, &cor4);
    DrawLine(0, 128, 512, 384, &cor2, &cor4);*/

    //DrawLine(0, 212, 512, 212, &cor1, &cor2);



    //DrawCircle(300,200,100);


}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

