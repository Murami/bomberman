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
			sound/SoundManager		\
			lua/LuaBiche

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
			include/menu

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
			jsoncpp/libs

LDFLAGS		=	src/sound/libfmodex64-4.44.31.so

## RUNS

CC		=	g++ -fmax-errors=5
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
LDFLAGS		+=	$(DLIB)			\
			$(LIB)			\
			-Wl,-rpath=./gdl/libs

## MISC RULES

MAKEOBJ		= $(addprefix $(DOBJ), %.o) : $(addprefix $(addprefix $(DSRC), %), $(SRC_EXT))

all:	$(CNAME)

dbg:	$(CNAME)

$(CNAME):	$(COBJ)
		@$(MD) $(DBIN)
		@echo
		@echo "[jsoncpp]"
		@$(MAKED) jsoncpp
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

fclean:		clean
		@$(MAKED) jsoncpp clean
		@$(RM) $(CNAME)

re:		fclean all
redbg:		fclean dbg

.PHONY:		fclean clean all dbg re
