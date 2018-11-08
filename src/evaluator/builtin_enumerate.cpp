#include <evaluator.hpp>

namespace walnut
{

  ObjectPtr Evaluator::BuiltinEnumerate(std::vector<ObjectPtr> arguments)
  {
    size_t start = 0;

    if (arguments.size() == 2)
    {
      if (arguments[1]->type == ObjectType::KEY_VALUE_ARGUMENT)
      {
        KeyValueArgumentObjectPtr kvpair = std::dynamic_pointer_cast<KeyValueArgumentObject>(arguments[1]);
        if (kvpair->key->ToString() == "start")
        {
          if (kvpair->value->type == ObjectType::INTEGER)
          {
            IntegerObjectPtr integer_start = std::dynamic_pointer_cast<IntegerObject>(kvpair->value);
            start = static_cast<size_t>(integer_start->value);
          }
          else
          {
            // TODO: report error
          }
        }
        arguments.erase(arguments.begin() + 1);
      }
      else if (arguments[1]->type == ObjectType::INTEGER)
      {
        IntegerObjectPtr start_argument = std::dynamic_pointer_cast<IntegerObject>(arguments[1]);
        start = start_argument->value;
        arguments.erase(arguments.begin() + 1);
      }
      else
      {
        // TODO: report error
      }
    }

    return std::make_shared<EnumerateObject>(arguments[0], start);
  }

} // namespace walnut