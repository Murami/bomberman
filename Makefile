##
## Makefile for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
## 
## Made by otoshigami
## Login   <otoshigami@epitech.net>
## 
## Started on  Sun Jun 15 08:48:53 2014 otoshigami
## Last update Sun Jun 15 13:58:48 2014 Manu
##

## FILES

NAME		=	bomberman

SRC		=	main				\
			events/Input			\
			events/Joystick			\
			events/InputConfig		\
			graphic/ARenderer		\
			graphic/Camera			\
			graphic/Object			\
			graphic/IDrawable		\
			graphic/ProjectionOrtho2D	\
			graphic/ProjectionPerspective	\
			graphic/Model			\
			graphic/RenderState		\
			graphic/Screen			\
			graphic/ShaderManager		\
			graphic/ModelManager		\
			graphic/TextureManager		\
			graphic/Transform		\
			graphic/Transformable		\
			graphic/Utils			\
			game/GameManager		\
			game/GameState			\
			game/GameOverState		\
			game/Game			\
			game/Tile			\
			game/TileManager		\
			game/TileMap			\
			game/Timer			\
			game/FrameManager		\
			game/Wall			\
			game/GameLoadingState		\
			game/APlayer			\
			game/AI				\
			game/HighScore			\
			entity/BonusFactory		\
			entity/EntityFactory		\
			entity/BombFactory		\
			entity/AEntity			\
			entity/ABomb			\
			entity/ABombExplode		\
			entity/GameBox			\
			entity/Marvin			\
			entity/MultiBomb		\
			entity/FireBomb			\
			entity/FireBombExplode		\
			entity/DarkBomb			\
			entity/DarkBombExplode		\
			entity/PowerBomb		\
			entity/PowerBombExplode		\
			entity/WaterBomb		\
			entity/WaterBombExplode		\
			entity/BoxBomb			\
			entity/BombBonus		\
			entity/FireBonus		\
			entity/SpeedBonus		\
			entity/RandomBonus		\
			entity/MultiBombBonus		\
			entity/PowerBonus		\
			entity/WaterBonus		\
			entity/DarkBonus		\
			entity/BoxBonus			\
			entity/Player			\
			serializer/JsonNode		\
			serializer/JSONSerializer	\
			serializer/Serializer		\
			serializer/SerializerException	\
			menu/AObject			\
			menu/Button			\
			menu/Letter			\
			menu/Menu			\
			menu/ResourceManager		\
			menu/Selector			\
			menu/Skybox			\
			menu/ToggleButton		\
			menu/MenuState			\
			menu/FileExplorer		\
			menu/Frame			\
			menu/AButton			\
			menu/StateButton		\
			menu/Image			\
			menu/FileLoadingException	\
			menu/PauseState			\
			menu/OpendirException		\
			menu/IntroState			\
			menu/IntroMarvin		\
			sound/SoundManager		\
			lua/LuaBiche			\
			hud/HUD				\

SRC_EXT		=	.cpp

## DIRECTORIES

DOBJ		=	obj
DSRC		=	src
DBIN		=	.

## COMPILATION

DINC		=	include		\
			template	\
			gdl/includes	\
			jsoncpp/include	\
			include/menu	\
			lua/include	\
			hud/

CFLAGS		=	-Wall		\
			-Wextra

MAKED		=	make --no-print-directory -C

## LINKAGE

LIB		=	gdl_gl		\
			GLEW		\
			GL		\
			fbxsdk		\
			SDL2		\
			pthread		\
			dl		\
			rt		\
			json		\
			lua

DLIB		=	gdl/libs	\
			jsoncpp/libs	\
			lua/libs

LDFLAGS		=	src/sound/libfmodex64-4.44.31.so

## RUNS

CC		=	g++
RM		=	rm -rf
MD		=	mkdir -p

####################
## INTERNAL RULES ##
####################

## CONSTANTS

DBGBOOL		=	yes

PROFILE		=	no

DBG		=	-g3		\
			-ggdb

WERROR		=	-Werror

## FILES

OBJ		=	$(addsuffix .o, $(SRC))
_SRC		=	$(addsuffix $(SRC_EXT), $(SRC))

## DIRECTORIES

DINC		:=	$(addsuffix /, $(DINC))
DOBJ		:=	$(addsuffix /, $(DOBJ))
DSRC		:=	$(addsuffix /, $(DSRC))
DBIN		:=	$(addsuffix /, $(DBIN))

## COMPILATION ARGS

CINC		=	$(addprefix -I, $(DINC))

COBJ		=	$(addprefix $(DOBJ), $(OBJ))
CSRC		=	$(addprefix $(DSRC), $(_SRC))
CNAME		=	$(addprefix $(DBIN), $(NAME))

## LINKAGE ARGS

LIB		:=	$(addprefix -l, $(LIB))
DLIB		:=	$(addsuffix /, $(DLIB))
DLIB		:=	$(addprefix -L, $(DLIB))

## FLAGS

ifeq ($(DBGBOOL), yes)
	CFLAGS  += $(DBG)
endif

ifeq ($(DBGBOOL), no)
	CFLAGS	+= $(WERROR)
endif

ifeq ($(PROFILE), yes)
	CFLAGS	+= -pg
	LDFLAGS += -pg
endif

CFLAGS		+=	$(CINC)
LDFLAGS		+=	$(DLIB)				\
			$(LIB)				\
			-Wl,-rpath=./gdl/libs:./lua/libs

## MISC RULES

MAKEOBJ		= $(addprefix $(DOBJ), %.o) : $(addprefix $(addprefix $(DSRC), %), $(SRC_EXT))

all:	$(CNAME)

dbg:	$(CNAME)

$(CNAME):	$(COBJ)
		@$(MD) $(DBIN)
		@echo
		@echo "[jsoncpp]"
		@$(MAKED) jsoncpp
		@echo "[lua]"
		@$(MAKED) lua/lua-5.2.3 linux
		@cp lua/lua-5.2.3/src/liblua.a lua/libs
		@echo
		@echo "Linkage : $(CNAME)"
		@$(CC) $(COBJ) -o $(CNAME) $(LDFLAGS)

$(COBJ):	$(MAKEOBJ)
		@$(MD) $(DOBJ)
		@for dir in `cd $(DSRC); ls -d */ 2> /dev/null`; \
		do \
		if [ ! -d "$(DOBJ)$$dir" ];then \
			$(MD) $(DOBJ)$$dir; \
		fi \
		done
		@echo "Compilation : $<"
		@$(CC) -c $< -o $@ $(CFLAGS)

clean:
		@$(MAKED) jsoncpp clean
		@$(RM) $(COBJ)
		@$(RM) lua/lua-5.2.3/src/*.o

fclean:		clean
		@$(MAKED) jsoncpp fclean
		@$(RM) $(CNAME)
		@$(RM) lua/lua-5.2.3/src/*.a
		@$(RM) lua/lua-5.2.3/src/luac
		@$(RM) lua/lua-5.2.3/src/lua

re:		fclean all
redbg:		fclean dbg

.PHONY:		fclean clean all dbg re
