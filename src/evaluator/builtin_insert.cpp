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
          input_array->elements.insert(input_array->elements.begin() + input_array->elements.size(), arguments[2]);
          return input_array;
        }
      }
    }
    else if (arguments[0]->type == ObjectType::TUPLE &&
      arguments[1]->type == ObjectType::INTEGER)
    {
      TupleObjectPtr input_tuple = std::dynamic_pointer_cast<TupleObject>(arguments[0]);
      IntegerObjectPtr index = std::dynamic_pointer_cast<IntegerObject>(arguments[1]);

      if (index->value < static_cast<int64_t>(input_tuple->elements.size()))
      {
        input_tuple->elements.insert(input_tuple->elements.begin() + static_cast<size_t>(index->value), arguments[2]);
        return input_tuple;
      }
      else
      {
        if (input_tuple->elements.size() == 0)
        {
          input_tuple->elements.insert(input_tuple->elements.begin(), arguments[2]);
          return input_tuple;
        }
        else
        {
          input_tuple->elements.insert(input_tuple->elements.begin() + input_tuple->elements.size(), arguments[2]);
          return input_tuple;
        }
      }
    }
    else if (arguments[0]->type == ObjectType::HASH)
    {
      HashObjectPtr input_hash = std::dynamic_pointer_cast<HashObject>(arguments[0]);

      if (input_hash->pairs.find(Hash(arguments[1])) == input_hash->pairs.end())
      {
        HashPair pair(arguments[1], arguments[2]);
        input_hash->pairs.insert(std::make_pair(Hash(arguments[1]), pair));
      }
      return input_hash;
    }
  }
  return std::make_shared<NullObject>();
}

} // namespace walnut