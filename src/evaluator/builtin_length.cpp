#include <evaluator.hpp>

namespace walnut
{

  ObjectPtr Evaluator::BuiltinLength(std::vector<ObjectPtr> arguments)
  {
    if (arguments.size() == 1)
    {
      if (arguments[0]->iterable == true)
      {
        return std::make_shared<IntegerObject>(static_cast<int>(arguments[0]->IterableSize()));
      }
    }
    return std::make_shared<NullObject>();
  }

}