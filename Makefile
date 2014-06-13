VERSION = 0.0.1

ifeq ($(OS),Windows_NT)
CXX = cl /c
LINK = link
CFLAGS = /O2 /Og /Ot /EHsc
EXT = .exe
OBJEXT = .obj
else
CXX = g++ -c
LINK = g++ -lstdc++
CFLAGS = -O3
EXT = 
OBJEXT = .o
endif

OBJS = CmdLine${OBJEXT} Dumper${OBJEXT} Main${OBJEXT} Parser${OBJEXT}

DESTDIR = vsrd-${VERSION}
DIST = ${DESTDIR}.tar.gz
PROGRAM = vsrd${EXT}

%.o : %.cpp
	$(CXX) $(CFLAGS) $?

${PROGRAM}: $(OBJS)
	$(LINK) $(OBJS) -o $@

all: ${PROGRAM}

install: ${PROGRAM}
	install -D -m755 ${PROGRAM} ${DESTDIR}/vsrd

dist: install
	tar czf ${DIST} ${DESTDIR}

clean:
	rm *.o
	rm vsrd

distclean: clean
	rm ${DIST}
	rm -rf ${DESTDIR}

.PHONY: all clean distclean install dist
