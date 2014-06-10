template<typename T>
Serializer Serializer::create()
{
  return (Serializer(new T));
}
