#!/bin/bash

red='\033[0;31m'
reset='\033[0m'

echo -e "${red} MISSING FILE TYPE ${reset}"
./cub3d maps/bad/filetype_missing
echo -e ""
echo -e "${red}WRONG FILE TYPE${reset}"
./cub3d maps/bad/filetype_wrong.buc
echo -e ""
echo -e "${red}INVALID COLOR${reset}"
./cub3d maps/bad/color_invalid_rgb.cub
echo -e ""
echo -e "${red}MISING PLAYER${reset}"
./cub3d maps/bad/player_none.cub
echo -e ""
echo -e "${red}TEXTURE NO XPM${reset}"
./cub3d maps/bad/textures_not_xpm.cub
echo -e ""
echo -e "${red}MISSING CEILING${reset}"
./cub3d maps/bad/color_missing_ceiling_rgb.cub
echo -e ""
echo -e "${red}MISSING FLOOR BUT HAVE WALL${reset}"
./cub3d maps/bad/forbidden.cub
echo -e ""
echo -e "${red}PLAYER OUT OF BOUND${reset}"
./cub3d maps/bad/player_on_edge.cub
echo -e ""
echo -e "${red}WALL HOLE IN EAST${reset}"
./cub3d maps/bad/wall_hole_east.cub
echo -e ""
echo -e "${red}WALL HOLE IN NORTH${reset}"
./cub3d maps/bad/wall_hole_north.cub
echo -e ""
echo -e "${red}WALL HOLE IN SOUTH${reset}"
./cub3d maps/bad/wall_hole_south.cub
echo -e ""
echo -e "${red}WALL HOLE IN WEST${reset}"
./cub3d maps/bad/wall_hole_west.cub
echo -e ""
echo -e "${red}MISSING FLOOR${reset}"
./cub3d maps/bad/color_missing.cub
echo -e ""
echo -e "${red}MAP IN THE FIRST LINE${reset}"
./cub3d maps/bad/map_first.cub
echo -e ""
echo -e "${red}TEXTURE DIRECTORY WITHOUT XPM${reset}"
./cub3d maps/bad/textures_dir.cub
echo -e ""
echo -e "${red}MISSING FLOOR COLOR${reset}"
./cub3d maps/bad/color_missing_floor_rgb.cub
echo -e ""
echo -e "${red}MAP IN THE MIDDLE line${reset}"
./cub3d maps/bad/map_middle.cub
echo -e ""
echo -e "${red}SAME TEXTURE DIRECTION AND XPM${reset}"
./cub3d maps/bad/textures_duplicates.cub
echo -e ""
echo -e "${red}NO COLOR${reset}"
./cub3d maps/bad/color_none.cub
echo -e ""
echo -e "${red}MAP MISSING${reset}"
./cub3d maps/bad/map_missing.cub
echo -e ""
echo -e "${red}NO EXIST XPM${reset}"
./cub3d maps/bad/textures_forbidden.cub
echo -e ""
echo -e "${red}EMPTY FILE${reset}"
./cub3d maps/bad/empty.cub
echo -e ""
echo -e "${red}MAP ONLY${reset}"
./cub3d maps/bad/map_only.cub
echo -e ""
echo -e "${red}INVALID TEXTURE${reset}"
./cub3d maps/bad/textures_invalid.cub
echo -e ""
echo -e "${red}MISSING WALL${reset}"
./cub3d maps/bad/wall_none.cub
echo -e ""
echo -e "${red}EXTRA WORD${reset}"
./cub3d maps/bad/file_letter_end.cub
echo -e ""
echo -e "${red}MAP TOO SMALL${reset}"
./cub3d maps/bad/map_too_small.cub
echo -e ""
echo -e "${red}MISSING ANOTHER TEXTURE${reset}"
./cub3d maps/bad/textures_missing.cub
echo -e ""
echo -e "${red}EXTRA PLAYER${reset}"
./cub3d maps/bad/player_multiple.cub
echo -e ""
echo -e "${red}NO TEXTURE${reset}"
./cub3d maps/bad/textures_none.cub
echo -e ""
