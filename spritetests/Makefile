.PHONY: all clean

all: skierLeft4.inc skierLeft3.inc skierLeft2.inc skierLeft1.inc skierDown.inc skierCrash.inc skierTree.inc skier.prg

clean:
	rm -f *.inc sprites.prg

skier.prg:	main.c
	cl65 -t cx16 -O -o $@ $<

skierLeft1.inc: ../res/skierLeft1.png
	python3 ../tools/png2sprite.py -n skierLeft1 ../res/skierLeft1.png skierLeft1.inc
skierLeft2.inc: ../res/skierLeft2.png
	python3 ../tools/png2sprite.py -n skierLeft2 ../res/skierLeft2.png skierLeft2.inc
skierLeft3.inc: ../res/skierLeft3.png
	python3 ../tools/png2sprite.py -n skierLeft3 ../res/skierLeft3.png skierLeft3.inc
skierLeft4.inc: ../res/skierLeft4.png
	python3 ../tools/png2sprite.py -n skierLeft4 ../res/skierLeft4.png skierLeft4.inc
skierDown.inc: ../res/skierDown.png
	python3 ../tools/png2sprite.py -n skierDown ../res/skierDown.png skierDown.inc
skierCrash.inc: ../res/skierCrash.png
	python3 ../tools/png2sprite.py -n skierCrash ../res/skierCrash.png skierCrash.inc
skierTree.inc: ../res/skierTree.png
	python3 ../tools/png2sprite.py -n skierTree ../res/skierTree.png skierTree.inc

