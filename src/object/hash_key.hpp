#pragma once
#include <object.hpp>
#include <boolean_object.hpp>
#include <integer_object.hpp>
#include <double_object.hpp>
#include <string_object.hpp>
#include <memory>
#include <functional>

namespace walnut
{

  struct HashKey : Object
  {
    size_t value;
    explicit HashKey(ObjectType type, size_t value) : Object(type), value(value) {}

    friend bool operator<(const HashKey &left, const HashKey &right)
    {
      return (left.value < right.value);
    }
  };

  typedef std::shared_ptr<HashKey> HashKeyPtr;

  HashKey Hash(ObjectPtr object);

}