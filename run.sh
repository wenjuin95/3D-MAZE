#!/bin/bash

clear

echo -e "  _______  __   __  _______  _______  ______  "
echo -e " |       ||  | |  ||  _    ||       ||      | "
echo -e " |       ||  | |  || |_|   ||___    ||  _    |"
echo -e " |       ||  |_|  ||       | ___|   || | |   |"
echo -e " |      _||       ||  _   | |___    || |_|   |"
echo -e " |     |_ |       || |_|   | ___|   ||       |"
echo -e " |_______||_______||_______||_______||______| "
echo -e "                                              "

echo "+----------------Control------------------+"
echo "| W: Move forward         <-: turn left   |"
echo "| A: Move left            ->: turn right  |"
echo "| S: Move backward        ESC: Exit       |"
echo "| D: Move right           M: Show minimap |"
echo "+-----------------------------------------+"
echo ""
echo "+---------------CHOOSE MAP----------------+"
echo "| 1. black_map.cub                        |"
echo "| 2. map1.cub                             |"
echo "| 3. map2.cub                             |"
echo "| 4. dungeon.cub                          |"
echo "|                                         |"
echo "| 0. exit                                 |"
echo "+-----------------------------------------+"
echo -n "choose map: "

# Read a single character
read nb

# Check if the input is a number
if [[ $nb =~ ^[0-9]+$ ]]; then
    if [ $nb -eq 1 ]; then
        ./cub3d maps/black_map.cub
    elif [ $nb -eq 2 ]; then
        ./cub3d maps/map1.cub
    elif [ $nb -eq 3 ]; then
        ./cub3d maps/map2.cub
	elif [ $nb -eq 4 ]; then
		./cub3d maps/dungeon.cub
	elif [ $nb -eq 0 ]; then
		echo "GOODBYE"
		exit 0
    else
        echo "Invalid choice"
    fi
else
    echo "Invalid choice"
fi
