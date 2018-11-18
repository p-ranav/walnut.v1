#include <evaluator.hpp>

namespace walnut
{

  ObjectPtr Evaluator::BuiltinTuple(std::vector<ObjectPtr> arguments)
  {
    if (arguments.size() == 0)
    {
      return std::make_shared<TupleObject>();
    }
    else if (arguments.size() == 1)
    {
      if (arguments[0]->iterable == true)
      {
        TupleObjectPtr result = std::make_shared<TupleObject>();
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