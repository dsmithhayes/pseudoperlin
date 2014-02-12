Multiple layers of perlin noise are needed.

The background is always black.

Create 3-4 layers of 3D perlin noise (3D, because we need to animate it and 2D perlin noise just scrolls and that's not the desired effect).

1 or 2 layers of "ridged" perlin noise, randomly colored (possibly using another set of 3D perlin noise?) altered with alpha texture (again, perlin noise?), so that parts of the black background will show through randomly. Use alpha blending (additive blending might also look good) to mix these layers together.

Then animate them all. Slow, slow, slow as hell, but should look a lot like our image. If the perlin is tileable (like it should be) we can alter the time steps so that the entire animation loops and we can prerender it if realtime is too slow.

Speedups: use GPU to generate 2-3 tiling perlin noise textures, the mirror/repeat them across pregenerated larger perlin noise textures and use the smaller textures to colorize/change the alpha values of the large textures. Still slow, but should be faster because only a few dynamic textures are needed.

http://www.inear.se/2010/04/ridged-perlin-noise/
http://iquilezles.org/www/articles/morenoise/morenoise.
