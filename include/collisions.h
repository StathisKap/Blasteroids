#ifndef INCLUDE_COLLISIONS_H_
    #define INCLUDE_COLLISIONS_H_

    #include <allegro5/allegro5.h>
    #include <allegro5/allegro_font.h>
    #include <allegro5/allegro_primitives.h>
    #include <allegro5/allegro_image.h>
    #include <allegro5/allegro_ttf.h>

    bool Box_Collision_Ship(); // Checks if two boxes are colliding
    bool Box_Collision_Bullets(); // Checks if two boxes are colliding
#endif // INCLUDE_COLLISIONS_H_
