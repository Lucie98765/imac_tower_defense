
CC     = g++
CFLAGS = -Wall -O2 -Wno-unused-result -g
LIB    = -lm
LDFLAGS	= -lSDL -lGLU -lGL -lm
SRCDIR		=	./src/
OBJDIR		=	./obj/
BIN	= ./bin/maint.out
OBJ    = ./obj/main.o ./obj/verifCarte.o ./obj/entity.o ./obj/monster.o ./obj/tower.o ./obj/batiment.o ./obj/timer.o
RM     = rm -f
DIRNAME = $(shell basename $$PWD)
BACKUP  = $(shell date +`basename $$PWD`-%m.%d.%H.%M.zip)
STDNAME = $(DIRNAME).zip

all : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(BIN) $(LDFLAGS)
	@echo "--------------------------------------------------------------"
	@echo "            to execute type: $(BIN) &"
	@echo "--------------------------------------------------------------"


$(OBJDIR)verifCarte.o : ./src/verifCarte.cpp ./include/verifCarte.hpp
	@echo "compile carte"
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)
	@echo "done..."

$(OBJDIR)entity.o : ./src/entity.cpp ./include/entity.h
	@echo "compile entity"
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)
	@echo "done..."

$(OBJDIR)monster.o : ./src/monster.cpp ./include/monster.h
	@echo "compile monster"
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)
	@echo "done..."

$(OBJDIR)tower.o : ./src/tower.cpp ./include/tower.h
	@echo "compile tower"
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)
	@echo "done..."

$(OBJDIR)batiment.o : ./src/batiment.cpp ./include/batiment.h
	@echo "compile batiment"
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)
	@echo "done..."

$(OBJDIR)timer.o : ./src/timer.cpp ./include/timer.h
	@echo "compile timer"
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)
	@echo "done..."


$(OBJDIR)main.o : ./src/main.cpp $(OBJDIR)verifCarte.o $(OBJDIR)entity.o $(OBJDIR)monster.o $(OBJDIR)tower.o $(OBJDIR)batiment.o $(OBJDIR)timer.o
	@echo "compile main"
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)
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
