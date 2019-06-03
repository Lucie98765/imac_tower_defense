
CC     = g++
CFLAGS = -Wall -O2 -Wno-unused-result -g
LIB    = -lm -lSDL_image
LDFLAGS	= -lSDL -lGLU -lGL -lm
SRCDIR		=	./src/
INCLDIR = ./include/
OBJDIR		=	./obj/
BIN	= ./bin/ImacTowerDefense
OBJ    = $(OBJDIR)main.o $(OBJDIR)node.o $(OBJDIR)map.o $(OBJDIR)entity.o $(OBJDIR)monster.o $(OBJDIR)tower.o $(OBJDIR)batiment.o $(OBJDIR)timer.o $(OBJDIR)money.o $(OBJDIR)texture.o
RM     = rm -f
DIRNAME = $(shell basename $$PWD)
BACKUP  = $(shell date +`basename $$PWD`-%m.%d.%H.%M.zip)
STDNAME = $(DIRNAME).zip

all : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(BIN) $(LDFLAGS)
	@echo "--------------------------------------------------------------"
	@echo "            to execute type: $(BIN) &"
	@echo "--------------------------------------------------------------"



$(OBJDIR)map.o : $(SRCDIR)map.cpp $(INCLDIR)map.h
	@echo "compile map"
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)
	@echo "done..."

$(OBJDIR)node.o : $(SRCDIR)node.cpp $(INCLDIR)node.h
	@echo "compile node"
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)
	@echo "done..."

$(OBJDIR)entity.o : $(SRCDIR)entity.cpp $(INCLDIR)entity.h
	@echo "compile entity"
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)
	@echo "done..."

$(OBJDIR)monster.o : $(SRCDIR)monster.cpp $(INCLDIR)monster.h
	@echo "compile monster"
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)
	@echo "done..."

$(OBJDIR)tower.o : $(SRCDIR)tower.cpp $(INCLDIR)tower.h
	@echo "compile tower"
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)
	@echo "done..."

$(OBJDIR)batiment.o : $(SRCDIR)batiment.cpp $(INCLDIR)batiment.h
	@echo "compile batiment"
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)
	@echo "done..."

$(OBJDIR)timer.o : $(SRCDIR)timer.cpp $(INCLDIR)timer.h
	@echo "compile timer"
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)
	@echo "done..."

$(OBJDIR)money.o : $(SRCDIR)money.cpp $(INCLDIR)money.h
	@echo "compile money"
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)
	@echo "done..."

$(OBJDIR)texture.o : $(SRCDIR)texture.cpp $(INCLDIR)texture.h
	@echo "compile texture"
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)
	@echo "done..."


$(OBJDIR)main.o : $(SRCDIR)main.cpp $(OBJDIR)map.o $(OBJDIR)node.o $(OBJDIR)entity.o $(OBJDIR)monster.o $(OBJDIR)tower.o $(OBJDIR)batiment.o $(OBJDIR)timer.o $(OBJDIR)money.o $(OBJDIR)texture.o
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
