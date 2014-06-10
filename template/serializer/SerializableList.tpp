template<typename ValueType>
SerializableList<ValueType>::SerializableList()
{

}

template<typename ValueType>
SerializableList<ValueType>::~SerializableList()
{

}

template<typename ValueType>
void	SerializableList<ValueType>::pack(ISerializedNode & current) const
{
  typename std::list<ValueType>::const_iterator	it;
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
void	SerializableList<ValueType>::unpack(const ISerializedNode & current)
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
