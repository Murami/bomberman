
#ifndef _SOUNDMANAGER_HH_
# define _SOUNDMANAGER_HH_

# include <map>
# include <string>
# include "fmod.h"

namespace bbm
{
  class	SoundManager
  {
  private:
    SoundManager();
    ~SoundManager();

  public:
    // Load a sound or a music from a filename. If the name already exists, the new sounds erase the previous one
    void	addMusic(std::string const& name, std::string const& path);
    void	addSound(std::string const& name, std::string const& path);

    // play a sound, if the sound doesn't exists, do nothing
    void	play(std::string const& name);

    // baisse le volume compris entre 0 et 100
    void	volume(std::string const& name, int volume);
    // baisse le volume général (de tous les sons)
    void	volume(int volume);
    void	pause(std::string const& name);
    void	stop(std::string const& name);
    void	del(std::string const& name);

    static SoundManager*	getInstance();
    static void			deleteInstance();

    void			music(bool);
    void			sound(bool);

  private:
    static SoundManager*			_instance;
    std::map<std::string, FMOD_SOUND*>		_sounds;
    std::map<std::string, FMOD_CHANNEL*>	_channels;
    FMOD_SYSTEM*				_system;
    bool					_music;
    bool					_sound;
  };
};

#endif /* _SOUNDMANAGER_HH_ */
