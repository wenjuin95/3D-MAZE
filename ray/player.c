#include "raycasting.h"

/**
 * @brief initialize the player
 * @param player the player structure
 * @note 1. set the player position
 * @note 2. set the key flag to false
 */
void init_player(t_player *player)
{
	player->x = 64; //set the player x position to the center of the window
	player->y = 64; //set the player y position to the center of the window
	player->angle = 3 * PI / 2;
	/*
		0 radians: Right (positive x-axis)
		PI / 2 radians: Down (positive y-axis)
		PI radians: Left (negative x-axis)
		3 * PI / 2 radians: Up (negative y-axis)
	*/

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
void move_player(t_player *player, t_data *game)
{
    int speed = 5;
    float angle_speed = 0.03;
    float cos_angle = cos(player->angle); //cos is the triangle x cordination length
    float sin_angle = sin(player->angle); //sin is the triangle y cordination length
    float new_x, new_y;

    if (player->key_turn_left == true) // if player press the left key
        player->angle -= angle_speed;
    if (player->key_turn_right == true) // if player press the right key
        player->angle += angle_speed;

	//these to make sure angle alway stay between 0 and 2 * PI ( is ecessary for consistent trigonometric calculations)
    if (player->angle > 2 * PI) // if player angle is over 360 degree then set to 0
        player->angle = 0;
    if (player->angle < 0) // if player angle is under 0 then set to 360 degree
        player->angle = 2 * PI;

    if (player->key_up == true)
    {
        new_x = player->x + cos_angle * speed;
        new_y = player->y + sin_angle * speed;
        if (player_view(new_x, player->y, game) == false) //check if player view is not block at x cordination
			player->x = new_x; //get the new x cordination
        if (player_view(player->x, new_y, game) == false) //check if player view is not block at y cordination
			player->y = new_y; //get the new y cordination
    }
    if (player->key_down == true)
    {
        new_x = player->x - cos_angle * speed;
        new_y = player->y - sin_angle * speed;
        if (player_view(new_x, player->y, game) == false)
			player->x = new_x;
        if (player_view(player->x, new_y, game) == false)
			player->y = new_y;
    }
    if (player->key_left == true)
    {
        new_x = player->x + sin_angle * speed;
        new_y = player->y - cos_angle * speed;
        if (player_view(new_x, player->y, game) == false)
			player->x = new_x;
        if (player_view(player->x, new_y, game) == false)
			player->y = new_y;
    }
    if (player->key_right == true)
    {
        new_x = player->x - sin_angle * speed;
        new_y = player->y + cos_angle * speed;
        if (player_view(new_x, player->y, game) == false)
			player->x = new_x;
        if (player_view(player->x, new_y, game) == false)
			player->y = new_y;
    }
}
