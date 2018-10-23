#include <evaluator.hpp>

ObjectPtr Evaluator::BuiltinAppend(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() == 2)
  {
    if (arguments[0]->type == ObjectType::STRING && arguments[1]->type == ObjectType::STRING)
    {
      StringObjectPtr result;
      StringObjectPtr first = std::dynamic_pointer_cast<StringObject>(arguments[0]);
      StringObjectPtr second = std::dynamic_pointer_cast<StringObject>(arguments[1]);
      return std::make_shared<StringObject>(first->Value() + second->Value());
    }
    else if (arguments[0]->type == ObjectType::STRING && arguments[1]->type == ObjectType::CHARACTER)
    {
      StringObjectPtr result;
      StringObjectPtr first = std::dynamic_pointer_cast<StringObject>(arguments[0]);
      CharacterObjectPtr second = std::dynamic_pointer_cast<CharacterObject>(arguments[1]);
      return std::make_shared<StringObject>(first->Value() + second->Value());
    }
    else if (arguments[0]->type == ObjectType::ARRAY)
    {
      ArrayObjectPtr array_object = std::dynamic_pointer_cast<ArrayObject>(arguments[0]);
      ArrayObject array_copy = ArrayObject(*(array_object.get()));
      array_copy.elements.push_back(arguments[1]);
      return std::make_shared<ArrayObject>(array_copy);
    }
    else if (arguments[0]->type == ObjectType::SET)
    {
      SetObjectPtr set_object = std::dynamic_pointer_cast<SetObject>(arguments[0]);
      SetObject set_copy = SetObject(*(set_object.get()));
      set_copy.IterableAppend(arguments[1]);
      return std::make_shared<SetObject>(set_copy);
    }
  }
  return std::make_shared<NullObject>();
}