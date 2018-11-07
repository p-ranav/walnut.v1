#pragma once
#include <object.hpp>
#include <character_object.hpp>
#include <null_object.hpp>
#include <utf8.hpp>
#include <memory>

namespace walnut
{

struct StringObject : Object
{
  std::vector<ObjectPtr> buffer;

  typedef std::vector<ObjectPtr>::iterator ObjectIterator;
  ObjectIterator iterator;

  explicit StringObject(StringConstRef value) : Object(STRING, true, true)
  {
    String value_string = value;
    size_t index = 0;
    while (index < value_string.length())
    {
      String current_character = "";
      int length = u8_seqlen(&(value_string[index]));

      for (int i = 0; i < length; i++, index++)
        current_character += value_string[index];

      CharacterObjectPtr character = std::make_shared<CharacterObject>(current_character);
      buffer.push_back(character);
    }
    iterator = buffer.begin();
  }

  ObjectPtr Copy() override
  {
    return std::make_shared<StringObject>(Value());
  }

  String Value()
  {
    String result = "";
    for (auto &object : buffer)
    {
      CharacterObjectPtr character = std::dynamic_pointer_cast<CharacterObject>(object);
      result += character->value;
    }
    return result;
  }

  size_t Length()
  {
    return buffer.size();
  }

  void IterableInit() override
  {
    iterator = buffer.begin();
  }

  ObjectIterator IterableNext() override
  {
    if (iterator != buffer.end())
      iterator = iterator + 1;
    return iterator;
  }

  ObjectPtr IterableCurrentValue() override
  {
    if (iterator != buffer.end())
      return *(iterator);
    else
      return std::make_shared<NullObject>();
  }

  std::vector<ObjectPtr>::iterator IterableEnd() override
  {
    return buffer.end();
  }

  void IterableAppend(ObjectPtr value) override
  {
    buffer.push_back(value);
  }

  size_t IterableSize() override
  {
    return buffer.size();
  }

  String Inspect() override
  {
    String result = "\"";
    for (auto &character : buffer)
    {
      result += character->Inspect();
    }
    result += "\"";
    return result;
  }
};

typedef std::shared_ptr<StringObject> StringObjectPtr;

} // namespace walnut