#include <evaluator.hpp>

namespace walnut
{

ObjectPtr Evaluator::BuiltinMap(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() == 2)
  {
    if (arguments[0]->iterable == true && arguments[1]->type == ObjectType::FUNCTION)
    {
      ObjectPtr result;
      switch (arguments[0]->type)
      {
      case ObjectType::ARRAY:
        result = std::make_shared<ArrayObject>();
        break;
      case ObjectType::STRING:
        result = std::make_shared<StringObject>("");
        break;
      case ObjectType::RANGE:
        result = std::make_shared<ArrayObject>();
        break;
      case ObjectType::SET:
        result = std::make_shared<SetObject>();
        break;
      default:
        result = std::make_shared<NullObject>();
        break;
      }

      FunctionObjectPtr map_function = std::dynamic_pointer_cast<FunctionObject>(arguments[1]);
      arguments[0]->IterableInit();
      do
      {
        result->IterableAppend(ApplyFunction(map_function, {arguments[0]->IterableCurrentValue()}));
      } while (arguments[0]->IterableNext() != arguments[0]->IterableEnd());
      return result;
    }
  }
  return std::make_shared<NullObject>();
}

} // namespace walnut