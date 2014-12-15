EXE = builder
all: $(EXE)

#  MinGW
ifeq "$(OS)" "Windows_NT"
INCLUDE_PATHS = -IC:\MinGW\SDL2
LIBRARY_PATHS = -LC:\MinGW\lib 
CFLG = -O3 -m32 -Wall 
# -w
#Wno-deprecated-declarations 
LIBS=-lglut32cu -lglu32 -lopengl32 -lmingw32 -lWs2_32
# -lSDL2main -lSDL2 -lSDL2_image  -lm
CLEAN=del *.exe *.o *.a



else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall  -fno-builtin-exit -fno-builtin-strcat -fno-builtin-strncat -fno-builtin-strcpy -fno-builtin-strlen -fno-builtin-calloc
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

#Dependencies
builder.o: builder.cpp CSCIx229.h
fatal.o: fatal.c CSCIx229.h
loadtexbmp.o: loadtexbmp.c CSCIx229.h
print.o: print.c CSCIx229.h
project.o: project.cpp CSCIx229.h
errcheck.o: errcheck.c CSCIx229.h
#houseFigure.o: houseFigure.cpp myShapes.o CSCIx229.h
foliage.o: foliage.cpp myShapes.o CSCIx229.h
object.o: object.c CSCIx229.h
myShapes.o: myShapes.cpp CSCIx229.h


#  Create archive
CSCIx229.a:fatal.o loadtexbmp.o print.o project.o errcheck.o foliage.o myShapes.o object.o 
	ar -rcs $@ $^


.cpp.o:
	g++ -c $(CFLG) $<
.c.o:
	gcc -c $(CFLG) $<


#  Link
builder:builder.o CSCIx229.a
	g++ -O3 -Wall -o $@ $^ $(LIBS)
	

	
	
#  Clean
clean:

	$(CLEAN)
