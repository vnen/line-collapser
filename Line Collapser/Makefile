CPPFLAGS?=-O2
LDFLAGS?=
LIBS?=

CPPFLAGS:=$(CPPFLAGS) -pedantic -Wall -Wextra -Werror
LDFLAGS:=$(LDFLAGS) -g
LIBS:=$(LIBS) -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer -lm -lc

SRCFILES:=$(shell find . -type f -name \*.cpp)
HDRFILES:=$(shell find . -type f -name \*.h)

OBJFILES:=$(patsubst %.cpp,%.o,$(SRCFILES))
DEPFILES:=$(patsubst %.cpp,%.d,$(SRCFILES))

.PHONY: all clean

all: linecollapser

clean:
	rm -f $(OBJFILES) $(DEPFILES) linecollapser

linecollapser: $(OBJFILES)
	@g++ $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	@g++ $(CPPFLAGS) -MD -MP -c $< -o $@

%.d:
	@touch $@

-include $(DEPFILES)
