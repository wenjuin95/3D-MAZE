#!/bin/bash

red='\033[0;31m'
blue='\033[0;34m'
reset='\033[0m'

check_error() {
    output=$("$@")
    if [ -z "$output" ] || [ "$output" == $'\n' ]; then # empty output
        echo -e "${blue}NO OUTPUT RECEIVED${reset}"
    else
        echo "$output"
    fi
}

echo -e "${red}1. MISSING FILE TYPE (filetype_missing)${reset}"
check_error ./cub3d maps/bad/filetype_missing
echo -e ""

echo -e "${red}2. WRONG FILE TYPE (filetype_wrong.buc)${reset}"
check_error ./cub3d maps/bad/filetype_wrong.buc
echo -e ""

echo -e "${red}3. INVALID COLOR (color_invalid_rgb.cub)${reset}"
check_error ./cub3d maps/bad/color_invalid_rgb.cub
echo -e ""

echo -e "${red}4. MISING PLAYER$ (player_none.cub)${reset}"
check_error ./cub3d maps/bad/player_none.cub
echo -e ""

echo -e "${red}5. TEXTURE NO XPM (textures_not_xpm.cub)${reset}"
check_error ./cub3d maps/bad/textures_not_xpm.cub
echo -e ""

echo -e "${red}6. MISSING CEILING$ (color_missing_ceiling_rgb.cub)${reset}"
check_error ./cub3d maps/bad/color_missing_ceiling_rgb.cub
echo -e ""

echo -e "${red}7. MISSING FLOOR BUT HAVE WALL (forbidden.cub)${reset}"
check_error ./cub3d maps/bad/forbidden.cub
echo -e ""

echo -e "${red}8. PLAYER OUT OF BOUND (player_on_edge.cub)${reset}"
check_error ./cub3d maps/bad/player_on_edge.cub
echo -e ""

echo -e "${red}9. WALL HOLE IN EAST (wall_hole_east.cub)${reset}"
check_error ./cub3d maps/bad/wall_hole_east.cub
echo -e ""

echo -e "${red}10. WALL HOLE IN NORTH (wall_hole_north.cub)${reset}"
check_error ./cub3d maps/bad/wall_hole_north.cub
echo -e ""

echo -e "${red}11. WALL HOLE IN SOUTH (wall_hole_south.cub)${reset}"
check_error ./cub3d maps/bad/wall_hole_south.cub
echo -e ""

echo -e "${red}12. WALL HOLE IN WEST (wall_hole_west.cub)${reset}"
check_error ./cub3d maps/bad/wall_hole_west.cub
echo -e ""

echo -e "${red}13. MISSING FLOOR (color_missing.cub)${reset}"
check_error ./cub3d maps/bad/color_missing.cub
echo -e ""

echo -e "${red}14. MAP IN THE FIRST LINE (map_first.cub)${reset}"
check_error ./cub3d maps/bad/map_first.cub
echo -e ""

echo -e "${red}15. TEXTURE DIRECTORY WITHOUT XPM (textures_dir.cub)${reset}"
check_error ./cub3d maps/bad/textures_dir.cub
echo -e ""

echo -e "${red}16. MISSING FLOOR COLOR (color_missing_floor_rgb.cub)${reset}"
check_error ./cub3d maps/bad/color_missing_floor_rgb.cub
echo -e ""

echo -e "${red}17. MAP IN THE MIDDLE line (map_middle.cub)${reset}"
check_error ./cub3d maps/bad/map_middle.cub
echo -e ""

echo -e "${red}18. SAME TEXTURE DIRECTION AND XPM (textures_duplicates.cub)${reset}"
check_error ./cub3d maps/bad/textures_duplicates.cub
echo -e ""

echo -e "${red}19. NO COLOR (color_none.cub)${reset}"
check_error ./cub3d maps/bad/color_none.cub
echo -e ""

echo -e "${red}20. MAP MISSING (map_missing.cub)${reset}"
check_error ./cub3d maps/bad/map_missing.cub
echo -e ""

echo -e "${red}21. NO EXIST XPM (textures_forbidden.cub)${reset}"
check_error ./cub3d maps/bad/textures_forbidden.cub
echo -e ""

echo -e "${red}22. EMPTY FILE (empty.cub)${reset}"
check_error ./cub3d maps/bad/empty.cub
echo -e ""

echo -e "${red}23. MAP ONLY (map_only.cub)${reset}"
check_error ./cub3d maps/bad/map_only.cub
echo -e ""

echo -e "${red}24. INVALID TEXTURE (textures_invalid.cub)${reset}"
check_error ./cub3d maps/bad/textures_invalid.cub
echo -e ""

echo -e "${red}25. MISSING WALL (wall_none.cub)${reset}"
check_error ./cub3d maps/bad/wall_none.cub
echo -e ""

echo -e "${red}26. EXTRA WORD (file_letter_end.cub)${reset}"
check_error ./cub3d maps/bad/file_letter_end.cub
echo -e ""

echo -e "${red}27. MAP TOO SMALL (map_too_small.cub)${reset}"
check_error ./cub3d maps/bad/map_too_small.cub
echo -e ""

echo -e "${red}28. MISSING ANOTHER TEXTURE (textures_missing.cub)${reset}"
check_error ./cub3d maps/bad/textures_missing.cub
echo -e ""

echo -e "${red}29. EXTRA PLAYER (player_multiple.cub)${reset}"
check_error ./cub3d maps/bad/player_multiple.cub
echo -e ""

echo -e "${red}30. NO TEXTURE (textures_none.cub)${reset}"
check_error ./cub3d maps/bad/textures_none.cub
echo -e ""

