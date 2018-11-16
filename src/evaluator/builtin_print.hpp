#include <evaluator.hpp>

namespace walnut
{

ObjectPtr Evaluator::BuiltinPrint(std::vector<ObjectPtr> arguments)
{
  String end = "\n", sep = " ";
  size_t index = 0;
  for (auto &argument : arguments)
  {
    if (argument->type == ObjectType::KEY_VALUE_ARGUMENT)
    {
      KeyValueArgumentObjectPtr kvpair = std::dynamic_pointer_cast<KeyValueArgumentObject>(argument);
      if (kvpair->key->ToString() == "end")
      {
        if (kvpair->value->type == ObjectType::STRING)
        {
          StringObjectPtr string_end = std::dynamic_pointer_cast<StringObject>(kvpair->value);
          end = string_end->Value();
        }
        else if (kvpair->value->type == ObjectType::CHARACTER)
        {
          CharacterObjectPtr character_end = std::dynamic_pointer_cast<CharacterObject>(kvpair->value);
          end = character_end->Value();
        }
        else
        {
          end = kvpair->value->Inspect();
        }
      }
      else if (kvpair->key->ToString() == "sep")
      {
        if (kvpair->value->type == ObjectType::STRING)
        {
          StringObjectPtr string_end = std::dynamic_pointer_cast<StringObject>(kvpair->value);
          sep = string_end->Value();
        }
        else if (kvpair->value->type == ObjectType::CHARACTER)
        {
          CharacterObjectPtr character_end = std::dynamic_pointer_cast<CharacterObject>(kvpair->value);
          sep = character_end->Value();
        }
        else
        {
          sep = kvpair->value->Inspect();
        }
      }

      arguments.erase(arguments.begin() + index + 1);
    }
    index += 1;
  }

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
    std::cout << end;
  }
  else if (print_vector.size() == 1)
  {
    std::cout << print_vector[0] << end;
  }
  else if (print_vector.size() > 1)
  {
    for (size_t i = 0; i < print_vector.size() - 1; i++)
    {
      std::cout << print_vector[i] << sep;
    }
    std::cout << print_vector[print_vector.size() - 1] << end;
  }
  return std::make_shared<StringObject>(""); // return Void object
}

} // namespace walnut