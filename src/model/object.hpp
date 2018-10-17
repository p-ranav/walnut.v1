#pragma once
#include <iostream>
#include <string>
#include <memory>

typedef std::string String;
typedef std::string& StringRef;
typedef const std::string& StringConstRef;

struct Object
{
  enum Type
  {
    INTEGER,
    DOUBLE,
    BOOLEAN,
    STRING,
    NULL_,
    RETURN,
    FUNCTION,
    BUILTIN_FUNCTION,
    ARRAY
  };

  Type type;
  explicit Object(Type type) : type(type) {}
  virtual ~Object() {}
  virtual String Inspect() = 0;
};

typedef std::shared_ptr<Object> ObjectPtr;
typedef Object::Type ObjectType;