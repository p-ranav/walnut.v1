#include <evaluator.hpp>

namespace walnut
{

  ObjectPtr Evaluator::BuiltinSet(std::vector<ObjectPtr> arguments)
  {
    if (arguments.size() == 0)
    {
      return std::make_shared<SetObject>();
    }
    else if (arguments.size() == 1)
    {
      if (arguments[0]->iterable == true)
      {
        SetObjectPtr result = std::make_shared<SetObject>();
        arguments[0]->IterableInit();
        do
        {
          result->IterableAppend(arguments[0]->IterableCurrentValue()->Copy());
        } while (arguments[0]->IterableNext() != arguments[0]->IterableEnd());
        return result;
      }
    }
    return std::make_shared<NullObject>();
  }

} // namespace walnut