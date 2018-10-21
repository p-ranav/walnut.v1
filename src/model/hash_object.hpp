#pragma once
#include <object.hpp>
#include <hash_key.hpp>
#include <memory>
#include <map>

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

  ObjectPtr Copy() override
  {
    HashObjectPtr result = std::make_shared<HashObject>();
    for (auto& pair : pairs)
    {
      HashPair copy(pair.second.key->Copy(), pair.second.value->Copy());
      pairs.insert(std::make_pair(pair.first, copy));
    }
    return result;
  }

  String Inspect() override {
    String result = "{";
    size_t index = 1;
    for (auto& pair : pairs)
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

  void Set(HashKey key, HashPair value)
  {
    if (pairs.find(key) != pairs.end())
      pairs[key] = value;
    else
      pairs.insert(std::make_pair(key, value));
  }
};

typedef std::shared_ptr<HashObject> HashObjectPtr;