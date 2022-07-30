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
or similarly, for a non exact power of two:
```
#include <stdint.h>

uint64_t
inv_17bits(uint64_t in)
{
    in = (in & 0x1fe00) >> 9
       | (in & 0x000ff) << 9
       | (in & 0x00100);
    in = (in & 0x1e0f0) >> 4
       | (in & 0x01e0f) << 4
       | (in & 0x00100);
    in = (in & 0x198cc) >> 2
       | (in & 0x06633) << 2
       | (in & 0x00100);
    in = (in & 0x154aa) >> 1
       | (in & 0x0aa55) << 1
       | (in & 0x00100);
    return in;
} /* inv_17bits */
```
