//
// Serializer.tpp for bomberman in /home/manu/rendu/cpp_bomberman/template/serializer
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jun 15 13:24:22 2014 Manu
// Last update Sun Jun 15 13:24:23 2014 Manu
//

template<typename T>
Serializer Serializer::create()
{
  return (Serializer(new T));
}
