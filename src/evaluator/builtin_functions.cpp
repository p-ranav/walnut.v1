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
      print_vector.push_back(string_argument->value);
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
      print_vector.push_back(string_argument->value);
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

ObjectPtr Evaluator::printf_(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() > 1)
  {
    StringObjectPtr format = std::dynamic_pointer_cast<StringObject>(arguments[0]);
    if (format)
    {
      String format_string = format->value;
      std::vector<size_t> used_arguments;

      for (size_t i = 1; i < arguments.size(); i++)
      {
        String search_string = "{" + std::to_string(i - 1) + "}";
        // TODO: catch exception in find and report error
        size_t search_index = format_string.find(search_string);
        std::string::iterator begin = format_string.begin() + search_index;
        std::string::iterator end = begin + search_string.length();
        if (begin != format_string.end())
        {
          format_string.replace(begin, end, arguments[i]->Inspect().c_str());
          used_arguments.push_back(i);
        }
      }

      std::cout << format_string;

    }
    else
    {
      // TODO: report error
    }
  }
  return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::length(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() == 1)
  {
    if (arguments[0]->type == ObjectType::STRING)
    {
      StringObjectPtr string_object = std::dynamic_pointer_cast<StringObject>(arguments[0]);
      return std::make_shared<IntegerObject>(static_cast<int>(string_object->value.length()));
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
      return std::make_shared<StringObject>(first->value + second->value);
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
    if (arguments[0]->type == ObjectType::ARRAY && arguments[1]->type == ObjectType::FUNCTION)
    {
      ArrayObjectPtr result = std::make_shared<ArrayObject>();
      ArrayObjectPtr array_object = std::dynamic_pointer_cast<ArrayObject>(arguments[0]);
      FunctionObjectPtr map_function = std::dynamic_pointer_cast<FunctionObject>(arguments[1]);
      for (auto& element : array_object->elements)
        result->elements.push_back(ApplyFunction(map_function, { element }));
      return result;
    }
  }
  return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::filter(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() == 2)
  {
    if (arguments[0]->type == ObjectType::ARRAY && arguments[1]->type == ObjectType::FUNCTION)
    {
      ArrayObjectPtr result = std::make_shared<ArrayObject>();
      ArrayObjectPtr array_object = std::dynamic_pointer_cast<ArrayObject>(arguments[0]);
      FunctionObjectPtr map_function = std::dynamic_pointer_cast<FunctionObject>(arguments[1]);
      for (auto& element : array_object->elements)
      {
        ObjectPtr filter_result = ApplyFunction(map_function, { element });
        if (filter_result->type == ObjectType::BOOLEAN)
        {
          BooleanObjectPtr filter_boolean_result = std::dynamic_pointer_cast<BooleanObject>(filter_result);
          if (filter_boolean_result->value)
            result->elements.push_back(element);
        }
      }
      return result;
    }
  }
  return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::join(std::vector<ObjectPtr> arguments)
{
  if (arguments.size() == 1)
  {
    if (arguments[0]->type == ObjectType::ARRAY)
    {
      StringObjectPtr result = std::make_shared<StringObject>("");
      ArrayObjectPtr array_object = std::dynamic_pointer_cast<ArrayObject>(arguments[0]);
      StringObjectPtr connector = std::make_shared<StringObject>("");
      for (auto& element : array_object->elements)
      {
        if (element->type == ObjectType::STRING)
        {
          StringObjectPtr object = std::dynamic_pointer_cast<StringObject>(element);
          result->value += object->value;
        }
        else
          result->value += element->Inspect();
        if (&element != &(array_object->elements).back())
          result->value += connector->value;
      }
      return result;
    }
  }  
  else if (arguments.size() == 2)
  {
    if (arguments[0]->type == ObjectType::ARRAY && arguments[1]->type == ObjectType::STRING)
    {
      StringObjectPtr result = std::make_shared<StringObject>("");
      ArrayObjectPtr array_object = std::dynamic_pointer_cast<ArrayObject>(arguments[0]);
      StringObjectPtr connector = std::dynamic_pointer_cast<StringObject>(arguments[1]);
      for (auto& element : array_object->elements)
      {
        if (element->type == ObjectType::STRING)
        {
          StringObjectPtr object = std::dynamic_pointer_cast<StringObject>(element);
          result->value += object->value;
        }
        else
          result->value += element->Inspect();
        if (&element != &(array_object->elements).back())
          result->value += connector->value;
      }

      return result;
    }
  }
  return std::make_shared<NullObject>();
}