#include <evaluator.hpp>

namespace walnut
{

  ObjectPtr Evaluator::BuiltinCopy(std::vector<ObjectPtr> arguments)
  {
    if (arguments.size() == 1)
    {
      return arguments[0]->Copy();
    }
    else
    {
      // TODO: report error
    }
    return std::make_shared<NullObject>();
  }

} // namespace walnut