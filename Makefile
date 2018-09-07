cc=gcc
floorplanner : fp.c random.c sa.c ga.c
	$(cc) -g $+ -lm -o $@
