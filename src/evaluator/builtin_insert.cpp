#include <evaluator.hpp>

namespace walnut
{

  ObjectPtr Evaluator::BuiltinInsert(std::vector<ObjectPtr> arguments)
  {
    if (arguments.size() == 3)
    {
      if (arguments[0]->type == ObjectType::ARRAY &&
        arguments[1]->type == ObjectType::INTEGER)
      {
        ArrayObjectPtr input_array = std::dynamic_pointer_cast<ArrayObject>(arguments[0]);
        IntegerObjectPtr index = std::dynamic_pointer_cast<IntegerObject>(arguments[1]);

        if (index->value < static_cast<int64_t>(input_array->elements.size()))
        {
          input_array->elements.insert(input_array->elements.begin() + static_cast<size_t>(index->value), arguments[2]);
          return input_array;
        }
        else
        {
          if (input_array->elements.size() == 0)
          {
            input_array->elements.insert(input_array->elements.begin(), arguments[2]);
            return input_array;
          }
          else
          {
            std::cout << "evaluator error: list index out of range - "
              << "array size = " << input_array->elements.size()
              << "; provided index = " << index->value
              << std::endl;
            return std::make_shared<NullObject>();
          }
        }
      }
    }
    return std::make_shared<NullObject>();
  }

}