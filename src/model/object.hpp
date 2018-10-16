#pragma once
#include <string>

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
    NULL_,
    RETURN
  };

  Type type;
  explicit Object(Type type) : type(type) {}
  virtual String Inspect() {}
};