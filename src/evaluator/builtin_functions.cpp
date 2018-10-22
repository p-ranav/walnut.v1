#include <evaluator.hpp>
#include <memory>
#include <algorithm>
#include <string>
#include <stdio.h>      /* printf */
#include <string.h>
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

ObjectPtr Evaluator::print(std::vector<ObjectPtr> arguments)
{
  std::vector<String> print_vector;
  for (auto& argument : arguments)
  {
    if (argument->type == ObjectType::STRING)
    {
      StringObjectPtr string_argument = std::dynamic_pointer_cast<StringObject>(argument);
      print_vector.push_back(string_argument->Value());
    }
    else if (argument->type == ObjectType::CHARACTER)
    {
      CharacterObjectPtr character_argument = std::dynamic_pointer_cast<CharacterObject>(argument);
      print_vector.push_back(character_argument->value);
    }
    else
    {
      print_vector.push_back(argument->Inspect());
    }
  }

  for (size_t i = 0; i < print_vector.size(); i++)
  {
    std::cout << print_vector[i];
  }
  return std::make_shared<StringObject>(""); // return Void object
}

ObjectPtr Evaluator::println(std::vector<ObjectPtr> arguments)
{
  std::vector<String> print_vector;
  for (auto& argument : arguments)
  {
    if (argument->type == ObjectType::STRING)
    {
      StringObjectPtr string_argument = std::dynamic_pointer_cast<StringObject>(argument);
      print_vector.push_back(string_argument->Value());
    }
    else if (argument->type == ObjectType::CHARACTER)
    {
      CharacterObjectPtr character_argument = std::dynamic_pointer_cast<CharacterObject>(argument);
      print_vector.push_back(character_argument->value);
    }
    else
    {
      print_vector.push_back(argument->Inspect());
    }
  }

  if (print_vector.size() == 0)
  {
    std::cout << std::endl;
  }
  else if (print_vector.size() == 1)
  {
    std::cout << print_vector[0] << std::endl;
  }
  else if (print_vector.size() > 1)
  {
    for (size_t i = 0; i < print_vector.size() - 1; i++)
    {
      std::cout << print_vector[i] << " ";
    }
    std::cout << print_vector[print_vector.size() - 1] << std::endl;
  }
  return std::make_shared<StringObject>(""); // return Void object
}

ObjectPtr Evaluator::length(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() == 1)
  {
    if (arguments[0]->type == ObjectType::STRING)
    {
      StringObjectPtr string_object = std::dynamic_pointer_cast<StringObject>(arguments[0]);
      return std::make_shared<IntegerObject>(static_cast<int>(string_object->Length()));
    }
    else if (arguments[0]->type == ObjectType::ARRAY)
    {
      ArrayObjectPtr array_object = std::dynamic_pointer_cast<ArrayObject>(arguments[0]);
      return std::make_shared<IntegerObject>(static_cast<int>(array_object->elements.size()));
    }
  }
  return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::append(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() == 2)
  {
    if (arguments[0]->type == ObjectType::STRING && arguments[1]->type == ObjectType::STRING)
    {
      StringObjectPtr result;
      StringObjectPtr first = std::dynamic_pointer_cast<StringObject>(arguments[0]);
      StringObjectPtr second = std::dynamic_pointer_cast<StringObject>(arguments[1]);
      return std::make_shared<StringObject>(first->Value() + second->Value());
    }
    else if (arguments[0]->type == ObjectType::STRING && arguments[1]->type == ObjectType::CHARACTER)
    {
      StringObjectPtr result;
      StringObjectPtr first = std::dynamic_pointer_cast<StringObject>(arguments[0]);
      CharacterObjectPtr second = std::dynamic_pointer_cast<CharacterObject>(arguments[1]);
      return std::make_shared<StringObject>(first->Value() + second->Value());
    }
    else if (arguments[0]->type == ObjectType::ARRAY)
    {
      ArrayObjectPtr array_object = std::dynamic_pointer_cast<ArrayObject>(arguments[0]);
      ArrayObject array_copy = ArrayObject(*(array_object.get()));
      array_copy.elements.push_back(arguments[1]);
      return std::make_shared<ArrayObject>(array_copy);
    }
  }
  return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::extend(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() == 2)
  {
    if (arguments[0]->type == ObjectType::ARRAY && arguments[1]->type == ObjectType::ARRAY)
    {
      ArrayObjectPtr first = std::dynamic_pointer_cast<ArrayObject>(arguments[0]);
      ArrayObjectPtr second = std::dynamic_pointer_cast<ArrayObject>(arguments[1]);
      ArrayObject array_copy = ArrayObject(*(first.get()));
      for (auto& element: second->elements)
        array_copy.elements.push_back(element);
      return std::make_shared<ArrayObject>(array_copy);
    }
  }
  return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::range(std::vector<ObjectPtr> arguments)
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

ObjectPtr Evaluator::map(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() == 2)
  {
    if (arguments[0]->iterable == true && arguments[1]->type == ObjectType::FUNCTION)
    {
      ObjectPtr result;
      switch (arguments[0]->type)
      {
      case ObjectType::ARRAY:
        result = std::make_shared<ArrayObject>();
        break;
      case ObjectType::STRING:
        result = std::make_shared<StringObject>("");
        break;
      case ObjectType::RANGE:
        result = std::make_shared<ArrayObject>();
        break;
      case ObjectType::HASH:
        result = std::make_shared<HashObject>();
        break;
      default:
        result = std::make_shared<NullObject>();
        break;
      }

      FunctionObjectPtr map_function = std::dynamic_pointer_cast<FunctionObject>(arguments[1]);
      arguments[0]->IterableInit();
      do
      {
        if (result->type != ObjectType::HASH)
        {
          result->IterableAppend(ApplyFunction(map_function, { arguments[0]->IterableCurrentValue() }));
        }
        else
        {
          ObjectPtr map_result = ApplyFunction(map_function, { arguments[0]->IterableCurrentValue() });
          if (map_result->type == ObjectType::ARRAY)
          {
            ArrayObjectPtr array_result = std::dynamic_pointer_cast<ArrayObject>(map_result);
            if (array_result->elements.size() == 2)
            {
              HashObjectPtr hash_result = std::dynamic_pointer_cast<HashObject>(result);
              HashPair new_hash_pair(array_result->elements[0], array_result->elements[1]);
              hash_result->Set(Hash(array_result->elements[0]), new_hash_pair);
            }
          }
        }
      } while (arguments[0]->IterableNext() != arguments[0]->IterableEnd());
      return result;
    }
  }
  return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::filter(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() == 2)
  {
    if (arguments[0]->iterable == true && arguments[1]->type == ObjectType::FUNCTION)
    {
      ObjectPtr result;
      switch (arguments[0]->type)
      {
      case ObjectType::ARRAY:
        result = std::make_shared<ArrayObject>();
        break;
      case ObjectType::STRING:
        result = std::make_shared<StringObject>("");
        break;
      case ObjectType::RANGE:
        result = std::make_shared<ArrayObject>();
        break;
      default:
        result = std::make_shared<NullObject>();
        break;
      }

      FunctionObjectPtr map_function = std::dynamic_pointer_cast<FunctionObject>(arguments[1]);
      arguments[0]->IterableInit();
      do
      {
        ObjectPtr filter_result = ApplyFunction(map_function, { arguments[0]->IterableCurrentValue() });
        if (filter_result->type == ObjectType::BOOLEAN)
        {
          BooleanObjectPtr filter_boolean_result = std::dynamic_pointer_cast<BooleanObject>(filter_result);
          if (filter_boolean_result->value)
            result->IterableAppend(arguments[0]->IterableCurrentValue());
        }
        
      } while (arguments[0]->IterableNext() != arguments[0]->IterableEnd());

      return result;
    }
  }
  return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::insert(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() == 3)
  {
    if (arguments[0]->type == ObjectType::ARRAY && 
        arguments[1]->type == ObjectType::INTEGER)
    {
      ArrayObjectPtr input_array = std::dynamic_pointer_cast<ArrayObject>(arguments[0]);
      IntegerObjectPtr index = std::dynamic_pointer_cast<IntegerObject>(arguments[1]);

      ObjectPtr result = input_array->Copy();
      ArrayObjectPtr result_array = std::dynamic_pointer_cast<ArrayObject>(result);

      if (static_cast<size_t>(index->value) < result_array->elements.size())
      {
        result_array->elements.insert(result_array->elements.begin() + index->value, arguments[2]);
        return result;
      }
      else
      {
        std::cout << "evaluator error: list index out of range - "
          << "array size = " << result_array->elements.size()
          << "; provided index = " << index->value
          << std::endl;
        return std::make_shared<NullObject>();
      }
    }
    else if (arguments[0]->type == ObjectType::HASH)
    {
      HashObjectPtr input_hash = std::dynamic_pointer_cast<HashObject>(arguments[0]);

      ObjectPtr result = input_hash->Copy();
      HashObjectPtr result_hash = std::dynamic_pointer_cast<HashObject>(result);
      if (result_hash->pairs.find(Hash(arguments[1])) != result_hash->pairs.end())
      {
        String key = arguments[1]->Inspect();
        if (arguments[1]->type == ObjectType::STRING)
        {
          StringObjectPtr string_argument = std::dynamic_pointer_cast<StringObject>(arguments[1]);
          key = "\"" + string_argument->Value() + "\"";
        }
        String value = arguments[2]->Inspect();
        if (arguments[2]->type == ObjectType::STRING)
        {
          StringObjectPtr string_argument = std::dynamic_pointer_cast<StringObject>(arguments[2]);
          value = "\"" + string_argument->Value() + "\"";
        }
        std::cout << "evaluator warning: "
          << "dictionary already has key " << key
          << " - dictionary.insert(" << key << ", " <<  value 
          << ") has done nothing"
          << std::endl;
      }
      else
      {
        HashPair pair(arguments[1], arguments[2]);
        result_hash->pairs.insert(std::make_pair(Hash(arguments[1]), pair));
      }
      return result;
    }
  }
  return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::upsert(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() == 3)
  {
    if (arguments[0]->type == ObjectType::HASH)
    {
      HashObjectPtr input_hash = std::dynamic_pointer_cast<HashObject>(arguments[0]);

      ObjectPtr result = input_hash->Copy();
      HashObjectPtr result_hash = std::dynamic_pointer_cast<HashObject>(result);

      HashPair pair(arguments[1], arguments[2]);
      result_hash->Set(Hash(arguments[1]), pair);

      return result;
    }
  }
  return std::make_shared<NullObject>();
}