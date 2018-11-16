#include <evaluator.hpp>

namespace walnut
{

ObjectPtr Evaluator::BuiltinExtend(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() == 2)
  {
    if (arguments[0]->type == ObjectType::ARRAY && arguments[1]->type == ObjectType::ARRAY)
    {
      ArrayObjectPtr first = std::dynamic_pointer_cast<ArrayObject>(arguments[0]);
      ArrayObjectPtr second = std::dynamic_pointer_cast<ArrayObject>(arguments[1]);
      for (auto &element : second->elements)
        first->elements.push_back(element);
      return first;
    }
    else if (arguments[0]->type == ObjectType::SET && arguments[1]->type == ObjectType::SET)
    {
      SetObjectPtr first = std::dynamic_pointer_cast<SetObject>(arguments[0]);
      SetObjectPtr second = std::dynamic_pointer_cast<SetObject>(arguments[1]);
      for (auto &element : second->elements)
        first->elements.push_back(element);
      return first;
    }
    return arguments[0];
  }
  return std::make_shared<NullObject>();
}

} // namespace walnut