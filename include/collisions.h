#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

typedef struct mask
{
    int w, h;
    int * bits;
} mask_t;


mask_t * Mask_New(ALLEGRO_BITMAP * bmp);

mask_t * Mask_Create(int w, int h);

mask_t * Mask_Clear(mask_t *m);

mask_t * Mask_Fill(mask_t *m);

mask_t * Mask_Delete(mask_t *m);

void Mask_SetBit(mask_t *m, int x, int y);

void Mask_UnsetBit(mask_t *m, int x, int y);

void Mask_UnsetBit(mask_t *m, int x, int y);

int Mask_Collide(const mask_t *m, const mask_t *b, int xoffset, int yoffset);

void Mask_Draw(mask_t *m, int x, int y);

int Color_Equiv(ALLEGRO_COLOR col1, ALLEGRO_COLOR col2);

int Transparent(ALLEGRO_COLOR col1);