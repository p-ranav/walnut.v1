#include <evaluator.hpp>

namespace walnut
{

  ObjectPtr Evaluator::BuiltinExtend(std::vector<ObjectPtr> arguments)
  {
    if (arguments.size() == 2)
    {
      if (arguments[0]->type == ObjectType::ARRAY && arguments[1]->type == ObjectType::ARRAY)
      {
        ArrayObjectPtr first = std::dynamic_pointer_cast<ArrayObject>(arguments[0]);
        ArrayObjectPtr second = std::dynamic_pointer_cast<ArrayObject>(arguments[1]);
        ArrayObject array_copy = ArrayObject(*(first.get()));
        for (auto &element : second->elements)
          array_copy.elements.push_back(element);
        return std::make_shared<ArrayObject>(array_copy);
      }
    }
    return std::make_shared<NullObject>();
  }

}