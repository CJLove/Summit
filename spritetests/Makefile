.PHONY: all clean

all: skierLeft1.inc skierLeft2.inc skierDown.inc skierRight1.inc skierRight2.inc skierCrash.inc skier.prg

clean:
	rm -f *.inc sprites.prg

skier.prg:	main.c
	cl65 -t cx16 -O -o $@ $<

skierLeft1.inc: ../res/skierLeft1.png
	python3 ../tools/png2sprite.py -n skierLeft1 ../res/skierLeft1.png skierLeft1.inc
skierLeft2.inc: ../res/skierLeft2.png
	python3 ../tools/png2sprite.py -n skierLeft2 ../res/skierLeft2.png skierLeft2.inc
skierDown.inc: ../res/skierDown.png
	python3 ../tools/png2sprite.py -n skierDown ../res/skierDown.png skierDown.inc
skierRight1.inc: ../res/skierRight1.png
	python3 ../tools/png2sprite.py -n skierRight1 ../res/skierRight1.png skierRight1.inc
skierRight2.inc: ../res/skierRight2.png
	python3 ../tools/png2sprite.py -n skierRight2 ../res/skierRight2.png skierRight2.inc
skierCrash.inc: ../res/skierCrash.png
	python3 ../tools/png2sprite.py -n skierCrash ../res/skierCrash.png skierCrash.inc
