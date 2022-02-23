all: map_age_guide

run: map_age_guide
	./map_age_guide

map_age_guide: map_age_guide.c
	gcc -o map_age_guide map_age_guide.c -lncurses
