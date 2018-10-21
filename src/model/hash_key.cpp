#include <hash_key.hpp>

HashKey Hash(ObjectPtr object)
{
  if (object->type == ObjectType::BOOLEAN)
  {
    BooleanObjectPtr boolean = std::dynamic_pointer_cast<BooleanObject>(object);
    return HashKey(ObjectType::BOOLEAN, std::hash<bool>()(boolean->value));
  }
  else if (object->type == ObjectType::INTEGER)
  {
    IntegerObjectPtr integer = std::dynamic_pointer_cast<IntegerObject>(object);
    return HashKey(ObjectType::INTEGER, std::hash<int>()(integer->value));
  }
  else if (object->type == ObjectType::DOUBLE)
  {
    DoubleObjectPtr double__ = std::dynamic_pointer_cast<DoubleObject>(object);
    return HashKey(ObjectType::DOUBLE, std::hash<double>()(double__->value));
  }
  else if (object->type == ObjectType::STRING)
  {
    StringObjectPtr string__ = std::dynamic_pointer_cast<StringObject>(object);
    return HashKey(ObjectType::STRING, std::hash<String>()(string__->Value()));
  }
  else
  {
    return HashKey(ObjectType::NULL_, 0);
  }
}