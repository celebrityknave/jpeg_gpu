# GPU-accelerated JPEG Encoder
This project came about after finding some issues with other encoders available. Freely available GPU-accelerated JPEG encoding libraries such NVIDIA's nvJPEG aren't too performant in comparison with some of the licensed methods available such as FastCompression.

This project is primarily a collection of whatever disgusting hacks I'm able to fit in to try and make this as fast an encoder as possible. If I can match FastCompression's achievement of 26 monochrome 50MP images per second on my terrible laptop, it will be complete. I'll be making it in several parts:

1. Develop the initial encoder in C. As long as it can produce a monochrome image interpretable by image-viewing programs, it's fine.
2. Implement CUDA integration. As long as it can off-load the DCT to the GPU, this will at least initially be complete.
3. Throw in the filthy hacks.

4. SIMD hell. ala JPEG-turbo. If I get here and JPEG is still a relevant standard, I'll be surprised and disappointed.
