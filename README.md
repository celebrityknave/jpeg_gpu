# CAJED -- CUDA-accelerated JPEG Encoder-Decoder

This project came about after finding some issues with other encoders
available. Freely available GPU-accelerated JPEG encoding libraries such
NVIDIA's nvJPEG aren't too performant in comparison with some of the licensed
methods available.

This project is primarily a collection of whatever disgusting hacks I'm able to
fit in to try and make this as fast an encoder as possible. If I can match
FastVideo FastCompression's achievement of 26 monochrome 50MP images per second
on my terrible laptop, it will be complete. I'll be making it in several main
parts:

1. Develop the initial encoder and decoder in C. As long as the encoder can
   produce a monochrome image interpretable by image-viewing programs, it's
fine.
2. Implement CUDA integration. As long as it can off-load the DCT to the GPU,
   this will at least initially be complete.
3. Throw in the filthy hacks. This one will take a while. I have a number of
   papers I've dug up which use some neat tricks, but some of them will need me
to read up on unfamiliar maths.
4. SIMD/SIMT hell. ala JPEG-turbo. I'm as yet unfamiliar with SIMT
   instructions, and they may not require as much hand-crafting as SIMD.

There's also a decent chance I'll want to change to a less-proprietary GPGPU
library if some of the competing libraries have improved by then. We'll find
out when we get here. Will need to change the name if so, which will be tragic. 

If I get to the last step and JPEG is still a relevant standard, I'll be
surprised and disappointed.

## Build instructions

```
$ mkdir build
$ cd build
$ cmake ..
$ make -j8
```
