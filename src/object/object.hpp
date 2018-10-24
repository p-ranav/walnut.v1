#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>

typedef std::string String;
typedef std::string &StringRef;
typedef const std::string &StringConstRef;

struct Object
{
  enum Type
  {
    INTEGER,
    DOUBLE,
    BOOLEAN,
    CHARACTER,
    STRING,
    NULL_,
    RETURN,
    FUNCTION,
    BUILTIN_FUNCTION,
    ARRAY,
    RANGE,
    HASH,
    SET,
    TUPLE
  };

  Type type;
  bool iterable;
  bool hashable;
  Object() : type(NULL_), iterable(false), hashable(false) {}
  explicit Object(Type type, bool iterable = false, bool hashable = false) : type(type), iterable(iterable), hashable(hashable) {}
  virtual ~Object() {}
  virtual String Inspect() { return ""; }

  typedef std::shared_ptr<Object> ObjectPtr;

  virtual ObjectPtr Copy() { return std::make_shared<Object>(); }
  virtual void IterableInit() {}
  virtual std::vector<ObjectPtr>::iterator IterableNext() { return std::vector<ObjectPtr>::iterator(); }
  virtual std::vector<ObjectPtr>::iterator IterableEnd() { return std::vector<ObjectPtr>::iterator(); }
  virtual ObjectPtr IterableCurrentValue() { return nullptr; }
  virtual size_t IterableSize() { return 0; }
  virtual void IterableAppend(ObjectPtr value) {}
};

typedef std::shared_ptr<Object> ObjectPtr;
typedef Object::Type ObjectType;
typedef std::vector<ObjectPtr>::iterator ObjectIterator;