#include "../includes/cub3d.h"
#include <math.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 1920
#define screenHeight 1080

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void verLine(t_game *game, int x, int y1, int y2, int color)
{
	int i;
	int start_y = y1;
	int end_y = y2;

	if (end_y < start_y) { start_y += end_y; end_y = start_y - end_y; start_y -= end_y; } //swap y1 and y2
	if (end_y < 0 || start_y >= screenHeight || x < 0 || x >= screenWidth) return; //no single point of the line is on screen
	if (start_y < 0) start_y = 0; //clip
	if (end_y >= screenHeight) end_y = screenHeight - 1; //clip

	for (i = start_y; i <= end_y; i++) {
		image_put_pixel(game->screen, game->screen->img, x, i, color);
	}
}

void	draw_map(t_game *game) {
	game->screen->img = init_image(game->screen, 1920, 1080);


	int w = screenWidth;

	for(int x = 0; x < screenWidth; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double) w - 1; //x-coordinate in camera space
		double rayDirX = game->player->dirX + game->planeX * cameraX;
		double rayDirY = game->player->dirY + game->planeY * cameraX;
		//which box of the map we're in
		int mapX = (int) game->player->posX;
		int mapY = (int) game->player->posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirX == 0) ? 1e30 : abs((int)(1 / rayDirX));
		double deltaDistY = (rayDirY == 0) ? 1e30 : abs((int)(1 / rayDirY));
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player->posY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		//Calculate height of line to draw on screen
		int lineHeight = (int)(screenHeight / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if(drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;
		//choose wall color
		int color = 0x00FF0000; // red

		//give x and y sides different brightness
		//if (side == 1)
			//color = color / 2;

		//draw the pixels of the stripe as a vertical line
		verLine(game, x, drawStart, drawEnd, color);

	}

	//image_put_pixel(screen, image, 0, 0, 0x00FF0000);
	//image_put_pixel(screen, image, 1, 1, 0x00FF0000);
	display_image(game->screen, game->screen->img);
}

int	key_event(int key_code, t_game *game) {

	if(key_code == 119)
	{
		if(worldMap[(int) (game->player->posX + game->player->dirX * game->player->move_speed)][(int) game->player->posY] == 0)
		game->player->posX += game->player->dirX * game->player->move_speed;
		if(worldMap[(int) game->player->posX][(int) (game->player->posY + game->player->dirY * game->player->move_speed)] == 0)
		game->player->posY += game->player->dirY * game->player->move_speed;
	}
	if(key_code == 115)
	{
		if(worldMap[(int) (game->player->posX - game->player->dirX * game->player->move_speed)][(int) game->player->posY] == 0)
		game->player->posX -= game->player->dirX * game->player->move_speed;
		if(worldMap[(int) game->player->posX][(int) (game->player->posY - game->player->dirY * game->player->move_speed)] == 0)
		game->player->posY -= game->player->dirY * game->player->move_speed;
	}
	if(key_code == 100)
	{
		double oldDirX = game->player->dirX;
		game->player->dirX = game->player->dirX * cos(-game->player->rot_speed) - game->player->dirY * sin(-game->player->rot_speed);
		game->player->dirY = oldDirX * sin(-game->player->rot_speed) + game->player->dirY * cos(-game->player->rot_speed);
		double oldPlaneX = game->planeX;
		game->planeX = game->planeX * cos(-game->player->rot_speed) - game->planeY * sin(-game->player->rot_speed);
		game->planeY = oldPlaneX * sin(-game->player->rot_speed) + game->planeY * cos(-game->player->rot_speed);
	}
	if(key_code == 97)
	{
		double oldDirX = game->player->dirX;
		game->player->dirX = game->player->dirX * cos(game->player->rot_speed) - game->player->dirY * sin(game->player->rot_speed);
		game->player->dirY = oldDirX * sin(game->player->rot_speed) + game->player->dirY * cos(game->player->rot_speed);
		double oldPlaneX = game->planeX;
		game->planeX = game->planeX * cos(game->player->rot_speed) - game->planeY * sin(game->player->rot_speed);
		game->planeY = oldPlaneX * sin(game->player->rot_speed) + game->planeY * cos(game->player->rot_speed);
	}
	mlx_clear_window(game->screen->holder, game->screen->window->holder);
	draw_map(game);
	printf("key code %d\n", key_code);
	return key_code;
}


int main(int argc, char **argv) {
	(void) argc;
	(void) argv;
	t_game	*game = calloc(sizeof(t_game), 1);
	game->screen = init_screen(1920, 1080, "HOla");
	game->player = calloc(sizeof(t_player), 1);
	game->player->posX = 22;
	game->player->posY = 12;
	game->player->dirX = -1;
	game->player->dirY = 0;
	game->player->move_speed = 0.5;
	game->player->rot_speed = 0.3;
	game->planeX = 0;
	game->planeY = 0.90;
	draw_map(game);
	mlx_hook(game->screen->window->holder, 2, 1L << 0, key_event, game);
	//mlx_hook(screen->window->holder, 17, 1L << 17, close_window, d);
	mlx_loop(game->screen->holder);
	return 0;
}
