#include <evaluator.hpp>

ObjectPtr Evaluator::BuiltinUpsert(std::vector<ObjectPtr> arguments)
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