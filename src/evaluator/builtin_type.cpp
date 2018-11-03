#include <evaluator.hpp>

namespace walnut
{

  ObjectPtr Evaluator::BuiltinType(std::vector<ObjectPtr> arguments)
  {
    if (arguments.size() == 1)
    {
      return std::make_shared<TypeObject>(arguments[0]->type);
    }
  }

}