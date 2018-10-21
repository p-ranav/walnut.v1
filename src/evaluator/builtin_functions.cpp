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
      default:
        result = std::make_shared<NullObject>();
        break;
      }

      FunctionObjectPtr map_function = std::dynamic_pointer_cast<FunctionObject>(arguments[1]);
      do
      {
        result->IterableAppend(ApplyFunction(map_function, { arguments[0]->IterableCurrentValue() }));
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
      default:
        result = std::make_shared<NullObject>();
        break;
      }

      FunctionObjectPtr map_function = std::dynamic_pointer_cast<FunctionObject>(arguments[1]);
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