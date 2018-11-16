#include <evaluator.hpp>

namespace walnut
{

ObjectPtr Evaluator::BuiltinAppend(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() == 2)
  {
    if (arguments[0]->type == ObjectType::STRING && arguments[1]->type == ObjectType::STRING)
    {
      StringObjectPtr result;
      StringObjectPtr first = std::dynamic_pointer_cast<StringObject>(arguments[0]);
      StringObjectPtr second = std::dynamic_pointer_cast<StringObject>(arguments[1]);
      first->buffer.insert(first->buffer.end(), second->buffer.begin(), second->buffer.end());
      return first;
    }
    else if (arguments[0]->type == ObjectType::STRING && arguments[1]->type == ObjectType::CHARACTER)
    {
      StringObjectPtr result;
      StringObjectPtr first = std::dynamic_pointer_cast<StringObject>(arguments[0]);
      CharacterObjectPtr second = std::dynamic_pointer_cast<CharacterObject>(arguments[1]);
      first->buffer.push_back(second);
      return first;
    }
    else if (arguments[0]->type == ObjectType::ARRAY)
    {
      ArrayObjectPtr array_object = std::dynamic_pointer_cast<ArrayObject>(arguments[0]);
      array_object->IterableAppend(arguments[1]);
      return array_object;
    }
    else if (arguments[0]->type == ObjectType::SET)
    {
      SetObjectPtr set_object = std::dynamic_pointer_cast<SetObject>(arguments[0]);
      set_object->IterableAppend(arguments[1]);
      return set_object;
    }
    else if (arguments[0]->type == ObjectType::ENUMERATE)
    {
      EnumerateObjectPtr enumerate_object = std::dynamic_pointer_cast<EnumerateObject>(arguments[0]);
      enumerate_object->IterableAppend(arguments[1]);
      return enumerate_object;
    }
  }
  return std::make_shared<NullObject>();
}

} // namespace walnut