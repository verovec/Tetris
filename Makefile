NAME 		= 	tetris
CC 			= 	g++
CPPFLAGS 	= 	-Wall -Werror -Wextra
SFMLLIBS	= 	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC			=	GameManager.cpp \
				Menu.cpp \
				Config.cpp \
				ResourceManager.cpp \
				ColorManager.cpp \
				BlockEntity.cpp \
				Board.cpp \
				TimeManager.cpp \
				EntityFactory.cpp \
				main.cpp

OBJS		= 	$(SRC:.cpp=.o)

all: 		$(NAME)

$(NAME): 	$(OBJS)
			$(CC) $(CPPFLAGS) -o $(NAME) $(OBJS) $(SFMLLIBS)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re