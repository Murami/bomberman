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
