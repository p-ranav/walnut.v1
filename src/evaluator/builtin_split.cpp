#include <string.hpp>
#include <evaluator.hpp>

namespace walnut
{

ObjectPtr Evaluator::BuiltinSplit(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() == 2)
  {
    if (arguments[0]->type == ObjectType::STRING && arguments[1]->type == ObjectType::STRING)
    {
      StringObjectPtr input_string = std::dynamic_pointer_cast<StringObject>(arguments[0]);
      StringObjectPtr split_string = std::dynamic_pointer_cast<StringObject>(arguments[1]);

      if (input_string->Value() == "")
        return std::make_shared<ArrayObject>();

      std::vector<std::string> split_result = string::Split(input_string->Value(), split_string->Value());
      ArrayObjectPtr result = std::make_shared<ArrayObject>();
      for (auto &part : split_result)
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

} // namespace walnut