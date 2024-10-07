#!/bin/bash
clear
make re -C ft_printf
cc test_printf.c ft_printf/libftprintf.a -fsanitize=address -g
./a.out
