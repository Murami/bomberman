//
// SoundManager.cpp for bomberman in /home/bichon_b/rendu/cpp_bomberman
//
// Made by bichon_b
// Login   <bichon_b@epitech.net>
//
// Started on  Sun Jun 15 08:25:25 2014 bichon_b
// Last update Sun Jun 15 20:11:06 2014 bichon_b
//

#include "sound/SoundManager.hh"
#include <iostream>

namespace bbm
{
  SoundManager*	SoundManager::_instance = NULL;

  SoundManager::SoundManager()
  {
    FMOD_System_Create(&_system);
    FMOD_System_Init(_system, 512, FMOD_INIT_NORMAL, NULL);
  }

  bool	SoundManager::musicPlaying() const
  {
    return (this->_music);
  }

  bool	SoundManager::soundPlaying() const
  {
    return (this->_sound);
  }

  SoundManager::~SoundManager()
  {
    unsigned int	i;

    for (i = 0; i < _sounds.size(); i++)
      FMOD_Sound_Release(_sounds[0]);
    _sounds.clear();
    for (i = 0; i < _musics.size(); i++)
      FMOD_Sound_Release(_musics[0]);
    _musics.clear();
    _channels.clear();
    FMOD_System_Close(_system);
    FMOD_System_Release(_system);
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
    _musics[name] = tmp;
  }

  void	SoundManager::playSound(std::string const& name)
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
    _sound = true;
  }

  void	SoundManager::playMusic(std::string const& name)
  {
    FMOD_BOOL	stat;

    FMOD_Channel_GetPaused(_channels[name], &stat);
    if (stat == 1)
      FMOD_Channel_SetPaused(_channels[name], 0);
    else
      {
	_channels[name] = NULL;
	if (FMOD_System_PlaySound(_system, FMOD_CHANNEL_FREE, _musics[name], false, &_channels[name]) != FMOD_OK)
	  {
	    std::cerr << "Error : can't play " << name << std::endl;
	    return ;
	  }
      }
    _music = true;
  }

  void	SoundManager::disableSounds()
  {
    std::map<std::string, FMOD_SOUND*>::iterator	it;

    for (it = _sounds.begin(); it != _sounds.end(); it++)
      this->stop(it->first);
    _sound = false;
  }

  void	SoundManager::enableSounds()
  {
    _sound = true;
  }

  void	SoundManager::disableMusics()
  {
    std::map<std::string, FMOD_SOUND*>::iterator	it;

    for (it = _musics.begin(); it != _musics.end(); it++)
      this->pause(it->first);
    _music = false;
  }

  void	SoundManager::enableMusics()
  {
    _music = true;
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
