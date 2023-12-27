# -*- makefile-gmake -*-
#
# THIS IS A GENERATED FILE - changes will not be kept if configure is
# run again.  If you wish to customise it, please be sure to give your
# version a different filename.
#
# Makefile for ONScripter-EN

WIN32=
OBJSUFFIX=.o
LIBSUFFIX=.a
EXESUFFIX=

PREFIX ?= /usr/local

# Extra handling for internal libraries.
EXTRADEPS= $(internal_sdl) $(internal_sdl_image) $(internal_sdl_mixer) $(internal_smpeg) $(internal_sdl_ttf)
INTERNAL_SDL=$(findstring true,true)
INTERNAL_SMPEG=$(findstring true,true)
INTERNAL_LIBPNG=$(findstring true,false)
INTERNAL_LIBJPEG=$(findstring true,false)
INTERNAL_OGGLIBS=$(findstring true,false)
SDL_CONFIG=./extlib/bin/sdl2-config

export PATH     :=   $(shell pwd)/extlib/bin:$(PATH)
export CFLAGS   := -I$(shell pwd)/extlib/include $(CFLAGS) 
export CPPFLAGS := -I$(shell pwd)/extlib/include $(CPPFLAGS) 
export LDFLAGS  := -L$(shell pwd)/extlib/lib $(LDFLAGS) 
export CSTD     := -std=c99
export CXXSTD   := -std=c++98

export CC      := gcc
export CXX     := g++
export MAKE    := make
export GNUMAKE := make
export AR      := ar
export RANLIB  := ranlib

# ONScripter variables
OSCFLAGSEXTRA = -Wall  -DUSE_X86_GFX $(OSCTMPFLAGS)
INCS = -Iextlib/include $(shell $(SDL_CONFIG) --cflags)      \
                        $(shell ./extlib/bin/smpeg2-config --cflags)    \
                        $(shell pkg-config freetype2 --cflags) \
       $(shell [ -d extlib/include/SDL ] && echo -Iextlib/include/SDL)

TOOL_LIBS = -Lextlib/lib \
            -ljpeg -lpng -lz \
            -lbz2
LIBS = -Lextlib/lib \
       extlib/lib/libSDL2_image$(LIBSUFFIX) $(if $(findstring true,true),-ljpeg -lpng -lz) \
       extlib/lib/libSDL2_mixer$(LIBSUFFIX) $(if $(or $(findstring true,true),$(findstring true,false)),-lvorbisfile -lvorbis -logg) \
       $(shell $(SDL_CONFIG) --libs)      \
       $(shell ./extlib/bin/smpeg2-config --libs)    \
       extlib/lib/libSDL2_ttf$(LIBSUFFIX) $(shell pkg-config freetype2 --libs) \
       -lbz2 $(if $(findstring true,true),-ldl -lasound -lX11 -lXext -lXrandr -pthread -lpulse-simple -lpulse)

DEFS = -DLINUX -DUSE_OGG_VORBIS 
EXT_OBJS = graphics_mmx.o graphics_sse2.o

SDL_MIXER_FLAGS = --enable-music-native-midi-gpl

.SUFFIXES:
.SUFFIXES: .o .cpp .h .c

ifdef DEBUG
OSCFLAGS = -O0 -g -pg -ggdb -pipe -Wpointer-arith   $(OSCFLAGSEXTRA)
export LDFLAGS  := -pg $(LDFLAGS)
else
  ifdef PROF
  OSCFLAGS = -O2 -pg -pipe -Wpointer-arith   $(OSCFLAGSEXTRA)
  export LDFLAGS  := -pg $(LDFLAGS)
  else
  OSCFLAGS = -O2 -fomit-frame-pointer -pipe -Wpointer-arith   $(OSCFLAGSEXTRA)
  endif
endif

TARGET ?= onscripter-en

binary: $(TARGET)

.PHONY: all clean distclean tools binary
all: $(TARGET) tools

SDLOTHERCONFIG := --disable-rpath
OTHERCONFIG := 

OTHER_OBJS =
RC_HDRS =

ICONFILE ?= ons-en.png
RESOURCES ?= $(ICONFILE) =icon.png
OTHER_OBJS = resources$(OBJSUFFIX) Linux_messagebox$(OBJSUFFIX)
RC_HDRS = resources.h
RCCLEAN = resources.cpp embed $(OTHER_OBJS)

resources$(OBJSUFFIX): $(RC_HDRS)

resources.cpp: embed $(filter-out =%,$(RESOURCES))
	./embed $(patsubst =%,%,$(RESOURCES)) > $@

embed: embed.cpp
	$(CXX) $(CXXSTD) $< -o $@

include Makefile.extlibs
include Makefile.onscripter

.PHONY: libtoolreplace
libtoolreplace:
	@cp $(ES)/required/freetype-config $(EB)

clean: pclean $(CLEAN_TARGETS) libtoolreplace
distclean: clean pdistclean $(DISTCLEAN_TARGETS)
	rm -r -f extlib/bin extlib/lib extlib/include \
	         extlib/share extlib/man
	rm -f Makefile 

install-bin:
	./install-sh -c -s $(TARGET) $(PREFIX)/bin/$(TARGET)
install: install-bin
uninstall:
	rm $(PREFIX)/bin/$(TARGET)

graphics_sse2.o: graphics_sse2.cpp graphics_sse2.h graphics_common.h graphics_sum.h graphics_blend.h
	$(CXX) $(CXXSTD) $(OSCFLAGS) $(INCS) $(DEFS) -msse2 -DUSE_X86_GFX -c $< -o $@

graphics_mmx.o: graphics_mmx.cpp graphics_mmx.h graphics_common.h graphics_sum.h
	$(CXX) $(CXXSTD) $(OSCFLAGS) $(INCS) $(DEFS) -mmmx -DUSE_X86_GFX -c $< -o $@

.PHONY: dist
dist:
	git archive --prefix=onscripter-en-20230628/ HEAD
	tar cf onscripter-en-20230628-fullsrc.tar onscripter-en-20230628
	rm -rf onscripter-en-20230628/extlib onscripter-en-20230628/win_dll \
			onscripter-en-20230628/tools/libgnurx
	tar cf onscripter-en-20230628-src.tar onscripter-en-20230628
	bzip2 -9 onscripter-en-20230628-*src.tar
	rm -rf onscripter-en-20230628
