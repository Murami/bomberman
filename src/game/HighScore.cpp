#include "game/HighScore.hh"
#include "serializer/ISerializedNode.hh"
#include "serializer/JSONSerializer.hh"
#include "serializer/Serializer.hh"
#include "serializer/SerializerException.hh"

HighScore::HighScore()
{

}

HighScore::~HighScore()
{

}

void			HighScore::load(const std::string& file)
{
  Serializer s = Serializer::create<JSONSerializer>();

  try
    {
      s->deserializeFromFile("data/" + file, *this);
    }
  catch (SerializerException& ex)
    {
      throw SerializerException("Deserializer HighScore Error : " + std::string(ex.what()));
    }
}

void			HighScore::save(const std::string& file)
{
  Serializer s = Serializer::create<JSONSerializer>();

  try
    {
      s->serializeToFile("data/" + file, *this);
    }
  catch (SerializerException& ex)
    {
      throw SerializerException("Serializer HighScore Error : " + std::string(ex.what()));
    }
}

void			HighScore::pack(ISerializedNode & current) const
{
  current.add("scores", _scores);
}

void			HighScore::unpack(const ISerializedNode & current)
{
  current.get("scores", _scores);
}

const std::vector<int>&	HighScore::getScores()
{
  return (_scores);
}

void			HighScore::addScore(int score)
{
  std::vector<int>::iterator it;
  std::vector<int>::iterator itSave;

  _scores.push_back(score);
  for (itSave = _scores.begin(), it = _scores.begin(); it != _scores.end(); it++)
    {
      if ((*it) <= (*itSave))
	itSave = it;
    }
  if (_scores.size() > 5)
    _scores.erase(itSave);
}
