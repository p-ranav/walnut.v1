#include <string.hpp>
#include <evaluator.hpp>

namespace walnut
{

  ObjectPtr Evaluator::BuiltinFormat(std::vector<ObjectPtr> arguments)
  {
    if (arguments.size() == 1)
    {
      return arguments[0];
    }
    // String formatting
    else if (arguments.size() > 1 && arguments[0]->type == ObjectType::STRING)
    {
      StringObjectPtr format = std::dynamic_pointer_cast<StringObject>(arguments[0]);
      std::map<String, String> kwargs;

      for (auto& argument : arguments)
      {
        if (argument->type == ObjectType::KEY_VALUE_ARGUMENT)
        {
          KeyValueArgumentObjectPtr kvpair = std::dynamic_pointer_cast<KeyValueArgumentObject>(argument);
          if (kvpair->value->type == ObjectType::STRING)
          {
            StringObjectPtr string_end = std::dynamic_pointer_cast<StringObject>(kvpair->value);
            if (kwargs.find(kvpair->key->ToString()) != kwargs.end())
              kwargs[kvpair->key->ToString()] = string_end->Value();
            else
              kwargs.insert(std::make_pair(kvpair->key->ToString(), string_end->Value()));
          }
          else if (kvpair->value->type == ObjectType::CHARACTER)
          {
            CharacterObjectPtr character_end = std::dynamic_pointer_cast<CharacterObject>(kvpair->value);
            if (kwargs.find(kvpair->key->ToString()) != kwargs.end())
              kwargs[kvpair->key->ToString()] = character_end->Value();
            else
              kwargs.insert(std::make_pair(kvpair->key->ToString(), character_end->Value()));
          }
          else
          {
            if (kwargs.find(kvpair->key->ToString()) != kwargs.end())
              kwargs[kvpair->key->ToString()] = kvpair->value->Inspect();
            else
              kwargs.insert(std::make_pair(kvpair->key->ToString(), kvpair->value->Inspect()));
          }
        }
      }

      if (format)
      {
        String format_string = format->Value();

        // Positional arguments
        for (size_t i = 1; i < arguments.size(); i++)
        {
          if (arguments[i]->type == ObjectType::KEY_VALUE_ARGUMENT)
            continue;
          try
          {
            String search_string = "{" + std::to_string(i - 1) + "}";
            // TODO: catch exception in find and report error
            size_t search_index = format_string.find(search_string);
            std::string::iterator begin = format_string.begin() + search_index;
            std::string::iterator end = begin + search_string.length();
            if (begin != format_string.end())
            {
              if (arguments[i]->type != ObjectType::STRING)
              {
                format_string.replace(begin, end, arguments[i]->Inspect().c_str());
              }
              else
              {
                StringObjectPtr string_argument = std::dynamic_pointer_cast<StringObject>(arguments[i]);
                format_string.replace(begin, end, string_argument->Value());
              }
            }
          }
          catch (std::exception& e) {}
        }

        // Kwargs
        for (auto& pair : kwargs)
        {
          try
          {
            String search_string = "{" + pair.first + "}";
            size_t search_index = format_string.find(search_string);
            std::string::iterator begin = format_string.begin() + search_index;
            std::string::iterator end = begin + search_string.length();
            if (begin != format_string.end() && begin < format_string.end())
            {
              format_string.replace(begin, end, pair.second);
            }
          }
          catch (std::exception& e) {}
        }

        return std::make_shared<StringObject>(format_string);
      }
      else
      {
        // TODO: report error
      }
    }
    return std::make_shared<NullObject>();
  }

}