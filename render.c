#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "bmp.c"

int main(int argc, char *argv[]){
	if(argc < 13){printf("a sin(by) + c cos(dx), e sin(fx) + g cos(hy)\na b c d e f g h contrast shadow width height\n"); return 0;}

	const int sink = atoi(argv[9]), bg = atoi(argv[10]), bg2 = 255-bg;
	const double a = atof(argv[1]),
		  b = atof(argv[2]),
		  c = atof(argv[3]),
		  d = atof(argv[4]),
		  e = atof(argv[5]),
		  f = atof(argv[6]),
		  g = atof(argv[7]),
		  h = atof(argv[8]),
		  srx = atof(argv[11]),
		  sry = atof(argv[12]);
	double x = .1, y = .1;

	const int szx = 1200, szy = abs((int)(szx * sry / srx));

	printf("grid alloc... "), fflush(stdout);
	unsigned int *grid = malloc(sizeof(int) * szx * szy);
	printf("fill... "), fflush(stdout);
	for(int i=0; i<szx*szy; ++i) grid[i] = 0;
	printf("done!\n");

	for(unsigned long long i=1; i<=50000000ull; ++i){
		if(i % 2500000ull == 0) printf("%llu ", i/2500000ull), fflush(stdout);
		int tx = (int)(((x+srx)/srx/2)*szx),
			ty = (int)(((sry-y)/sry/2)*szy);
		if(tx >= 0 && tx < szx && ty >= 0 && ty < szy) ++grid[tx+ty*szx];

		double nx = a*sin(b*y)+c*cos(d*x),
			   ny = e*sin(f*x)+g*cos(h*y);
		x = nx, y = ny;
	}

	printf("\nimg alloc... "), fflush(stdout);

	unsigned char *image = malloc(sizeof(unsigned char)*szx*szy*3);

	printf("fill... "), fflush(stdout);

	int *p = grid, m = 0;
	for(int i=0; i<szx; ++i)for(int j=0; j<szy; ++j)
		m = *p > m ? *p : m, ++p;
	p = grid;
	for(int i=0; i<szy; ++i)for(int j=0; j<szx; ++j){
		float col = (float)(*p)/m;
		for(int k=0; k<sink; ++k) col = log2f(col + 1.);
		col = (bg + col*bg2)/255;
		if(col > 1) col = 1;
		if(*p == 0) col = 0;
		image[i*szx*3+j*3+0] = 230-(unsigned char)(col*(1.-.6)*230);
		image[i*szx*3+j*3+1] = 225-(unsigned char)(col*(1.-.4)*225);
		image[i*szx*3+j*3+2] = 210-(unsigned char)(col*(1.-.1)*210);
		++p;
	}

	printf("done!\n");

	generateBitmapImage(image, szy, szx, "strange-attractor.bmp");

	system("convert strange-attractor.bmp processed.png");
}
