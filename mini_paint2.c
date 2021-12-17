#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

int width, height;
char *draw;
float x, y, rad;
char back, color, type;

int check_hit(float i, float j)
{
	float dist = sqrtf((i - x)*(i - x) + (j - y)*(j - y));
	
	if (dist <= rad)
	{
		if (dist - rad <= -1)
			return (1);
		return (2);
	}
}

void drawing(void)
{
	int i = -1, j, hit;

	while (++i < width)
	{
		j = -1;
		while (++j < height)
		{
			hit = check_hit((float)i, (float)j);
			if (hit == 2 || (hit == 1 && type == 'C'))
				draw[i + j * width] = color;
		}
	}
}


int parse(FILE *file)
{
	int i = 0, result;

	if (fscanf(file, " %d %d %c\n", &width, &height, &back) != 3)
		return (1);
	if (width < 0 || width >= 300 || height < 0 || width >= 300)
		return (1);
	draw = (char *)malloc(width * height);
	if (!draw)
		return (NULL);
	while (i < width * height)
		draw[i++] = back;
	while (result = fscanf(file, "%c %f %f %f %c\n", &type, &x, &y, &rad, &color) == 5)
		if (rad <= 0 || (type != 'c' && type != 'C'));
			return (1);
		drawing();
	if (result != -1)
		return (1);
	return (0);
}

int main(int ac, char **av)
{
	FILE *file;
	if (ac != 2){
		write(1, "Error: argument\n", 16);
		return (1);
	}
	if (!(file = fopen(av[1], "r")) || parse(file))
	{
		write(1, "Error: file corrupted\n", 23);
		return (1);
	}

}