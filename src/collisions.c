#ifndef COLLISIONS_
#define COLLISIONS_
#include "../include/blasteroids.h"
#endif

extern Global * global;

mask_t * Mask_New(ALLEGRO_BITMAP *bmp)
{
    mask_t * temp;
    int h = al_get_bitmap_height(bmp);
    int w = al_get_bitmap_width(bmp);

    ALLEGRO_COLOR transColor = al_map_rgb(255,0,255);
    ALLEGRO_COLOR pixel;
    temp = Mask_Create(w,h);

    if(!temp)
        error("Failed to create temprary mask in Mask_New");
    
    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++){
            pixel = al_get_pixel(bmp,j,i);
            if(!Transparent(pixel))
                Mask_SetBit(temp, j, i);
        }
    return temp;
}

mask_t * Mask_Create(int w, int h)
{
    mask_t *temp = malloc(sizeof(mask_t));

    temp->w = w;
    temp->h = h;
    temp->bits = calloc(sizeof(int)*(w*h),1);


    if(!temp)
        error("Failed to create temprary mask in Mask_Create");
    
    return temp;
}

void Mask_Fill(mask_t *m)
{
    for (int i = 0; i < m->w * m->h; i++)
    {
        m->bits[i] = 1;
    }
    
}

void Mask_SetBit(mask_t *m, int x, int y)
{
    m->bits[x * m->w + y] = 1;
}

void Mask_UnsetBit(mask_t *m, int x, int y)
{
    m->bits[x * m->w +y] = 0;
}

void Mask_Delete(mask_t *m)
{
    if (m->bits != NULL)
        free(m->bits);
    
    if (m != NULL)
        free(m);

}

int Mask_Collide(const mask_t *a, const mask_t *b, int xoffset, int yoffset)
{
    int xover = (a->w + b->w) / 2 - abs(xoffset);
    int yover = (a->h + b->h) / 2 - abs(yoffset);

    if (xover <= 0 || yover <= 0)
        return 0;

    int x1 = (a->w - xover) * ((xoffset < 0) ? 1 : 0);
    int y1 = (a->h - yover) * ((yoffset < 0) ? 1 : 0);
    int x2 = (b->w - xover) * ((xoffset < 0) ? 0 : 1);
    int y2 = (b->h - yover) * ((yoffset < 0) ? 0 : 1);

    for (int i = 0; i < xover; i++)
    {
        for (int j = 0; j < yover; j++)
        {
            if (a->bits[(x1 +i) * a->w + (y1 + j)] == 1 &&
                b->bits[(x2 +i) * b->w + (y2 + j)] == 1)
                printf("Collision\n");
                return 1;
            
        }
        
    }
    return 0;
}

void Mask_Draw(mask_t *m, int x, int y)
{
    m->bmp = al_create_bitmap(m->w * m->BitmapScale , m->h * m->BitmapScale);
    al_set_target_bitmap(m->bmp);
    x = x - m->w / 2;
    y = y - m->h / 2;

    for (int i = 0; i < m->w; i++)
    {
        for (int j = 0; j < m->h; j++)
        {
            if(m->bits[i * m->h + j] == 1)
                al_put_pixel(x+i, y+j, al_map_rgba_f(.75, 0, .75, .75));
        }
    }
	al_set_target_bitmap(al_get_backbuffer(global->disp));
}

int Color_Equiv(ALLEGRO_COLOR col1, ALLEGRO_COLOR col2)
{
    return col1.r == col2.r && col1.g == col2.g && col1.b == col2.b && col1.a == col2.a;
}

int Transparent(ALLEGRO_COLOR col1)
{
    return col1.a == 0;
}