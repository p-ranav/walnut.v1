#include <evaluator.hpp>

namespace walnut
{

ObjectPtr Evaluator::BuiltinType(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() == 1)
  {
    ObjectPtr argument = arguments[0];
    ObjectType argument_type = argument->type;
    switch (argument_type)
    {
    case ObjectType::INTEGER:
      return std::make_shared<StringObject>("int");
    case ObjectType::DOUBLE:
      return std::make_shared<StringObject>("double");
    case ObjectType::BOOLEAN:
      return std::make_shared<StringObject>("bool");
    case ObjectType::CHARACTER:
      return std::make_shared<StringObject>("char");
    case ObjectType::STRING:
      return std::make_shared<StringObject>("string");
    case ObjectType::NULL_:
      return std::make_shared<StringObject>("null");
    case ObjectType::RETURN:
      return std::make_shared<StringObject>("return");
    case ObjectType::FUNCTION:
      return std::make_shared<StringObject>("function");
    case ObjectType::BUILTIN_FUNCTION:
      return std::make_shared<StringObject>("builtin");
    case ObjectType::ARRAY:
      return std::make_shared<StringObject>("list");
    case ObjectType::RANGE:
      return std::make_shared<StringObject>("range");
    case ObjectType::HASH:
      return std::make_shared<StringObject>("dict");
    case ObjectType::SET:
      return std::make_shared<StringObject>("set");
    case ObjectType::TUPLE:
      return std::make_shared<StringObject>("tuple");
    case ObjectType::KEY_VALUE_ARGUMENT:
      return std::make_shared<StringObject>("pair");
    case ObjectType::ENUMERATE:
      return std::make_shared<StringObject>("enumerate");
    default:
      return std::make_shared<StringObject>("");
    }
  }
  return std::make_shared<StringObject>("");
}

} // namespace walnut