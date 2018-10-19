#include <evaluator.hpp>
#include <memory>

ObjectPtr Evaluator::print(std::vector<ObjectPtr> arguments, bool mutate)
{
  String result;
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

  if (print_vector.size() == 1)
  {
    std::cout << print_vector[0] << std::endl;
    result += print_vector[0];
  }
  else if (print_vector.size() > 1)
  {
    for (size_t i = 0; i < print_vector.size() - 1; i++)
    {
      std::cout << print_vector[i] << " ";
      result += print_vector[i] + " ";
    }
    std::cout << print_vector[print_vector.size() - 1] << std::endl;
    result += print_vector[print_vector.size() - 1];
  }
  return std::make_shared<StringObject>(""); // return Void object
}

ObjectPtr Evaluator::length(std::vector<ObjectPtr> arguments, bool mutate)
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

ObjectPtr Evaluator::append(std::vector<ObjectPtr> arguments, bool mutate)
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
      // TODO: deep copy the array and mutate/return either the actual array or the copy
      if (mutate)
      {
        ArrayObjectPtr array_object = std::dynamic_pointer_cast<ArrayObject>(arguments[0]);
        array_object->elements.push_back(arguments[1]);
        return std::make_shared<NullObject>();
      }
      else 
      {
        ArrayObjectPtr array_object = std::dynamic_pointer_cast<ArrayObject>(arguments[0]);
        ArrayObject array_copy = ArrayObject(*(array_object.get()));
        array_copy.elements.push_back(arguments[1]);
        return std::make_shared<ArrayObject>(array_copy);
      }
    }
  }
  return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::map(std::vector<ObjectPtr> arguments, bool mutate)
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
        result->elements.push_back(ApplyFunction(map_function, { element }));
      }

      return result;
    }
  }
  return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::filter(std::vector<ObjectPtr> arguments, bool mutate)
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

ObjectPtr Evaluator::join(std::vector<ObjectPtr> arguments, bool mutate)
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