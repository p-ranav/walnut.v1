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
      else if (arguments[0]->type == ObjectType::HASH)
      {
        HashObjectPtr input_hash = std::dynamic_pointer_cast<HashObject>(arguments[0]);

        if (input_hash->pairs.find(Hash(arguments[1])) != input_hash->pairs.end())
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
            << " - dictionary.insert(" << key << ", " << value
            << ") has done nothing"
            << std::endl;
        }
        else
        {
          HashPair pair(arguments[1], arguments[2]);
          input_hash->pairs.insert(std::make_pair(Hash(arguments[1]), pair));
        }
        return input_hash;
      }
    }
    return std::make_shared<NullObject>();
  }

}