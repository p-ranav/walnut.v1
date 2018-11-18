#include <evaluator.hpp>

namespace walnut
{

  ObjectPtr Evaluator::BuiltinAny(std::vector<ObjectPtr> arguments)
  {
    if (arguments.size() == 1)
    {
      if (arguments[0]->iterable == true)
      {
        BooleanObjectPtr result = std::make_shared<BooleanObject>(false);
        EnvironmentPtr environment = std::make_shared<Environment>();
        if (arguments[0]->IterableSize() == 0)
          return result;
        arguments[0]->IterableInit();
        do
        {
          if (IsTruth(arguments[0]->IterableCurrentValue(), environment))
          {
            result->value = true;
            break;
          }
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