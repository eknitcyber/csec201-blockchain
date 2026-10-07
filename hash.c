#include "hash.h"
#include <stdint.h>

unsigned char* SSHA(const unsigned char* msg, size_t length) {
    unsigned char A = 56;
    unsigned char B = 99;
    unsigned char C = 102;
    unsigned char D = 67;
    unsigned char E = 76;

    for (int i = 0; i < length; i++) {
        for (int round = 0; round < 8; round++) {
            unsigned char g = (B & C) | (C & D);

            unsigned char old_A = A;
            unsigned char old_B = B;
            unsigned char old_E = E;

            A = old_E;
            B = old_A;
            C = (old_A >> 2) + old_E;
            D = (old_A >> 2) ^ (old_B >> 1);
            E = (old_B >> 1) + g + msg[i];
        }
    }

    unsigned char* digest =
        (unsigned char*)malloc(DIGEST_SIZE * sizeof(unsigned char));

    digest[0] = A;
    digest[1] = B;
    digest[2] = C;
    digest[3] = D;
    digest[4] = E;

    return digest;
}


unsigned char* SSHA2(const unsigned char* msg, size_t length)
{
    /*
     * Five 8-bit state values, initialized exactly as specified.
     */
    uint8_t A = 56;
    uint8_t B = 99;
    uint8_t C = 102;
    uint8_t D = 67;
    uint8_t E = 76;

    for (size_t i = 0; i < length; ++i) {
        /*
         * Each input byte is processed through 8 rounds.
         */
        for (int round = 0; round < 8; ++round) {
            uint8_t oldA = A;
            uint8_t oldB = B;
            uint8_t oldC = C;
            uint8_t oldD = D;
            uint8_t oldE = E;

            /*
             * Operations from the diagram:
             *
             *   A >> 2
             *   B >> 1
             *
             *   (B & C) | (C & D)
             *
             *   (A >> 2) ^ (B >> 1)
             *
             *   E' = ((B & C) | (C & D)) + msg[i]
             *   C' = (B >> 1) + E'
             *   D' = (A >> 2) ^ (B >> 1)
             *
             * State movement:
             *   A' = E
             *   B' = A
             */
            uint8_t b_shift = (uint8_t)(oldB >> 1);
            uint8_t a_shift = (uint8_t)(oldA >> 2);

            uint8_t and1 = (uint8_t)(oldB & oldC);
            uint8_t and2 = (uint8_t)(oldC & oldD);
            uint8_t or_result = (uint8_t)(and1 | and2);

            uint8_t d_new = (uint8_t)(a_shift ^ b_shift);

            uint8_t e_new =
                (uint8_t)(or_result + msg[i]);

            uint8_t c_new =
                (uint8_t)(b_shift + e_new);

            A = oldE;
            B = oldA;
            C = c_new;
            D = d_new;
            E = e_new;
        }
    }

    /*
     * Final output is the five state values A, B, C, D, E,
     * in that order, as shown at the bottom of the diagram.
     */
    unsigned char* digest = malloc(5);

    if (digest == NULL)
        return NULL;

    digest[0] = A;
    digest[1] = B;
    digest[2] = C;
    digest[3] = D;
    digest[4] = E;

    return digest;
}


int digest_equal(struct Digest digest1, struct Digest digest2) {
    return ((digest1.hash0 == digest2.hash0) &&
        (digest1.hash1 == digest2.hash1) &&
        (digest1.hash2 == digest2.hash2) &&
        (digest1.hash3 == digest2.hash3) &&
        (digest1.hash4 == digest2.hash4));
}


void printDigest(struct Digest digest) {
    printf("%d %d %d %d %d\n",
        digest.hash0,
        digest.hash1,
        digest.hash2,
        digest.hash3,
        digest.hash4);
}