all: tp1_0 tp1_1 tp1_2 tp1_3 tp1_4 tp1_adsd

tp1_0: tp1_0.o smpl.o rand.o
	$(LINK.c) -o $@ -Bstatic tp1_0.o smpl.o rand.o -lm

tp1_1: tp1_1.o smpl.o rand.o
	$(LINK.c) -o $@ -Bstatic tp1_1.o smpl.o rand.o -lm

tp1_2: tp1_2.o smpl.o rand.o
	$(LINK.c) -o $@ -Bstatic tp1_2.o smpl.o rand.o -lm

tp1_3: tp1_3.o smpl.o rand.o
	$(LINK.c) -o $@ -Bstatic tp1_3.o smpl.o rand.o -lm

tp1_4: tp1_4.o smpl.o rand.o
	$(LINK.c) -o $@ -Bstatic tp1_4.o smpl.o rand.o -lm

tp1_adsd: tp1_adsd.o smpl.o rand.o
	$(LINK.c) -o $@ -Bstatic tp1_adsd.o smpl.o rand.o -lm
	
smpl.o: smpl.c smpl.h
	$(COMPILE.c)  -g smpl.c

tp1_0.o: tp1_0.c smpl.h
	$(COMPILE.c) -g  tp1_0.c

tp1_1.o: tp1_1.c smpl.h
	$(COMPILE.c) -g  tp1_1.c

tp1_2.o: tp1_2.c smpl.h
	$(COMPILE.c) -g  tp1_2.c

tp1_3.o: tp1_3.c smpl.h
	$(COMPILE.c) -g  tp1_3.c

tp1_4.o: tp1_4.c smpl.h
	$(COMPILE.c) -g  tp1_4.c

tp1_4.adsd: tp1_adsd.c smpl.h
	$(COMPILE.c) -g  tp1_adsd.c


rand.o: rand.c
	$(COMPILE.c) -g rand.c

clean:
	$(RM) *.o tp1_0 tp1_1 tp1_2 tp1_3 tp1_4

