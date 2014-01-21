# O/S Dependencies and Common Rules for Makefiles
#
OS     = $(shell uname)

ifneq (,$(findstring CYGWIN, $(OS)))

# CYGWIN
#
GLUT_DIR = /usr/src/freeglut-2.6.0
CC     = gcc
LD     = /bin/sh /usr/src/freeglut-2.6.0/libtool --tag=CC --mode=link gcc -all-static ${GLUT_DIR}/src/libglut.la
CFLAGS = -Wall -Werror -pedantic -O2 -g -DEMULATE_BUFFERS -I../common -I${GLUT_DIR}/include
LFLAGS = -g -lm -lstdc++ -lglu32
DRUN   = /bin/sh /usr/src/freeglut-2.6.0/libtool --mode=execute gdb --init-command=.gdbinit $(PROG)
COPY_BACKUP = cp nanocad.tar.gz  /cygdrive/z
#COPY_BACKUP = 

else
ifeq ($(OS), Darwin) 

# MAC OS X
#
CC     = gcc
LD     = gcc
CFLAGS = -Wall -Werror -pedantic -O2 -g -DEMULATE_BUFFERS -I../common
LFLAGS = -g -lm -lstdc++ -framework OpenGl -framework GLUT -framework CoreFoundation -framework IOKit -framework Carbon -framework CoreGraphics -framework Cocoa
DRUN   = gdb $(PROG)
COPY_BACKUP = 

else
ifeq ($(OS), Linux)

# LINUX
#
# TODO: 
#
COPY_BACKUP = 

else
$(error Unknown O/S: $(OS))
endif
endif
endif

all: $(OBJS) $(PROG) $(WRAPPER).pm

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

%.exe: %.o $(DEPS) $(OBJS)
	$(LD) $(OBJS) $(LIBS) $(LFLAGS) -o $@ 

$(WRAPPER).java : $(DEPS) $(WRAPPER).i
	swig -w401 -w451 -java -c++ -I../common $(WRAPPER).i 

$(WRAPPER).pm : $(DEPS) $(WRAPPER).i
	swig -w401 -w451 -perl -c++ -I../common $(WRAPPER).i

drun: $(PROG)
	$(DRUN)

run: all
	./$(PROG)

clean:
	rm -fr *.o *.exe .libs *.gz *.out ._* .libs $(PROG) *.stackdump *.mp4 *.java $(WRAPPER).pm *.cxx

backup: 
	cd ../common; make clean
	cd ../nv;   make clean
	cd ../phys; make clean
	cd ../..;\
	tar cvfz nanocad.tar.gz nanocad;\
        $(COPY_BACKUP)
