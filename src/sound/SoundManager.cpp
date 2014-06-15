#include "sound/SoundManager.hh"
#include <iostream>

namespace bbm
{
  SoundManager*	SoundManager::_instance = NULL;

  SoundManager::SoundManager()
  {
    FMOD_System_Create(&_system);
    FMOD_System_Init(_system, 32, FMOD_INIT_NORMAL, NULL);
  }

  SoundManager::~SoundManager()
  {
    unsigned int	i;

    for (i = 0; i < _sounds.size(); i++)
      FMOD_Sound_Release(_sounds[0]);
    _sounds.clear();
    _channels.clear();
    FMOD_System_Close(_system);
    FMOD_System_Release(_system);
  }

  void	SoundManager::music(bool music)
  {
    this->_music = music;
  }

  void	SoundManager::sound(bool sound)
  {
    this->_sound = sound;
  }

  void	SoundManager::addSound(std::string const& name, std::string const& path)
  {
    FMOD_SOUND*	tmp;

    if (FMOD_System_CreateSound(_system, path.c_str(), FMOD_CREATESAMPLE, 0, &tmp) != FMOD_OK)
      {
	std::cerr << "Error with " << path << std::endl;
	return ;
      }
    _sounds.insert(std::pair<std::string, FMOD_SOUND*>(name, tmp));
  }

  void	SoundManager::addMusic(std::string const& name, std::string const& path)
  {
    FMOD_SOUND*		tmp;

    if (FMOD_System_CreateSound(_system, path.c_str(),
				FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL,
				0, &tmp) != FMOD_OK)
      {
	std::cerr << "Error with " << path << std::endl;
	return ;
      }
    FMOD_Sound_SetLoopCount(tmp, -1);
    _sounds[name] = tmp;
  }

  ////////////////////////////
  // faire la gestion des booleens pour jouer ou non la musique
  ////////////////////////////

  void	SoundManager::play(std::string const& name)
  {
    FMOD_BOOL	stat;

    FMOD_Channel_GetPaused(_channels[name], &stat);
    if (stat == 1)
      FMOD_Channel_SetPaused(_channels[name], 0);
    else
      {
	_channels[name] = NULL;
	if (FMOD_System_PlaySound(_system, FMOD_CHANNEL_FREE, _sounds[name], false, &_channels[name]) != FMOD_OK)
	  {
	    std::cerr << "Error : can't play " << name << std::endl;
	    return ;
	  }
      }
  }

  void	SoundManager::pause(std::string const& name)
  {
    FMOD_Channel_SetPaused(_channels[name], 1);
  }

  void	SoundManager::stop(std::string const& name)
  {
    FMOD_Channel_Stop(_channels[name]);
  }

  void	SoundManager::del(std::string const& name)
  {
    this->stop(name);
    FMOD_Sound_Release(_sounds[name]);
    _sounds.erase(_sounds.find(name));
    if (_channels[name])
      _channels.erase(_channels.find(name));
  }

  void	SoundManager::volume(std::string const& name, int volume)
  {
    FMOD_Channel_SetVolume(_channels[name], ((double)volume) / 100);
  }

  void	SoundManager::volume(int volume)
  {
    FMOD_CHANNELGROUP*	tmp;

    FMOD_System_GetMasterChannelGroup(_system, &tmp);
    FMOD_ChannelGroup_SetVolume(tmp, ((double)volume) / 100);
  }

  SoundManager*	SoundManager::getInstance()
  {
    if (_instance == NULL)
      _instance = new SoundManager;
    return (_instance);
  }

  void	SoundManager::deleteInstance()
  {
    if (_instance)
      {
	delete (_instance);
	_instance = NULL;
      }
  }

};
