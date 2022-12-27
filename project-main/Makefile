EXE = Sokoban

SRCS = play.cpp file_loader.cpp main.cpp file_loader_2P.cpp play_2P.cpp show.cpp sokoban.cpp

HEAD = sokoban.h

OUTO = *.o

all: $(EXE)

$(EXE): $(HEAD)
	@g++ $(SRCS) -lSDL -lSDL_image -o $(EXE)
	@echo "./Anya's Sokoban is created!"

clean:
	@/bin/rm -f $(OUTO)

fclean: clean
	@/bin/rm -f $(EXE)

re: fclean all
