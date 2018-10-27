#include <evaluator.hpp>

namespace walnut
{

  ObjectPtr Evaluator::BuiltinRange(std::vector<ObjectPtr> arguments)
  {
    if (arguments.size() == 1)
    {
      ObjectPtr start_argument = nullptr;
      ObjectPtr end_argument = arguments[0];
      ObjectPtr step_argument = nullptr;
      bool integral_range = true;
      double start = 0.0, end = 0.0, step = 1.0;

      if (end_argument->type == ObjectType::DOUBLE)
        integral_range = false;

      if (end_argument->type == ObjectType::DOUBLE)
        end = std::dynamic_pointer_cast<DoubleObject>(end_argument)->value;
      else if (end_argument->type == ObjectType::INTEGER)
        end = static_cast<double>(std::dynamic_pointer_cast<IntegerObject>(end_argument)->value);

      if (start > end)
        step = step * -1;

      return std::make_shared<RangeObject>(start, end, step, integral_range);
    }
    if (arguments.size() >= 2)
    {
      ObjectPtr start_argument = arguments[0];
      ObjectPtr end_argument = arguments[1];
      ObjectPtr step_argument = nullptr;
      bool integral_range = true;
      double start = 0.0, end = 0.0, step = 0.0;

      if (arguments.size() == 3)
        step_argument = arguments[2];

      if (start_argument->type == ObjectType::DOUBLE || end_argument->type == ObjectType::DOUBLE || (step_argument && step_argument->type == ObjectType::DOUBLE))
        integral_range = false;

      if (start_argument->type == ObjectType::DOUBLE)
        start = std::dynamic_pointer_cast<DoubleObject>(start_argument)->value;
      else if (start_argument->type == ObjectType::INTEGER)
        start = static_cast<double>(std::dynamic_pointer_cast<IntegerObject>(start_argument)->value);

      if (end_argument->type == ObjectType::DOUBLE)
        end = std::dynamic_pointer_cast<DoubleObject>(end_argument)->value;
      else if (end_argument->type == ObjectType::INTEGER)
        end = static_cast<double>(std::dynamic_pointer_cast<IntegerObject>(end_argument)->value);

      if (step_argument)
      {
        if (step_argument->type == ObjectType::DOUBLE)
          step = std::dynamic_pointer_cast<DoubleObject>(step_argument)->value;
        else if (step_argument->type == ObjectType::INTEGER)
          step = static_cast<double>(std::dynamic_pointer_cast<IntegerObject>(step_argument)->value);
      }
      else
      {
        step = 1;
      }

      return std::make_shared<RangeObject>(start, end, step, integral_range);
    }
    return std::make_shared<NullObject>();
  }

}