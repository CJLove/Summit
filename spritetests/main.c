#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <cx16.h>
#include <conio.h>
#include <cbm.h>

static const
#include "skierLeft4.inc"
const
#include "skierLeft3.inc"
const
#include "skierLeft2.inc"
const
#include "skierLeft1.inc"
const
#include "skierDown.inc"
const
#include "skierCrash.inc"
const
#include "skierTree.inc"

// VMEM addresses for sprite data
#define SKIERLEFT4  0x110000
#define SKIERLEFT3  0x111000
#define SKIERLEFT2  0x112000
#define SKIERLEFT1  0x113000
#define SKIERDOWN   0x114000
#define SKIERCRASH  0x115000
#define TREE   0x116000

#define MAXTREES     2

struct tree {
    uint16_t x;
    uint16_t y;
};

void initTree(struct tree *t)
{
    t->x = (rand() % 575) + 4;
    t->y = 425;
}

struct tree trees[MAXTREES];
uint8_t treeMask = 0;

int main()
{
    uint16_t x = 200;
    uint16_t dx = 0;
    uint16_t y = 100;
    uint8_t pos = 4;
    uint16_t i = 0;
    uint32_t addrs[] = { SKIERLEFT4, SKIERLEFT3, SKIERLEFT2, SKIERLEFT1, SKIERDOWN, SKIERLEFT1, SKIERLEFT2, SKIERLEFT3, SKIERLEFT4 };
    uint8_t flip[] =   {  0,  0,  0,  0, 0, 1, 1, 1, 1 };
    int16_t deltaX[] = { -4, -3, -2, -1, 0, 1, 2, 3, 4 };
    int16_t deltaY[] = {  1,  1,  3,  3, 5, 3, 3, 1, 1 };
    uint16_t dy = 5;

    // Read VIA1 register in memory as a seed
    uint16_t *seed = (uint16_t *) 0x9f64;

    srand(*seed);
//    printf("seed=%d\n",*seed);

    // Switch back to the uppercase character set.
    cbm_k_bsout(CH_FONT_UPPER);

    // Attr0:
    vpoke((SKIERDOWN >> 5) & 0xFF, 0x1F5000 );
    // Attr1: 
    VERA.data0 = (1 << 7) | (SKIERDOWN >> 13);
    // Attr2: x co-ordinate, bits 7:0
    VERA.data0 = x & 0xff;
    // Attr3: x co-ordinate, bits 9:8
    VERA.data0 = x >> 8;
    // Attr4: y co-ordinate, bits 7:0
    VERA.data0 = y & 0xFF;
    // Attr5: y co-ordinate, bits 9:8
    VERA.data0 = y >> 8;
    // Attr6: z-depth: in front of layer 1
    VERA.data0 = (3 << 2);
    // Attr7: Height, width
    VERA.data0 = 0xf0;

    for (i = 0; i < MAXTREES; i++) {
        // Initialize state info for tree
        initTree(&trees[i]);

        // Attr0
        vpoke((TREE >> 5) & 0xff, 0x1F5008 + i*8);
        // Attr1
        VERA.data0 = (1 << 7) | (TREE >> 13);
        // Attr2
        VERA.data0 = trees[i].x & 0xff;
        // Attr3
        VERA.data0 = trees[i].x >> 8;
        // Attr4
        VERA.data0 = trees[i].y & 0xff;
        // Attr5
        VERA.data0 = trees[i].y >> 8;
        // Attr6
        VERA.data0 = (3 << 2);
        // Attr7
        VERA.data0 = 0xf0;
    }

    // Copy sprite data into video RAM.
    vpoke(skierLeft4[0], SKIERLEFT4);
    for (i = 0; i < 64*64; i++) {
        VERA.data0 = skierLeft4[i];
    }
    vpoke(skierLeft3[0], SKIERLEFT3);
    for (i = 0; i < 64*64; i++) {
        VERA.data0 = skierLeft3[i];
    }
    vpoke(skierLeft2[0], SKIERLEFT2);
    for (i = 0; i < 64*64; i++) {
        VERA.data0 = skierLeft2[i];
    }
    vpoke(skierLeft1[0], SKIERLEFT1);
    for (i = 0; i < 64*64; i++) {
        VERA.data0 = skierLeft1[i];
    }
    vpoke(skierDown[0], SKIERDOWN);
    for (i = 0; i < 64*64; i++) {
        VERA.data0 = skierDown[i];
    }
    vpoke(skierCrash[0], SKIERCRASH);
    for (i = 0; i < 64*64; i++) {
        VERA.data0 = skierCrash[i];
    }
    vpoke(skierTree[0], TREE);
    for (i = 0; i < 64*64; i++) {
        VERA.data0 = skierTree[i];
    }

    // Enable sprites
    vpoke(0x01, 0x0F4000);

    do {
        waitvsync();

        if (kbhit()) {
            char c = cgetc();
            if (c == 'j') {
                if (pos > 0) {
                    pos--;
                    dx = deltaX[pos];
                    dy = deltaY[pos];
                    // Change sprite graphic
                    vpoke((addrs[pos] >> 5) & 0xFF, 0x1F5000 );
                    VERA.data0 = (1 << 7) | (addrs[pos] >> 13);
                    // Change sprite h-flip
                    vpoke((3 << 2) | flip[pos],0x1F5006);
                }

            } else if (c == 'k') {
                if (pos < 8) {
                    pos++;
                    dx = deltaX[pos];
                    dy = deltaY[pos];
                    // Change sprite graphic
                    vpoke((addrs[pos] >> 5) & 0xFF, 0x1F5000 );
                    VERA.data0 = (1 << 7) | (addrs[pos] >> 13);                    
                    // Change sprit h-flip
                    vpoke((3 << 2) | flip[pos],0x1F5006);
                }

            }
        }
        // Update X position
        if (((x + dx) > 575) ||
            ((x + dx) < 4)) {
            i = 4;
            dx = deltaX[i];
            dy = 0;
            // Change sprite graphic to crash
            vpoke((SKIERCRASH >> 5) & 0xFF, 0x1F5000 );
            VERA.data0 = (1 << 7) | (SKIERCRASH >> 13);
        }
        x += dx;
        vpoke(x & 0xff, 0x1F5002);
        VERA.data0 = x >> 8;

        // Update tree(s)
        for (i = 0; i < MAXTREES; i++) {
            if (trees[i].y < 6) {
                // Tree scrolling off of the top of screen
                initTree(&trees[i]);
                //printf("initTree() x=%d\n",trees[i].x);

                vpoke(trees[i].x & 0xff, 0x1F500a + i*8);
                VERA.data0 = trees[i].x >> 8;
                continue;
            }
            trees[i].y -= dy;
            vpoke(trees[i].y & 0xff, 0x1F500c + i*8);
            VERA.data0 = trees[i].y >> 8;
        }

    } while (!kbhit());
    cgetc();

    // Disable sprite
    vpoke(0x00, 0x0F4000);

    return 0;
}

