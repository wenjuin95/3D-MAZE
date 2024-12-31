#!/bin/bash

BLUE='\033[0;34m'
RESET='\033[0m'

echo ""
echo -e "${BLUE}-----CHECK PARSING-----${RESET}"
norminette parse/*.c
echo ""
echo -e "${BLUE}-----CHECK SRC-----${RESET}"
norminette src/*.c
echo ""
echo -e "${BLUE}-----CHECK INCLUDE-----${RESET}"
norminette include/*.h
echo ""
echo -e "${BLUE}-----CHECK LIBFT-----${RESET}"
norminette libft/*.c libft/*.h