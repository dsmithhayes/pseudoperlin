#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define WIDTH		1024
#define HEIGHT		1024
#define	MAX_PPM_COL	255

double	noise[WIDTH][HEIGHT];

void      rough_noise();
double    smooth_noise(double x, double y);
double    turbulence(double x, double y, double size);
double    random_in_range (double min, double max);

static struct color {
    unsigned char r, g, b;
} output[WIDTH*HEIGHT];

int x, y;

int main(int argc, char *argv[])
{
    rough_noise();

    struct color *itr = output;

    FILE * fp;
    fp = fopen (argv[1], "w+");

    fprintf(fp, "%s %d %d %d \n", "P6", WIDTH, HEIGHT, MAX_PPM_COL);

    for(x = 0; x < WIDTH; ++x)
        for(y = 0; y < HEIGHT; ++y) {
            /* random_in_range is too noisy, so we use pre-defined numbers for now. */
            fprintf(fp, "%c", itr->r  = turbulence(x, y, 32));
            fprintf(fp, "%c", itr->g  = turbulence(x, y, 64));
            fprintf(fp, "%c", itr->b  = turbulence(x, y, 96));
            itr++;
        }

    fclose(fp);
    return 0;
}


void rough_noise()
{
    srand((unsigned)time(NULL));

    for (x = 0; x < WIDTH; ++x)
        for (y = 0; y < HEIGHT; ++y)
            noise[x][y] = (rand() % RAND_MAX) / (double)RAND_MAX;
}

double smooth_noise(double x, double y)
{
    /* get fractional part of x and y */
    double fractX = x - (int)(x);
    double fractY = y - (int)(y);

    /* wrap around */
    int x1 = ((int)(x) + WIDTH) % WIDTH;
    int y1 = ((int)(y) + HEIGHT) % HEIGHT;

    /* neighbour values */
    int x2 = (x1 + WIDTH - 1) % WIDTH;
    int y2 = (y1 + HEIGHT - 1) % HEIGHT;

    /* smooth the noise with bilinear interpolation */
    double value = 0.0;
    value += fractX       * fractY       * noise[x1][y1];
    value += fractX       * (1 - fractY) * noise[x1][y2];
    value += (1 - fractX) * fractY       * noise[x2][y1];
    value += (1 - fractX) * (1 - fractY) * noise[x2][y2];

    return value;
}

double turbulence(double x, double y, double size)
{
    double value = 0.0, initial_size = size;
    int int_size = (int)floor(size);
    int offset_x[int_size], offset_y[int_size];

    int a, b;

    for (a = 0; a < int_size; ++a) {
        offset_x[a] = (rand() % RAND_MAX) / (double)RAND_MAX;
    }
    for (b = 0; b < int_size; ++b) {
        offset_y[b] = (rand() % RAND_MAX) / (double)RAND_MAX;
    }

    while(size >= 1) {
        value += smooth_noise(x / size + offset_x[int_size], y / size + offset_y[int_size]) * size;
        size /= 2.0;
        int_size /= 2.0;
    }

    return(128.0 * value / initial_size);
}

double random_in_range (double min, double max)
{
    srand((unsigned)time(NULL));
    double result = min + rand() / (RAND_MAX / (max - min + 1.0) + 1.0);
    return result;
}
