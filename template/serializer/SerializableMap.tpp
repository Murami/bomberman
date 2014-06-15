//
// SerializableMap.tpp for bomberman in /home/manu/rendu/cpp_bomberman/template/serializer
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jun 15 13:24:30 2014 Manu
// Last update Sun Jun 15 13:28:19 2014 otoshigami
//

template<typename FirstType, typename SecondType>
SerializablePair<FirstType, SecondType>::SerializablePair()
{

}

template<typename FirstType, typename SecondType>
SerializablePair<FirstType, SecondType>::~SerializablePair()
{

}

template<typename FirstType, typename SecondType>
SerializablePair<FirstType, SecondType>::SerializablePair(const std::pair<FirstType, SecondType> pair)
{
  *this = pair;
}

template<typename FirstType, typename SecondType>
SerializablePair<FirstType, SecondType>& SerializablePair<FirstType, SecondType>::operator=(const std::pair<FirstType, SecondType> pair)
{
  std::pair<FirstType, SecondType>::operator=(pair);
  return (*this);
}

template<typename FirstType, typename SecondType>
void	SerializablePair<FirstType, SecondType>::pack(ISerializedNode & current) const
{
  current.add("first", this->first);
  current.add("sedond", this->second);
}

template<typename FirstType, typename SecondType>
void	SerializablePair<FirstType, SecondType>::unpack(const ISerializedNode & current)
{
  current.get("first", this->first);
  current.get("second", this->second);
}

template<typename IndexType, typename ValueType>
SerializableMap<IndexType, ValueType>::SerializableMap()
{

}

template<typename IndexType, typename ValueType>
SerializableMap<IndexType, ValueType>::~SerializableMap()
{

}

template<typename IndexType, typename ValueType>
void	SerializableMap<IndexType, ValueType>::pack(ISerializedNode & current) const
{
  typename std::map<IndexType, ValueType>::const_iterator	it;
  SerializablePair<IndexType, ValueType>			pair;
  int								index;

  for (it = this->begin(); it != this->end(); ++it)
    {
      index = std::distance(this->begin(),
			    std::find(this->begin(), this->end(), *it));
      std::stringstream ss;
      ss << index;
      pair = *it;
      current.add(ss.str(), pair);
    }
}

template<typename IndexType, typename ValueType>
void	SerializableMap<IndexType, ValueType>::unpack(const ISerializedNode & current)
{
  SerializablePair<IndexType, ValueType> tmp;
  int			size;
  int			index;

  size = current.size();
  for (index = 0; index < size; index++)
    {
      std::stringstream ss;
      ss << index;
      current.get(ss.str(), tmp);
      this->insert(tmp);
    }
}
