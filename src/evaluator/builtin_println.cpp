#include <evaluator.hpp>

ObjectPtr Evaluator::BuiltinPrintln(std::vector<ObjectPtr> arguments)
{
  std::vector<String> print_vector;
  for (auto &argument : arguments)
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