#pragma once
#include <identifier_node.hpp>
#include <object.hpp>
#include <memory>

namespace walnut
{

struct KeyValueArgumentObject : Object
{
  IdentifierNodePtr key;
  ObjectPtr value;
  explicit KeyValueArgumentObject(IdentifierNodePtr key, ObjectPtr value) : Object(KEY_VALUE_ARGUMENT, false, true),
                                                                            key(key),
                                                                            value(value) {}

  ObjectPtr Copy() override
  {
    return std::make_shared<KeyValueArgumentObject>(key, value);
  }

  String Inspect() override
  {
    return key->ToString() + " = " + value->Inspect();
  }
};

typedef std::shared_ptr<KeyValueArgumentObject> KeyValueArgumentObjectPtr;

} // namespace walnut