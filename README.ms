## INVERT BITS.

This program produces a function to efficiently invert the bits
of an `uint64_t` integer.  The typical output of this program
is like this:

```
#include <stdint.h>

uint64_t
inv_32bits(uint64_t in)
{
    in = (in & 0xffff0000) >> 16
       | (in & 0x0000ffff) << 16;
    in = (in & 0xff00ff00) >> 8
       | (in & 0x00ff00ff) << 8;
    in = (in & 0xf0f0f0f0) >> 4
       | (in & 0x0f0f0f0f) << 4;
    in = (in & 0xcccccccc) >> 2
       | (in & 0x33333333) << 2;
    in = (in & 0xaaaaaaaa) >> 1
       | (in & 0x55555555) << 1;
    return in;
} /* inv_32bits */
```
