CC			= g++
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lSDL -lGLU -lGL -lm

BIN	= bin/towerDefense.itd
SRC	= src/
OBJ	= main.o verifCarte.o

LIB    = -lm
RM     = rm -f
DIRNAME = $(shell basename $$PWD)
BACKUP  = $(shell date +`basename $$PWD`-%m.%d.%H.%M.zip)
STDNAME = $(DIRNAME).zip


all : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(BIN) $(LDFLAGS)
	@echo "--------------------------------------------------------------"
	@echo "            to execute type: $(BIN) &"
	@echo "--------------------------------------------------------------"




verifCarte.o : src/verifCarte.cpp include/verifCarte.hpp
	@echo "compile image"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

main.o : src/main.cpp verifCarte.o
	@echo "compile main"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."




clean :	
	@echo "**************************"
	@echo "CLEAN"
	@echo "**************************"
	$(RM) *~ $(OBJ) $(BIN)    

bigclean :
	@echo "**************************"
	@echo "BIG CLEAN"
	@echo "**************************"
	find . -name '*~' -exec rm -fv {} \;
	$(RM) *~ $(OBJ) $(BIN)

zip : clean 
	@echo "**************************"
	@echo "ZIP"
	@echo "**************************"
	cd .. && zip -r $(BACKUP) $(DIRNAME)
