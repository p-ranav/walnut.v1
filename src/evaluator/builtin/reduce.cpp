#include <evaluator.hpp>

namespace walnut
{

  ObjectPtr Evaluator::BuiltinReduce(std::vector<ObjectPtr> arguments)
  {
    ObjectPtr result;

    if (arguments.size() == 3)
    {
      if (arguments[2]->type == ObjectType::KEY_VALUE_ARGUMENT)
      {
        KeyValueArgumentObjectPtr kvpair = std::dynamic_pointer_cast<KeyValueArgumentObject>(arguments[2]);
        if (kvpair->key->ToString() == "initial_value")
        {
          result = kvpair->value;
        }
      }
      else {
        result = arguments[2];
      }

      if (arguments[0]->iterable == true && arguments[1]->type == ObjectType::FUNCTION)
      {
        FunctionObjectPtr reduce_function = std::dynamic_pointer_cast<FunctionObject>(arguments[1]);
        arguments[0]->IterableInit();
        do
        {
          result = ApplyFunction(reduce_function, { result, arguments[0]->IterableCurrentValue() });
        } while (arguments[0]->IterableNext() != arguments[0]->IterableEnd());
        return result;
      }
    }
    else
    {
      // TODO: report error
    }
    return std::make_shared<NullObject>();
  }

} // namespace walnut