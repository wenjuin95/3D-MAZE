#include "raycasting.h"

/**
 * @brief initialize the player
 * @param player the player structure
 * @note 1. set the player position
 * @note 2. set the key flag to false
 */
void init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2;

	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;

	player -> key_turn_left = false;
	player -> key_turn_right = false;
}

/**
 * @brief handle the key press event
 * @param keycode the key code
 * @param player the player structure
 * @return 0
 * @note 1. set flag to true when the key is pressed
 */
int key_press(int keycode, t_player *player)
{
	printf("player x: %f, y: %f\n", player->x, player->y);
	if (keycode == ESC)
		exit(0);
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->key_turn_left = true;
	if (keycode == RIGHT)
		player->key_turn_right = true;
	return (0);
}

/**
 * @brief handle the key release event
 * @param keycode the key code
 * @param player the player structure
 * @return 0
 * @note 1. set flag to false when the key is released
 */
int key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->key_turn_left = false;
	if (keycode == RIGHT)
		player->key_turn_right = false;
	return (0);
}

/**
 * @brief move the player
 * @param player the player structure
 * @note 1. move the player based on the key press event
 * @note 2. "speed" is the speed of the player
 */
void move_player(t_player *player)
{
	int speed = 5;
	float angle_speed = 0.1;
	float cos_angle = cos(player->angle);
	float sin_angle = sin(player->angle);

	if (player->key_turn_left)
		player->angle -= angle_speed;
	if (player->key_turn_right)
		player->angle += angle_speed;
	if (player->angle > 2 * PI) // if player angle is over the 2 * PI
		player->angle = 0;
	if (player->angle < 0) // if player angle is under the 0
		player->angle = 2 * PI;
	if (player->key_up)
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	if (player->key_down)
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}
	if (player->key_left)
	{
		player->x += sin_angle * speed;
		player->y -= cos_angle * speed;
	}
	if (player->key_right)
	{
		player->x -= sin_angle * speed;
		player->y += cos_angle * speed;
	}

}
