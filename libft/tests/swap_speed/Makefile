
all:
	gcc -Wall -Wextra -Werror test_swap_speed.c -DUSE_GENERIC_SWAP -I ../../includes/ -L .  -lft -o normal_swap
	gcc -Wall -Wextra -Werror test_swap_speed.c -I ../../includes/ -L .  -lft -o int_swap
	sh ./speedtest.sh

optimized: all
	gcc -O3 -Wall -Wextra -Werror test_swap_speed.c -DUSE_GENERIC_SWAP -I ../../includes/ -L .  -lft -o normal_swap
	gcc -O3 -Wall -Wextra -Werror test_swap_speed.c -I ../../includes/ -L .  -lft -o int_swap
	sh ./speedtest.sh
