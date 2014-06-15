//
// SerializerException.hh for bomberman in /home/manu/rendu/cpp_bomberman/include/serializer
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jun 15 13:22:45 2014 Manu
// Last update Sun Jun 15 13:22:46 2014 Manu
//

#ifndef SERIALIZER_EXCEPTION_HH
# define SERIALIZER_EXCEPTION_HH

# include <exception>
# include <stdexcept>

class SerializerException : public std::runtime_error
{
public:
  explicit SerializerException(const std::string& what) throw();
};

#endif
