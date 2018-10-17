#include <evaluator.hpp>

ObjectPtr Evaluator::len(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() == 1)
  {
    if (arguments[0]->type == ObjectType::STRING)
    {
      StringObjectPtr string_object = std::dynamic_pointer_cast<StringObject>(arguments[0]);
      return std::make_shared<IntegerObject>(static_cast<int>(string_object->value.length()));
    }
  }
  return std::make_shared<NullObject>();
}