/* mktab.c -- creates a table of bit patterns
 * to exchange bits in order to invert the weights
 * of the bits (exchange the MSB with the LSB, and
 * so on)
 * Author: Luis Colorado <luis.colorado.urcola@gmail.com>
 * Date: Sat Jul 30 11:25:33 EEST 2022
 * Copyright: (c) 2022 Luis Colorado.  All rights reserved.
 * License: BSD.
 */
#include <assert.h>
#include <errno.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define DEFAULT_N      (32)

#define F(_F_fmt) "%s:%04u:%s:"_F_fmt,__FILE__,__LINE__,__func__
#define DEB_TAIL(_DEB_TAIL_fmt, ...) /* printf(_DEB_TAIL_fmt,##__VA_ARGS__) */
#define DEB(_DEB_fmt, ...) DEB_TAIL(F("DEBUG: "_DEB_fmt),##__VA_ARGS__)

struct masks {
    uint64_t lft, rgt, unmov;
    unsigned shift;
};

int compile(
        unsigned nbit,
        struct masks *m,
        int pos,
        int lvl)
{
    DEB("%s(nbit=%d, m=%p, pos=%d, lvl=%d);\n",
        __func__, nbit, m, pos, lvl);

    if (!nbit) return --lvl;

    int      odd     = nbit & 1;
             nbit  >>= 1;
    int      shift   = m->shift
                     = nbit + odd;
    uint64_t all1    = (1UL << nbit) - 1;
             m->lft |= all1 << (pos + shift);
             m->rgt |= all1 << pos;

    if (odd)
        m->unmov    |= 1UL << (pos + nbit);

    int      lvl1    = compile(nbit, ++m, pos,         ++lvl),
             lvl2    = compile(nbit,   m, pos + shift,   lvl);

    assert(lvl1 == lvl2);

    return lvl1;
}

int
main(int argc, char **argv)
{
    int   opt;
    int   N   = DEFAULT_N;
    FILE *out = stdout;

    while ((opt = getopt(argc, argv, "n:")) != EOF) {
        switch (opt) {
        case 'n':
			N = atoi(optarg);
			break;
        case 'o':
			out = fopen(optarg, "a+");
            if (!out) {
                fprintf(stderr,
                        "%s: %s\n",
                        optarg,
                        strerror(errno));
                out = stdout;
            }
            break;
        }
    }
    int digs = (N + 3) >> 2;

    struct masks msk[10];
    bzero(msk, sizeof msk);

    int lvl = compile(N, msk, 0, 0);
    DEB("compile(N=%d, msk, 0, 0) ==> %d\n", N, lvl);

    printf("#include <stdint.h>\n"
           "uint64_t\n"
           "inv_%dbits(uint64_t in)\n"
           "{\n",
           N);

    for (int i = 0; i < lvl; i++) {
        if (i) msk[i].unmov |= msk[i-1].unmov;
        int disp             = msk[i].shift;
        const char *sep      = "";

        printf("    in = (in & 0x%0*lx)",
                digs, msk[i].lft);
        if (disp)
            printf(" >> %d", disp);
        printf("\n       | (in & 0x%0*lx)",
                digs, msk[i].rgt);
        if (disp)
            printf(" << %d", disp);
        if (msk[i].unmov) {
            printf("\n       | (in & 0x%0*lx)",
                   digs, msk[i].unmov);
        }
        printf(";\n");
    } /* for */
    printf("    return in;\n} "
		   "/* inv_%dbits */\n",
           N);
    return 0;
} /* main */
