#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include <math.h>

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************
typedef struct {
    int r;
    int g;
    int b;
} tipoCor;

typedef struct {
    tipoCor c;
    int x;
    int y;
} tipoPixel;

void PutPixel(int x, int y, int r, int g, int b)
{
        FBptr[(x*4) + (y*IMAGE_WIDTH*4) + 0] = r;
        FBptr[(x*4) + (y*IMAGE_WIDTH*4) + 1] = g;
        FBptr[(x*4) + (y*IMAGE_WIDTH*4) + 2] = b;
        FBptr[(x*4) + (y*IMAGE_WIDTH*4) + 3] = 255;

}

void DrawLine(int x0, int y0, int x1, int y1, tipoCor c1[], tipoCor c2[])
{
    int dx = x1 - x0; //Delta X
    int dy = y1 - y0; //Delta y
    int inclinacao = 0;

    if(dx < 0) // caso ponto final < ponto inicial
    {
        DrawLine(x1, y1, x0, y0, c2, c1);
        return;
    }


    int variacaoR = (c2->r) - (c1->r); //se a variacao for 0, vai incrementar 0
    int variacaoG = (c2->g) - (c1->g);
    int variacaoB = (c2->b) - (c1->b);

    unsigned int vdx = dx; //variacao de x e y a cada incremento na forma de inteiro sem sinal
    unsigned int vdy = dy;

    float tamLinha = sqrt((vdx*vdx) + (vdy*vdy)); //tamanho da linha a ser desenhada

    float addR = (float) variacaoR / tamLinha;
    float addG = (float) variacaoG / tamLinha;
    float addB = (float) variacaoB / tamLinha;

    float r0 = c1->r; //valores iniciais de RGB
    float g0 = c1->g;
    float b0 = c1->b;

    if(dy < 0)
    {
        inclinacao = -1;
    }
    else
    {
        inclinacao = 1;
    }

    if(dx == 0) //caso retas verticais (onde x não varia)
    {
        if(y0 < y1) //varia o y inicial ate o final
        {
            PutPixel(x0, y0, r0, g0, b0);
            while(y0++ < y1)
            {
                PutPixel(x0, y0, round(r0 += addR), round(g0 += addG), round(b0 += addB));
            }
        }
        else //varia o y final ate o inicial
        {
            PutPixel(x0, y0, r0, g0, b0);
            while(y1++ < y0)
            {
                PutPixel(x0, y1, round(r0 += addR), round(g0 += addG), round(b0 += addB));
            }
        }

        return;
    }

    int incr_e, incr_ne, d;
    int x = x0;
    int y = y0;

    PutPixel(x, y, r0, g0, b0);

    if(dx >= inclinacao * dy) // caso m <= 1
    {
        if(dy < 0) // caso y1 < y0
        {
            d = 2 * dy + dx;
            incr_e = 2 * dy;
            incr_ne = 2 * (dy + dx);
            while(x < x1)
            {
                if(d < 0)
                {
                    d += incr_ne;
                    x++;
                    y--;
                }
                else{
                    d += incr_e;
                    x++;
                }
                PutPixel(x, y, round(r0 += addR), round(g0 += addG), round(b0 += addB));
            }
        }
        else // caso y0 < y1
        {
            d = 2 * dy - dx;
            incr_e = 2 * dy;
            incr_ne = 2 * (dy - dx);

            if(dy == 0)
            {
                while(x < (x1 - 1))
                {
                    if(d < 0)
                    {
                        d += incr_e;
                        x++;
                    }
                    else
                    {
                        d += incr_ne;
                        x++;
                        y++;
                    }
                    PutPixel(x, y, round(r0 += addR), round(g0 += addG), round(b0 += addB));
                }
            }
            else
            {
                while(x < x1)
                {
                    if(d < 0)
                    {
                        d += incr_e;
                        x++;
                    }
                    else
                    {
                        d += incr_ne;
                        x++;
                        y++;
                    }
                    PutPixel(x, y, round(r0 += addR), round(g0 += addG), round(b0 += addB));
                }
            }
        }
    }
    else // caso |m|>1
    {
        if(dy < 0) // caso y1 < y0
        {
            d = dy + 2 * dx;
            incr_e = 2 * dx;
            incr_ne = 2 * (dy + dx);
            while(y > y1)
            {
                if(d < 0)
                {
                    d += incr_e;
                    y--;
                }
                else
                {
                    d += incr_ne;
                    x++;
                    y--;
                }
                PutPixel(x, y, round(r0 += addR), round(g0 += addG), round(b0 += addB));
            }
        }
        else // caso y0 < y1
        {
            d = dy - 2 * dx;
            incr_e = -2 * dx;
            incr_ne = 2 * (dy - dx);
            while(y < y1)
            {
                if(d < 0)
                {
                    d += incr_ne;
                    x++;
                    y++;
                }
                else
                {
                    d += incr_e;
                    y++;
                }
                PutPixel(x, y, round(r0 += addR), round(g0 += addG), round(b0 += addB));
            }
        }
    }

}

void DrawTriangle(tipoPixel p1[], tipoPixel p2[], tipoPixel p3[])
{
    DrawLine(p1->x, p1->y, p2->x, p2->y, &p1->c, &p2->c);
    DrawLine(p2->x, p2->y, p3->x, p3->y, &p2->c, &p3->c);
    DrawLine(p3->x, p3->y, p1->x, p1->y, &p3->c, &p1->c);
}

void PaintTriangle(tipoPixel p1[], tipoPixel p2[], tipoPixel p3[])
{
    tipoCor aux;
    int x1 = p3->x;
    int x0 = p2->x;
    int y0 = p2->y;
    int y1 = p3->y;
    tipoCor* c1 = &p2->c;
    tipoCor* c2 = &p3->c;


    DrawLine(p1->x, p1->y, p2->x, p2->y, &p1->c, &p2->c);

        int dx = x1 - x0; //Delta X
        int dy = y1 - y0; //Delta y
        int inclinacao = 0;

        if(dx < 0) // caso ponto final < ponto inicial
        {
            DrawLine(x1, y1, x0, y0, c2, c1);
            return;
        }


        int variacaoR = (c2->r) - (c1->r); //se a variacao for 0, vai incrementar 0
        int variacaoG = (c2->g) - (c1->g);
        int variacaoB = (c2->b) - (c1->b);

        unsigned int vdx = dx; //variacao de x e y a cada incremento na forma de inteiro sem sinal
        unsigned int vdy = dy;

        float tamLinha = sqrt((vdx*vdx) + (vdy*vdy)); //tamanho da linha a ser desenhada

        float addR = (float) variacaoR / tamLinha;
        float addG = (float) variacaoG / tamLinha;
        float addB = (float) variacaoB / tamLinha;

        float r0 = c1->r; //valores iniciais de RGB
        float g0 = c1->g;
        float b0 = c1->b;

        if(dy < 0)
        {
            inclinacao = -1;
        }
        else
        {
            inclinacao = 1;
        }

        if(dx == 0) //caso retas verticais (onde x não varia)
        {
            if(y0 < y1) //varia o y inicial ate o final
            {
                PutPixel(x0, y0, r0, g0, b0);
                while(y0++ < y1)
                {
                    PutPixel(x0, y0, round(r0 += addR), round(g0 += addG), round(b0 += addB));
                    aux = {round(r0), round(g0), round(b0)};
                    DrawLine(p1->x, p1->y, x0, y0, &p1->c, &aux);
                }
            }
            else //varia o y final ate o inicial
            {
                PutPixel(x0, y0, r0, g0, b0);
                while(y1++ < y0)
                {
                    PutPixel(x0, y1, round(r0 += addR), round(g0 += addG), round(b0 += addB));
                    aux = {round(r0), round(g0), round(b0)};
                    DrawLine(p1->x, p1->y, x0, y0, &p1->c, &aux);
                }
            }

            return;
        }

        int incr_e, incr_ne, d;
        int x = x0;
        int y = y0;

        PutPixel(x, y, r0, g0, b0);

        if(dx >= inclinacao * dy) // caso m <= 1
        {
            if(dy < 0) // caso y1 < y0
            {
                d = 2 * dy + dx;
                incr_e = 2 * dy;
                incr_ne = 2 * (dy + dx);
                while(x < x1)
                {
                    if(d < 0)
                    {
                        d += incr_ne;
                        x++;
                        y--;
                    }
                    else{
                        d += incr_e;
                        x++;
                    }
                    PutPixel(x, y, round(r0 += addR), round(g0 += addG), round(b0 += addB));
                    aux = {round(r0), round(g0), round(b0)};
                    DrawLine(p1->x, p1->y, x, y, &p1->c, &aux);
                }
            }
            else // caso y0 < y1
            {
                d = 2 * dy - dx;
                incr_e = 2 * dy;
                incr_ne = 2 * (dy - dx);

                if(dy == 0)
                {
                    while(x < (x1 - 1))
                    {
                        if(d < 0)
                        {
                            d += incr_e;
                            x++;
                        }
                        else
                        {
                            d += incr_ne;
                            x++;
                            y++;
                        }
                        PutPixel(x, y, round(r0 += addR), round(g0 += addG), round(b0 += addB));
                        aux = {round(r0), round(g0), round(b0)};
                        DrawLine(p1->x, p1->y, x, y, &p1->c, &aux);
                    }
                }
                else
                {
                    while(x < x1)
                    {
                        if(d < 0)
                        {
                            d += incr_e;
                            x++;
                        }
                        else
                        {
                            d += incr_ne;
                            x++;
                            y++;
                        }
                        PutPixel(x, y, round(r0 += addR), round(g0 += addG), round(b0 += addB));
                        aux = {round(r0), round(g0), round(b0)};
                        DrawLine(p1->x, p1->y, x, y, &p1->c, &aux);
                    }
                }
            }
        }
        else // caso |m|>1
        {
            if(dy < 0) // caso y1 < y0
            {
                d = dy + 2 * dx;
                incr_e = 2 * dx;
                incr_ne = 2 * (dy + dx);
                while(y > y1)
                {
                    if(d < 0)
                    {
                        d += incr_e;
                        y--;
                    }
                    else
                    {
                        d += incr_ne;
                        x++;
                        y--;
                    }
                    PutPixel(x, y, round(r0 += addR), round(g0 += addG), round(b0 += addB));
                    aux = {round(r0), round(g0), round(b0)};
                    DrawLine(p1->x, p1->y, x, y, &p1->c, &aux);
                }
            }
            else // caso y0 < y1
            {
                d = dy - 2 * dx;
                incr_e = -2 * dx;
                incr_ne = 2 * (dy - dx);
                while(y < y1)
                {
                    if(d < 0)
                    {
                        d += incr_ne;
                        x++;
                        y++;
                    }
                    else
                    {
                        d += incr_e;
                        y++;
                    }
                    PutPixel(x, y, round(r0 += addR), round(g0 += addG), round(b0 += addB));
                    aux = {round(r0), round(g0), round(b0)};
                    DrawLine(p1->x, p1->y, x, y, &p1->c, &aux);
                }
            }
        }


}
/*void plotpoints(int x, int y, int r)
{
    int xcenter, ycenter;

    if(x > 256)
        xcenter = x - r;
    else
        xcenter = x + r;
    if(y > 256)
        ycenter = y - r;
    else
        ycenter = y + r;

        PutPixel(xcenter+x, ycenter+y, 0, 0, 255);
        PutPixel(xcenter-x, ycenter+y, 0, 0, 255);
        PutPixel(xcenter+x, ycenter-y, 0, 0, 255);
        PutPixel(xcenter-x, ycenter-y, 0, 0, 255);
        PutPixel(xcenter+y, ycenter+x, 0, 0, 255);
        PutPixel(xcenter-y, ycenter+x, 0, 0, 255);
        PutPixel(xcenter+y, ycenter-x, 0, 0, 255);
        PutPixel(xcenter-x, ycenter-x, 0, 0, 255);
}

void DrawCircle(int x0, int y0, int r)
{
    int x, y;
    if(x0 > 256)
        x = x0 - r;
    else
        x = x0 + r;
    if(y0 > 256)
        y = y0 - r;
    else
        y0 = y0 + r;
    plotpoints(x,y,r);
    int p = 1 - r;
    while(x < y)
    {
        x++;
        if(p < 0)
            p += 2*x + 1;
        else
        {
            y--;
            p += 2*(x - y) + 1;
        }
        plotpoints(x,y,r);
    }
}*/

#endif // _MYGL_H_

