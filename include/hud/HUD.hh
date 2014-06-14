#ifndef		__HUD_HH__
# define	__HUD_HH__

# include	<iostream>
# include	<sstream>
# include	<map>
# include	<iostream>
# include	"game/APlayer.hh"

namespace	bbm
{
  class		ARenderer;
  class		RenderState;
  class		Image;
  class		Transform;
  class		Camera;
  class		Letter;

  class		HUD
  {
  private :
    BombType			_bonus;
    int				_nbBombs;
    int				_score;
    bool			_darkMalus;
    bool			_slowMalus;
    Image*			_normalBomb;
    std::map<BombType, Image*>	_bonusBombs;
    Image*			_background;

  public :
    const static std::string	NORMAL_BOMB_PATH;
    const static std::string	WATER_BOMB_PATH;
    const static std::string	DARK_BOMB_PATH;
    const static std::string	POWER_BOMB_PATH;
    const static std::string	MULTI_BOMB_PATH;
    const static std::string	BOX_BOMB_PATH;
    const static std::string	BACKGROUND_PATH;
    const static std::string	RANDOM_BOMB_PATH;

  public :
    void			initialize();
    void			draw(ARenderer&, const RenderState&);
    void			update(APlayer*);

  public :
    BombType			getType() const;
    int				getNbBombs() const;
    int				getScore() const;
    bool			hasDarkMalus() const;
    bool			hasSlowMalus() const;

  public :
    void			setType(BombType);
    void			setNbBombs(int);
    void			setScore(int);
    void			setDark(bool);
    void			setSlow(bool);

  public :
    HUD();
    ~HUD();
  };
}

#endif
