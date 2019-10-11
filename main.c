#include <gb/gb.h>
#include <stdio.h>
#include "SmilesSprites.c"
#include "simple_background.c"
#include "backgroundTiles.c"
#include "window_map.c"
#include "Sprites.c"
#include <gb/font.h>

typedef struct
{
    UINT8 x;
    UINT8 y;
} Position;

#define BULLET_COUNT 10
#define BULLET_DELAY 10

UINT8 collisionCheck(UINT8 x1, UINT8 y1, UINT8 w1, UINT8 h1, UINT8 x2, UINT8 y2, UINT8 w2, UINT8 h2);

void moveEnemy(Position *enemy)
{

    if (enemy->x >= 160)
    {
        enemy->x = 8;
        enemy->y += 10;
        return;
    }
    enemy->x += 10;
}

void main()
{
    Position shipPosition = {8, 152};
    Position enemy = {8, 16};
    UINT8 i;
    UINT8 y = 0;
    UINT8 bulletDelay = 0;

    Position bulletPositions[BULLET_COUNT] = {
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
    };

    set_sprite_data(0, 3, Sprites);
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 1);

    move_sprite(0, shipPosition.x, shipPosition.y);
    move_sprite(1, enemy.x, enemy.y);

    for (i = 0; i < BULLET_COUNT; i++)
    {
        set_sprite_tile(2 + i, 2);
        move_sprite(2 + i, bulletPositions[i].x, bulletPositions[i].y);
    }

    SHOW_SPRITES;

    while (1)
    {
        UBYTE joypad_state = joypad();

        if (joypad_state & J_LEFT)
        {
            shipPosition.x -= 1;
            shipPosition.x = shipPosition.x < 8 ? 8 : shipPosition.x;
        }
        else if (joypad_state & J_RIGHT)
        {
            shipPosition.x += 1;
            shipPosition.x = shipPosition.x > 160 ? 160 : shipPosition.x;
        }

        if (joypad_state & J_A && bulletDelay == 0)
        {
            for (i = 0; i < BULLET_COUNT; i++)
            {
                if (bulletPositions[i].y == 0)
                {
                    bulletPositions[i].y = 152;
                    bulletPositions[i].x = shipPosition.x;
                    bulletDelay = BULLET_DELAY;
                    break;
                }
            }
        }

        move_sprite(0, shipPosition.x, shipPosition.y);

        for (i = 0; i < BULLET_COUNT; i++)
        {
            move_sprite(2 + i, bulletPositions[i].x, bulletPositions[i].y);
            y = bulletPositions[i].y;
            if (y != 0)
                bulletPositions[i].y = (y < 5) ? 0 : y - 5;

            if (collisionCheck(bulletPositions[i].x, bulletPositions[i].y, 8, 8, enemy.x, enemy.y, 8, 8))
            {
                enemy.x = 8;
                enemy.y = 8;
                bulletPositions[i].x = 0;
                bulletPositions[i].y = 0;
            }
        }

        delay(10);
        bulletDelay = bulletDelay ? bulletDelay - 1 : 0;
        moveEnemy(&enemy);
        move_sprite(1, enemy.x, enemy.y);
        if (collisionCheck(shipPosition.x, shipPosition.y, 8, 8, enemy.x, enemy.y, 8, 8))
        {
            while(1){}
        }
    }
}

UINT8 collisionCheck(UINT8 x1, UINT8 y1, UINT8 w1, UINT8 h1, UINT8 x2, UINT8 y2, UINT8 w2, UINT8 h2)
{
    return ((x1 < (x2 + w2)) && ((x1 + w1) > x2) && (y1 < (h2 + y2)) && ((y1 + h1) > y2)) ? 1 : 0;
}

// void main(){
//     NR52_REG = 0x80;
//     NR50_REG = 0x77;
//     NR51_REG = 0xff;

//     while(1){
//         UBYTE joypad_state = joypad();

//         if(!joypad_state)
//             continue;

//         NR41_REG = 0x1f;
//         NR42_REG = 0xf1;
//         NR43_REG = 0x30;
//         NR44_REG = 0xc0;

//         delay(100);
//     }
// }

// void main(){
//     NR52_REG = 0x80;
//     NR50_REG = 0x77;
//     NR51_REG = 0xff;

//     while(1){
//         UBYTE joypad_state = joypad();

//         if(joypad_state){

//             NR10_REG = 0x16;
//             NR11_REG = 0x40;
//             NR12_REG = 0x73;
//             NR13_REG = 0x00;
//             NR14_REG = 0xc3;

//             delay(100);
//         }

//     }
// }

// void main(){

//     font_t min_font;
//     font_init();
//     min_font = font_load(font_min);
//     font_set(min_font);

//     set_bkg_data(38,7, BackgroudTiles);
//     set_bkg_tiles(0,0,40,18, backgroundmap);

//     set_win_tiles(0,0,5,1,windowMap);
//     move_win(7,120);

//     SHOW_BKG;
//     SHOW_WIN;
//     DISPLAY_ON;

//     while(1){
//         scroll_bkg(1,0);
//         delay(100);
//     }
// }

// void main(){

//     UINT8 currentSpriteIndex = 0;

//     set_sprite_data(0, 2, Smilter);
//     set_sprite_tile(0,0);
//     move_sprite(0, 88, 78);
//     SHOW_SPRITES;

//     while(1){

//         switch(joypad()){
//             case J_LEFT:
//             scroll_sprite(0, -10, 0);
//             break;

//             case J_RIGHT:
//             scroll_sprite(0, 10, 0);
//             break;

//             case J_UP:
//             scroll_sprite(0, 0, -10);
//             break;

//             case J_DOWN:
//             scroll_sprite(0, 0, 10);
//             break;
//         }
//         currentSpriteIndex = !currentSpriteIndex;
//         delay(10);
//     }
// }
