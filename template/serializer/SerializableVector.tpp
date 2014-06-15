//
// SerializableVector.tpp for bomberman  in /home/manu/rendu/cpp_bomberman/template/serializer
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jun 15 13:24:26 2014 Manu
// Last update Sun Jun 15 13:24:26 2014 Manu
//

template<typename ValueType>
SerializableVector<ValueType>::SerializableVector()
{

}

template<typename ValueType>
SerializableVector<ValueType>::~SerializableVector()
{

}

template<typename ValueType>
void		SerializableVector<ValueType>::pack(ISerializedNode & current) const
{
  typename std::vector<ValueType>::const_iterator	it;
  int							index;

  for (it = this->begin(); it != this->end(); ++it)
    {
      index = std::distance(this->begin(),
			    std::find(this->begin(), this->end(), *it));
      std::stringstream ss;
      ss << index;
      current.add(ss.str(), *it);
    }
}

template<typename ValueType>
void	SerializableVector<ValueType>::unpack(const ISerializedNode & current)
{
  int			size;
  ValueType		value;
  int			index;

  size = current.size();
  for (index = 0; index < size; index++)
    {
      std::stringstream ss;
      ss << index;
      current.get(ss.str(), value);
      this->push_back(value);
    }
}
