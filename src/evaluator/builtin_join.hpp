#include <string.hpp>
#include <evaluator.hpp>

namespace walnut
{

ObjectPtr Evaluator::BuiltinJoin(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() >= 1 && arguments.size() <= 2)
  {
    ArrayObjectPtr input_list = std::dynamic_pointer_cast<ArrayObject>(arguments[0]);
    ObjectPtr connector = arguments.size() == 2 ? arguments[1] : std::make_shared<StringObject>("");
    StringObjectPtr connector_string = std::dynamic_pointer_cast<StringObject>(connector);

    std::vector<String> input_vector;
    for (auto &object : input_list->elements)
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

    String result = string::Join(input_vector, connector_string->Value());
    return std::make_shared<StringObject>(result);
  }
  return std::make_shared<NullObject>();
}

} // namespace walnut