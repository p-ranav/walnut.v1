#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <climits>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <stdio.h>
#include <stdarg.h>
#include <cctype>
#include <regex>

namespace walnut
{

namespace string
{

typedef std::string String;
typedef std::string &StringRef;
typedef const std::string StringConst;
typedef const std::string &StringConstRef;

size_t Copy(char *dst, const char *src, size_t destination_size);

String Format(StringConstRef format_string, ...);
String Slice(StringConstRef input_string, int start_index, int end_index = INT_MAX, int step = 1);

// split string based on a delimiter string
// supports multi-character delimiter
// returns a vector of substrings after split
std::vector<String> Split(StringConstRef input_string, StringConstRef delimiter,
                          std::vector<String> *result = new std::vector<String>());

// join a vector of strings into a single string
String Join(const std::vector<String> &input, StringConstRef connector = "");

// Check if string startswith some character
bool StartsWith(StringConstRef input_string, char c, bool ignore_case = false);

// Check if string startswith some substring
bool StartsWith(StringConstRef input_string, StringConstRef starter, bool ignore_case = false);

// Check if string endswith character
bool EndsWith(StringConstRef input_string, char c, bool ignore_case = false);

// String contains
bool Contains(String input, String search_string, bool ignore_case = false);

// Count number of times some search_string appears in input_string
size_t Count(String input_string, String search_string, bool ignore_case = false);

// repeat input string for count number of times, optionally with a connector string
String Repeat(StringConstRef input_string, int count_value, StringConstRef connector = "");

// returns copy of input string that is all upper case
String Upper(StringConstRef input_string);

// returns copy of input string that is all lower case
String Lower(StringConstRef input_string);

// find and replace substring in input string, optionally for a limited number of times
// by default, every occurrence of find_string is replaced by replace_string
String Replace(StringConstRef input_string, StringConstRef find_string,
               StringConstRef replace_string, int replace_count = -1);

// bulk find and replace sub-string in input string using translation table
String Translate(StringConstRef input_string,
                 const std::map<String, String> &translation_table);

// trim white spaces from the left end of an input string
String TrimLeft(StringConstRef input_string);

// trim white spaces from right end of an input string
String TrimRight(StringConstRef input_string);

// trim white spaces from either end of an input string
String Trim(StringConstRef input_string);

// Returns true if the two input strings are equal
bool Equal(StringConstRef lhs, StringConstRef rhs);

// generic find function
// if sub-string is found, returns the index
// if sub-string is not found, returns String::npos
size_t Find(StringConstRef input_string, StringConstRef search_string);

// finds first occurrence of sub-string in input string
size_t FindFirst(StringConstRef input_string, StringConstRef search_string);

// finds last occurrence of sub-string in input string
size_t FindLast(StringConstRef input_string, StringConstRef search_string);

// performs std regex search and returns a vector of matched results
std::vector<String> FindRegex(StringConstRef input_string, StringConstRef regex_string);

} // namespace string

} // namespace walnut