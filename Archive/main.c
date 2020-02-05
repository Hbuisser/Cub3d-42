#include <stdio.h>
#include <stdlib.h>

#define COLOR_DEFAULT	"\x1B[0m"
#define COLOR_RED	"\x1B[31m"
#define COLOR_GREEN	"\x1B[32m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

void start_cub3d(char *folder, char *name)
{
	char	cmd[4096];

	printf("Testing %s...\n", name);
	printf(RED "======================\n");
	sprintf(cmd, "./cub3d %s/%s.cub", folder, name);
	system(cmd);
	printf(GRN "======================\n\n" RESET);
}

int main(int argc, char **argv)
{
	printf("Testing open maps...\n");
	printf("You should return an error in any case.\n\n");
	start_cub3d("open", "open_up");
	start_cub3d("open", "open_down");
	start_cub3d("open", "open_left");
	start_cub3d("open", "open_right");
	start_cub3d("open", "open_corner_1");
	start_cub3d("open", "open_corner_2");

	printf("Testing respawn maps...\n");
	printf("You should return an error in any case.\n\n");
	start_cub3d("respawn", "res_1");
	start_cub3d("respawn", "res_2");
	start_cub3d("respawn", "res_3");

	printf("Testing malformed maps...\n");
	printf("You should return an error in any case.\n\n");
	start_cub3d("malformed", "ma_1");
	start_cub3d("malformed", "ma_2");
	start_cub3d("malformed", "ma_3");
	start_cub3d("malformed", "ma_4");
	start_cub3d("malformed", "ma_5");
	start_cub3d("malformed", "ma_6");
	start_cub3d("malformed", "ma_7");
	start_cub3d("malformed", "ma_8");
	start_cub3d("malformed", "ma_9");
	start_cub3d("malformed", "ma_10");

	printf("Testing malformed path...\n");
	printf("You should return an error in any case.\n\n");
	start_cub3d("path", "path_1");
	start_cub3d("path", "path_2");
	start_cub3d("path", "path_3");
	start_cub3d("path", "path_4");
	start_cub3d("path", "path_5");
	start_cub3d("path", "path_6");

	printf("Testing multiples path...\n");
	printf("If you support these maps check for leaks.\n\n");
	start_cub3d("multipath", "path_1");
	start_cub3d("multipath", "path_2");
	start_cub3d("multipath", "path_3");
	start_cub3d("multipath", "path_4");
	start_cub3d("multipath", "path_5");

	printf("Testing possible maps...\n");
	printf("You have to handle all these maps. The mad one is optionnal.\n\n");
	start_cub3d("possible", "map_1");
	start_cub3d("possible", "map_2");
	start_cub3d("possible", "map_3");
	start_cub3d("possible", "path_1");
	start_cub3d("possible", "path_2");
	start_cub3d("possible", "mad_path_1");

	// test ceiling / floor color.
	// test sprites

	/*printf("Testing resolution...\n");
	printf("You can return an error, or better, handle the problem.\n\n");
	start_cub3d("res", "res_1");
	start_cub3d("res", "res_2");
	start_cub3d("res", "res_3");
	start_cub3d("res", "res_4");
	start_cub3d("res", "res_5");
	start_cub3d("res", "res_6");
	start_cub3d("res", "res_7");
	start_cub3d("res", "res_8");
	start_cub3d("res", "res_9");
	start_cub3d("res", "res_10");
	start_cub3d("res", "res_11");
	start_cub3d("res", "res_12");
	start_cub3d("res", "res_13");
	start_cub3d("res", "res_14");*/
	return (0);
}
