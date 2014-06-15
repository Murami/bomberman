//
// SoundManager.hh for bomberman in /home/bichon_b/rendu/cpp_bomberman
//
// Made by bichon_b
// Login   <bichon_b@epitech.net>
//
// Started on  Sun Jun 15 08:26:40 2014 bichon_b
// Last update Sun Jun 15 08:26:40 2014 bichon_b
//

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
    void	playSound(std::string const& name);
    void	playMusic(std::string const& name);

    // enable and disable sounds or musics
    void	enableSounds();
    void	disableSounds();
    void	enableMusics();
    void	disableMusics();

    // baisse le volume compris entre 0 et 100
    void	volume(std::string const& name, int volume);
    // baisse le volume général (de tous les sons)
    void	volume(int volume);
    void	pause(std::string const& name);
    void	stop(std::string const& name);
    void	del(std::string const& name);

    static SoundManager*	getInstance();
    static void			deleteInstance();

    bool			musicPlaying() const;
    bool			soundPlaying() const;

  private:
    static SoundManager*			_instance;
    std::map<std::string, FMOD_SOUND*>		_sounds;
    std::map<std::string, FMOD_SOUND*>		_musics;
    std::map<std::string, FMOD_CHANNEL*>	_channels;
    FMOD_SYSTEM*				_system;
    bool					_music;
    bool					_sound;
  };
};

#endif /* _SOUNDMANAGER_HH_ */
