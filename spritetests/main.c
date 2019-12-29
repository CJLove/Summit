#include <stdint.h>
#include <stdio.h>
#include <cx16.h>
#include <conio.h>
#include <cbm.h>

static const
#include "skierLeft2.inc"
const
#include "skierLeft1.inc"
const
#include "skierDown.inc"
const
#include "skierRight1.inc"
const
#include "skierRight2.inc"
const
#include "skierCrash.inc"

// VMEM addresses for sprite data
#define SKIERLEFT2  0x110000
#define SKIERLEFT1  0x110800
#define SKIERDOWN   0x111000
#define SKIERRIGHT1 0x111800
#define SKIERRIGHT2 0x112000
#define SKIERCRASH  0x112800

int main()
{
    uint16_t x = 200;
    uint16_t dx = 0;
    uint16_t y = 100;
    uint16_t i = 0;
    uint32_t addrs[] = { SKIERLEFT2, SKIERLEFT1, SKIERDOWN, SKIERRIGHT1, SKIERRIGHT2 };
    int16_t deltaX[] = { -2, -1, 0, 1, 2 };
    int16_t deltaY[] = { 1, 2, 3, 2, 1 };

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
    VERA.data0 = 0xe0;

    // Copy sprite data into video RAM.
    vpoke(skierLeft2[0], SKIERLEFT2);
    for (i = 0; i < 64*32; i++) {
        VERA.data0 = skierLeft2[i];
    }
    vpoke(skierLeft1[0], SKIERLEFT1);
    for (i = 0; i < 64*32; i++) {
        VERA.data0 = skierLeft1[i];
    }
    vpoke(skierDown[0], SKIERDOWN);
    for (i = 0; i < 64*32; i++) {
        VERA.data0 = skierDown[i];
    }
    vpoke(skierRight1[0], SKIERRIGHT1);
    for (i = 0; i < 64*32; i++) {
        VERA.data0 = skierRight1[i];
    }
    vpoke(skierRight2[0], SKIERRIGHT2);
    for (i = 0; i < 64*32; i++) {
        VERA.data0 = skierRight2[i];
    }
    vpoke(skierCrash[0], SKIERCRASH);
    for (i = 0; i < 64*32; i++) {
        VERA.data0 = skierCrash[i];
    }

    // Enable sprite
    vpoke(0x01, 0x0F4000);

    i = 2;

    do {
        waitvsync();

        if (kbhit()) {
            char c = cgetc();
            if (c == 'j') {
                if (i > 0) {
                    i--;
                    dx = deltaX[i];
                    // Change sprite graphic
                    vpoke((addrs[i] >> 5) & 0xFF, 0x1F5000 );
                    VERA.data0 = (1 << 7) | (addrs[i] >> 13);
                }

            } else if (c == 'k') {
                if (i < 4) {
                    i++;
                    dx = deltaX[i];
                    // Change sprite graphic
                    vpoke((addrs[i] >> 5) & 0xFF, 0x1F5000 );
                    VERA.data0 = (1 << 7) | (addrs[i] >> 13);                    
                }

            }
        }
        // Update X position
        if (((x + dx) > 600) ||
            ((x + dx) < 4)) {
            i = 2;
            dx = deltaX[i];
            // Change sprite graphic to crash
            vpoke((SKIERCRASH >> 5) & 0xFF, 0x1F5000 );
            VERA.data0 = (1 << 7) | (SKIERCRASH >> 13);
        }
        x += dx;
        vpoke(x & 0xff, 0x1F5002);
        VERA.data0 = x >> 8;

    } while (!kbhit());
    cgetc();

    // Disable sprite
    vpoke(0x00, 0x0F4000);

    return 0;
}

