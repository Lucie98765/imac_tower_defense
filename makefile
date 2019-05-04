CC			= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lSDL -lGLU -lGL -lm

BIN	= bin/
SRCDIR	= src/
OBJ	= obj/

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


image.o : src/image.c src/image.h
	@echo "compile image"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

lut.o : src/lut.c src/lut.h
	@echo "compile image"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

list_commands.o : src/list_commands.c src/list_commands.h
	@echo "compile image"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

effects.o : src/effects.c src/effects.h
	@echo "compile image"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

histo.o : src/histo.c src/histo.h
	@echo "compile image"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

main.o : src/main.c image.o lut.o list_commands.o effects.o
	@echo "compile main"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."




clean :
	rm -rf *~
	rm -rf $(SRCDIR)*/*~
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)*

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p `dirname $@`
	$(CC) -o $@ -c $< $(CFLAGS)

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