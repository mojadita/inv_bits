## INVERT BITS.

This program produces a function to efficiently invert the bits
of an `uint64_t` integer.  The typical output of this program
is like this:

```
#include <stdint.h>

uint64_t
inv_32bits(uint64_t in)
{
    in = (in & 0xffff0000UL) >> 16
       | (in & 0x0000ffffUL) << 16;
    in = (in & 0xff00ff00UL) >> 8
       | (in & 0x00ff00ffUL) << 8;
    in = (in & 0xf0f0f0f0UL) >> 4
       | (in & 0x0f0f0f0fUL) << 4;
    in = (in & 0xccccccccUL) >> 2
       | (in & 0x33333333UL) << 2;
    in = (in & 0xaaaaaaaaUL) >> 1
       | (in & 0x55555555UL) << 1;
    return in;
} /* inv_32bits */
```
or similarly, for a non exact power of two:
```
#include <stdint.h>

uint64_t
inv_17bits(uint64_t in)
{
    in = (in & 0x1fe00UL) >> 9
       | (in & 0x000ffUL) << 9
       | (in & 0x00100UL);
    in = (in & 0x1e0f0UL) >> 4
       | (in & 0x01e0fUL) << 4
       | (in & 0x00100UL);
    in = (in & 0x198ccUL) >> 2
       | (in & 0x06633UL) << 2
       | (in & 0x00100UL);
    in = (in & 0x154aaUL) >> 1
       | (in & 0x0aa55UL) << 1
       | (in & 0x00100UL);
    return in;
} /* inv_17bits */
```
