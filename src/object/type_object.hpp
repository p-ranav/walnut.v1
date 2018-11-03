#pragma once
#include <object.hpp>
#include <memory>

namespace walnut
{

  struct TypeObject : Object
  {
    ObjectType value;
    explicit TypeObject(ObjectType value) : Object(TYPE), value(value) {}

    ObjectPtr Copy() override
    {
      return std::make_shared<TypeObject>(value);
    }

    String Inspect() override
    {
      switch (value)
      {
      case INTEGER:
        return "integer";
      case DOUBLE:
        return "double";
      case BOOLEAN:
        return "boolean";
      case CHARACTER:
        return "character";
      case STRING:
        return "string";
      case NULL_:
        return "null";
      case RETURN:
        return "return";
      case FUNCTION:
        return "function";
      case BUILTIN_FUNCTION:
        return "builtin";
      case ARRAY:
        return "array";
      case RANGE:
        return "range";
      case HASH:
        return "hash";
      case SET:
        return "set";
      case TUPLE:
        return "tuple";
      case KEY_VALUE_ARGUMENT:
        return "kwarg";
      default:
        return "type";
      }
    }
  };

  typedef std::shared_ptr<TypeObject> TypeObjectPtr;

}