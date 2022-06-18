#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

typedef struct mask
{
    int w, h;
    int * bits;
    float BitmapScale;
    ALLEGRO_TRANSFORM *tranform;
    ALLEGRO_BITMAP *bmp;
} mask_t;


mask_t * Mask_New(ALLEGRO_BITMAP * bmp); // Creates a mask over the bitmap. Stores it in an array
mask_t * Mask_Create(int w, int h); // Allocates memory
void Mask_Fill(mask_t *m); // Completely masks the bitmap
void Mask_Delete(mask_t *m); // Deallocates everything
void Mask_SetBit(mask_t *m, int x, int y); // Masks an individual Bit
void Mask_UnsetBit(mask_t *m, int x, int y); // Unmasks an Individual Bit
int Mask_Collide(const mask_t *m, const mask_t *b, int xoffset, int yoffset); 
void Mask_Draw(mask_t *m, int x, int y); // Draws the Mask as a bitmap from the array
int Color_Equiv(ALLEGRO_COLOR col1, ALLEGRO_COLOR col2); // Checks if 2 colors are the same
int Transparent(ALLEGRO_COLOR col1); // Checks if a bit is transparent