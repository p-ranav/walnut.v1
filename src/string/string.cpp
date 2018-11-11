#include <string.hpp>

namespace walnut
{

  namespace string
  {

    // String operations
    size_t Copy(char *dst, const char *src, size_t destination_size)
    {
      size_t length = strlen(src);
      if (destination_size)
      {
        size_t bl = (length < destination_size - 1 ? length : destination_size - 1);
        ((char *)memcpy(dst, src, bl))[bl] = 0;
      }
      return length;
    }

    String Format(StringConst format_string, ...)
    {
      int n = ((int)format_string.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
      std::unique_ptr<char[]> formatted;
      va_list ap;
      while (1)
      {
        formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
        Copy(&formatted[0], format_string.c_str(), format_string.length());
        va_start(ap, format_string);
        int final_n = vsnprintf(&formatted[0], n, format_string.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
          n += abs(final_n - n + 1);
        else
          break;
      }
      return String(formatted.get());
    }

    // Python-style String slicing
    String Slice(StringConstRef input_string, int start_index, int end_index, int step)
    {
      String result;
      if (end_index == INT_MAX)
      { // if end index is default, i.e., till end of string
        if (start_index < 0)
        { // if start index is negative, then start start_index characters from end of string
          for (int i = static_cast<int>(input_string.size()) + start_index; i < static_cast<int>(input_string.size()); i = i + step)
          {
            result += input_string[i];
          }
        }
        else
        { // start_index is not negative; iterate from start_index till end of string
          for (int i = start_index; i < static_cast<int>(input_string.size()); i = i + step)
          {
            result += input_string[i];
          }
        }
      }
      else
      { // end_index is not String::npos
        if (end_index < 0)
        { // if end_index is negative, start from start_index and go till (end_of_string + end_index)
          for (int i = start_index; i < static_cast<int>(input_string.size()) + end_index; i = i + step)
          {
            result += input_string[i];
          }
        }
        else
        { // if end_index is not negative either, then this is the trivial case
          for (int i = start_index; i < end_index; i = i + step)
          {
            result += input_string[i];
          }
        }
      }
      return result;
    }

    // split string based on a delimiter string
    // supports multi-character delimiter
    // returns a vector of substrings after split
    std::vector<String> Split(StringConstRef input_string, StringConstRef delimiter, std::vector<String> *result)
    {
      String current_string(input_string);
      size_t delimiter_position = current_string.find(delimiter); // check if delimiter is in input string
      if (delimiter_position != String::npos)
      { // if delimiter position is not end_of_string
        size_t counter_position = 0;
        String split_string = current_string.substr(counter_position, delimiter_position);
        delimiter_position += delimiter.size();
        String split_remaining = current_string.erase(counter_position, delimiter_position);
        result->push_back(split_string);
        Split(split_remaining, delimiter, result);
      }
      else
      { // delimiter not in input string. Just add entire input string to result vector
        result->push_back(current_string);
      }
      return *result;
    }

    // Check if string startswith some character
    bool StartsWith(StringConstRef input_string, char c, bool ignore_case)
    {
      bool result = false;
      if (input_string.size() > 0)
      {
        char first_character = input_string[0];
        if (ignore_case)
        {
          first_character = toupper(first_character);
          c = toupper(c);
        }
        if (first_character == c)
          result = true;
      }
      return result;
    }

    // Check if string startswith some substring
    bool StartsWith(StringConstRef input_string, StringConstRef starter, bool ignore_case)
    {
      bool result = false;
      if (input_string.size() > 0 && input_string.size() > starter.size())
      {
        String input_copy = input_string;
        for (size_t i = 0; i < starter.size(); i++)
        {
          char input_character = input_string[i];
          char starter_character = starter[i];
          if (ignore_case)
          {
            input_character = toupper(input_character);
            starter_character = toupper(starter_character);
          }
          if (input_character == starter_character)
          {
            result = true;
            continue;
          }
          else
          {
            result = false;
            break;
          }
        }
      }
      return result;
    }

    // Check if string endswith character
    bool EndsWith(StringConstRef input_string, char c, bool ignore_case)
    {
      bool result = false;
      if (input_string.size() > 0)
      {
        char last_character = input_string[input_string.size() - 1];
        if (ignore_case)
        {
          last_character = toupper(last_character);
          c = toupper(c);
        }
        if (last_character == c)
          result = true;
      }
      return result;
    }

    // String contains
    bool Contains(String input, String search_string, bool ignore_case)
    {
      bool result = false;
      if (ignore_case)
      { // if case is to be ignored, convert both input and search string to all upper case
        std::transform(input.begin(), input.end(), input.begin(), ::toupper);
        std::transform(search_string.begin(), search_string.end(), search_string.begin(), ::toupper);
      }
      if (input.find(search_string) != String::npos)
      { // search using find algorithm
        result = true;
      }
      return result;
    }

    // Count number of times some search_string appears in input_string
    size_t Count(String input_string, String search_string, bool ignore_case)
    {
      size_t result = 0;
      if (Contains(input_string, search_string, ignore_case))
      {
        if (ignore_case)
        {
          std::transform(input_string.begin(), input_string.end(), input_string.begin(), ::toupper);
          std::transform(search_string.begin(), search_string.end(), search_string.begin(), ::toupper);
        }
        auto split_vector = Split(input_string, search_string);
        result = split_vector.size() - 1;
      }
      return result;
    }

    // repeat input string for count number of times, optionally with a connector string
    String Repeat(StringConstRef input_string, int count_value, StringConstRef connector)
    {
      String result = "";
      while (count_value > 0)
      {
        result += input_string + connector;
        count_value--;
      }
      return result;
    }

    // returns copy of input string that is all upper case
    String Upper(StringConstRef input_string)
    {
      String result;
      result.resize(input_string.size());
      std::transform(input_string.begin(), input_string.end(), result.begin(), ::toupper);
      return result;
    }

    // returns copy of input string that is all lower case
    String Lower(StringConstRef input_string)
    {
      String result;
      result.resize(input_string.size());
      std::transform(input_string.begin(), input_string.end(), result.begin(), ::tolower);
      return result;
    }

    // find and replace substring in input string, optionally for a limited number of times
    // by default, every occurrence of find_string is replaced by replace_string
    String Replace(StringConstRef input_string, StringConstRef find_string,
      StringConstRef replace_string, int replace_count)
    {
      String result = "";
      auto split_vector = Split(input_string, find_string);
      auto split_size = split_vector.size();
      auto max_replace_count = split_size - 1;
      if (replace_count == -1)
      {
        for (auto &s : split_vector)
        {
          if (max_replace_count > 0)
            result += s + replace_string;
          else
            result += s;
          max_replace_count--;
        }
      }
      else
      {
        for (auto &s : split_vector)
        {
          if (replace_count > 0)
          {
            if (max_replace_count > 0)
              result += s + replace_string;
            else
              result += s;
            max_replace_count--;
          }
          else
          {
            if (max_replace_count > 0)
              result += s + find_string;
            else
              result += s;
            max_replace_count--;
          }
          replace_count--;
        }
      }
      return result;
    }

    // join a vector of strings into a single string
    String Join(const std::vector<String>& input, StringConstRef connector)
    {
      String result;
      size_t max_connector_count = input.size() - 1;
      for (auto &s : input)
      {
        if (max_connector_count > 0)
          result += s + connector;
        else
          result += s;
        max_connector_count--;
      }
      return result;
    }

    // bulk find and replace sub-string in input string using translation table
    String Translate(StringConstRef input_string,
      const std::map<String, String>& translation_table)
    {
      String result = input_string;
      for (auto &pair : translation_table)
        result = Replace(result, pair.first, pair.second);
      return result;
    }

    // trim white spaces from the left end of an input string
    String TrimLeft(StringConstRef input_string)
    {
      String result = input_string;
      result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](int ch) {
        return !std::isspace(ch);
      }));
      return result;
    }

    // trim white spaces from right end of an input string
    String TrimRight(StringConstRef input_string)
    {
      String result = input_string;
      result.erase(std::find_if(result.rbegin(), result.rend(), [](int ch) {
        return !std::isspace(ch);
      })
        .base(),
        result.end());
      return result;
    }

    // trim white spaces from either end of an input string
    String Trim(StringConstRef input_string)
    {
      return TrimLeft(TrimRight(input_string));
    }

    // Returns true if the two input strings are equal
    bool Equal(StringConstRef lhs, StringConstRef rhs)
    {
      return (lhs.compare(rhs) == 0);
    }

    // generic find function
    // if sub-string is found, returns the index
    // if sub-string is not found, returns String::npos
    size_t Find(StringConstRef input_string, StringConstRef search_string)
    {
      return input_string.find(search_string);
    }

    // finds first occurrence of sub-string in input string
    size_t FindFirst(StringConstRef input_string, StringConstRef search_string)
    {
      return input_string.find_first_of(search_string);
    }

    // finds last occurrence of sub-string in input string
    size_t FindLast(StringConstRef input_string, StringConstRef search_string)
    {
      return input_string.find_last_of(search_string);
    }

    // performs std regex search and returns a vector of matched results
    std::vector<String> FindRegex(StringConstRef input_string, StringConstRef regex_string)
    {
      String current_string(input_string);
      std::vector<String> results;
      std::smatch match_result;
      while (std::regex_search(current_string, match_result, std::regex(regex_string)))
      {
        for (auto &m : match_result)
          results.push_back(m);
        current_string = match_result.suffix();
      }
      return results;
    }

  } // namespace string

} // namespace walnut