#include <evaluator.hpp>

namespace walnut
{

  ObjectPtr Evaluator::BuiltinPrint(std::vector<ObjectPtr> arguments)
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

    for (size_t i = 0; i < print_vector.size(); i++)
    {
      std::cout << print_vector[i];
    }
    return std::make_shared<StringObject>(""); // return Void object
  }

}