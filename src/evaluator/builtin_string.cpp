#include <strcpp.hpp>
#include <evaluator.hpp>

ObjectPtr Evaluator::BuiltinSplit(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() == 2)
  {
    if (arguments[0]->type == ObjectType::STRING && arguments[1]->type == ObjectType::STRING)
    {
      StringObjectPtr input_string = std::dynamic_pointer_cast<StringObject>(arguments[0]);
      StringObjectPtr split_string = std::dynamic_pointer_cast<StringObject>(arguments[1]);
      std::vector<std::string> split_result = split(input_string->Value(), split_string->Value());
      ArrayObjectPtr result = std::make_shared<ArrayObject>();
      for (auto& part : split_result)
      {
        result->elements.push_back(std::make_shared<StringObject>(part));
      }
      return result;
    }
    else
      return std::make_shared<NullObject>();
  }
  else
    return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::BuiltinJoin(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() >= 1 && arguments.size() <= 2)
  {
    ArrayObjectPtr input_list = std::dynamic_pointer_cast<ArrayObject>(arguments[0]);
    ObjectPtr connector = arguments.size() == 2 ? arguments[1] : std::make_shared<StringObject>("");
    StringObjectPtr connector_string = std::dynamic_pointer_cast<StringObject>(connector);

    std::vector<std::string> input_vector;
    for (auto& object : input_list->elements)
    {
      if (object->type == ObjectType::STRING)
      {
        StringObjectPtr string_object = std::dynamic_pointer_cast<StringObject>(object);
        input_vector.push_back(string_object->Value());
      }
      else if (object->type == ObjectType::CHARACTER)
      {
        CharacterObjectPtr char_object = std::dynamic_pointer_cast<CharacterObject>(object);
        input_vector.push_back(char_object->Value());
      }
      else
      {
        input_vector.push_back(object->Inspect());
      }
    }

    std::string result = join(input_vector, connector_string->Value());
    return std::make_shared<StringObject>(result);
  }
  return std::make_shared<NullObject>();
}