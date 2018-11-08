#include <evaluator.hpp>

namespace walnut
{

  ObjectPtr Evaluator::BuiltinEnumerate(std::vector<ObjectPtr> arguments)
  {
    return std::make_shared<NullObject>();
  }

} // namespace walnut