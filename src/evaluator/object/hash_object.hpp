#pragma once
#include <object.hpp>
#include <hash_key.hpp>
#include <tuple_object.hpp>
#include <vector>
#include <memory>
#include <map>

namespace walnut
{

struct HashPair
{
  ObjectPtr key;
  ObjectPtr value;
  HashPair() : key(nullptr), value(nullptr) {}
  HashPair(ObjectPtr key, ObjectPtr value) : key(key), value(value) {}
};

struct HashObject : Object
{
  std::map<HashKey, HashPair> pairs;
  explicit HashObject() : Object(HASH, true), pairs({}) {}
  typedef std::shared_ptr<HashObject> HashObjectPtr;

  size_t current_index;
  std::vector<ObjectPtr> elements;
  typedef std::vector<ObjectPtr>::iterator ObjectIterator;
  ObjectIterator iterator;

  ObjectPtr Copy() override
  {
    HashObjectPtr result = std::make_shared<HashObject>();
    for (auto &pair : pairs)
    {
      HashPair copy(pair.second.key->Copy(), pair.second.value->Copy());
      result->pairs.insert(std::make_pair(pair.first, copy));
    }
    return result;
  }

  void IterableInit() override
  {
    current_index = 0;

    if (elements.size() > 0)
      elements.clear();

    for (auto &pair : pairs)
    {
      std::shared_ptr<TupleObject> pair_as_tuple = std::make_shared<TupleObject>();
      pair_as_tuple->IterableAppend(pair.second.key);
      pair_as_tuple->IterableAppend(pair.second.value);
      elements.push_back(pair_as_tuple);
      break;
    }
  }

  ObjectIterator IterableNext() override
  {
    current_index += 1;

    if (current_index == pairs.size())
    {
      return elements.end();
    }

    if (elements.size() == 0)
    {
      size_t index = 0;
      for (auto &pair : pairs)
      {
        if (index == current_index)
        {
          std::shared_ptr<TupleObject> pair_as_tuple = std::make_shared<TupleObject>();
          pair_as_tuple->IterableAppend(pair.second.key);
          pair_as_tuple->IterableAppend(pair.second.value);
          elements.push_back(pair_as_tuple);
          break;
        }
        index += 1;
      }
    }
    else
    {
      size_t index = 0;
      for (auto &pair : pairs)
      {
        if (index == current_index)
        {
          std::shared_ptr<TupleObject> pair_as_tuple = std::make_shared<TupleObject>();
          pair_as_tuple->IterableAppend(pair.second.key);
          pair_as_tuple->IterableAppend(pair.second.value);
          elements[0] = pair_as_tuple;
          break;
        }
        index += 1;
      }
    }
    return elements.begin();
  }

  ObjectPtr IterableCurrentValue() override
  {
    if (elements.size() == 0)
      return std::make_shared<NullObject>();
    else
      return elements[0];
  }

  std::vector<ObjectPtr>::iterator IterableEnd() override
  {
    return elements.end();
  }

  void IterableAppend(ObjectPtr value) override {}

  size_t IterableSize() override
  {
    return elements.size();
  }

  String Inspect() override
  {
    String result = "{";
    size_t index = 1;
    for (auto &pair : pairs)
    {
      if (pair.second.key->type == ObjectType::STRING)
      {
        StringObjectPtr string_key = std::dynamic_pointer_cast<StringObject>(pair.second.key);
        result += "\"" + string_key->Value() + "\"";
      }
      else
      {
        result += pair.second.key->Inspect();
      }

      result += " : ";

      if (pair.second.value->type == ObjectType::STRING)
      {
        StringObjectPtr string_value = std::dynamic_pointer_cast<StringObject>(pair.second.value);
        result += "\"" + string_value->Value() + "\"";
      }
      else
      {
        result += pair.second.value->Inspect();
      }

      if (index < pairs.size())
        result += ", ";
      index += 1;
    }
    result += "}";
    return result;
  }

  HashPair &Get(HashKey key)
  {
    if (pairs.find(key) != pairs.end())
      return pairs[key];
    else
    {
      throw std::runtime_error("error: key not found");
    }
  }

  void Set(HashKey key, HashPair value)
  {
    if (pairs.find(key) != pairs.end())
      pairs[key] = value;
    else
      pairs.insert(std::make_pair(key, value));
  }
};

typedef std::shared_ptr<HashObject> HashObjectPtr;

} // namespace walnut