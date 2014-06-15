//
// HighScore.hh for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
//
// Made by otoshigami
// Login   <otoshigami@epitech.net>
//
// Started on  Sun Jun 15 08:36:26 2014 otoshigami
// Last update Sun Jun 15 08:36:28 2014 otoshigami
//

#ifndef		HIGHSCORE_HH
# define	HIGHSCORE_HH

# include "serializer/ISerializable.hh"
# include "serializer/SerializableVector.hh"

class HighScore : public ISerializable
{
public:
  HighScore();
  ~HighScore();

  void				pack(ISerializedNode & current) const;
  void				unpack(const ISerializedNode & current);
  void				save(const std::string& file);
  void				load(const std::string& file);
  const std::vector<int>&	getScores();
  void				addScore(int score);

private:
  SerializableVector<int>	_scores;
};

#endif
