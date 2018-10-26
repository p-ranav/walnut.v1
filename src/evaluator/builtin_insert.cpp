#include <evaluator.hpp>

ObjectPtr Evaluator::BuiltinInsert(std::vector<ObjectPtr> arguments)
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

      if (index->value < static_cast<int64_t>(result_array->elements.size()))
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
          << " - dictionary.insert(" << key << ", " << value
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