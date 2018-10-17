#include <evaluator.hpp>

ObjectPtr Evaluator::print(std::vector<ObjectPtr> arguments)
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

ObjectPtr Evaluator::len(std::vector<ObjectPtr> arguments)
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
      StringObjectPtr first = std::dynamic_pointer_cast<StringObject>(arguments[0]);
      StringObjectPtr second = std::dynamic_pointer_cast<StringObject>(arguments[1]);
      return std::make_shared<StringObject>(first->value + second->value);
    }
    else if (arguments[0]->type == ObjectType::ARRAY)
    {
      ArrayObjectPtr array_object = std::dynamic_pointer_cast<ArrayObject>(arguments[0]);
      array_object->elements.push_back(arguments[1]);
      return array_object;
    }
  }
  return std::make_shared<NullObject>();
}