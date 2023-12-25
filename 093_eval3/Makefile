CFLAGS= -Wall -Werror -std=gnu++98 -pedantic -ggdb3
PROGS=cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
OBJS=$(patsubst %,%.o,$(PROGS)) cyoa-step%.o

all: $(PROGS)

cyoa-step%: util.o page.o story.o choice.o cyoa-step%.o
	g++ -o $@ $^

%.o: %.cpp %.hpp
	g++ $(CFLAGS) -c $<

clean:
	rm -f *~ $(PROGS) $(OBJS)