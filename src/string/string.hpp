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

size_t strlcpy(char *dst, const char *src, size_t destination_size);

std::string format(const std::string format_string, ...);
std::string slice(std::string input_string, int start_index, int end_index = INT_MAX, int step = 1);

// split string based on a delimiter string
// supports multi-character delimiter
// returns a vector of substrings after split
std::vector<std::string> split(std::string input_string, std::string delimiter,
                               std::vector<std::string> *result = new std::vector<std::string>());

// join a vector of strings into a single string
std::string join(std::vector<std::string> input, std::string connector = "");

// Check if string startswith some character
bool starts_with(std::string input_string, char c, bool ignore_case = false);

// Check if string startswith some substring
bool starts_with(std::string input_string, std::string starter, bool ignore_case = false);

// Check if string endswith character
bool ends_with(std::string input_string, char c, bool ignore_case = false);

// String contains
bool contains(std::string input, std::string search_string, bool ignore_case = false);

// Count number of times some search_string appears in input_string
size_t count(std::string input_string, std::string search_string, bool ignore_case = false);

// repeat input string for count number of times, optionally with a connector string
std::string repeat(std::string input_string, int count_value, std::string connector = "");

// returns copy of input string that is all upper case
std::string upper(std::string input_string);

// returns copy of input string that is all lower case
std::string lower(std::string input_string);

// find and replace substring in input string, optionally for a limited number of times
// by default, every occurrence of find_string is replaced by replace_string
std::string replace(std::string input_string, std::string find_string,
                    std::string replace_string, int replace_count = -1);

// bulk find and replace sub-string in input string using translation table
std::string translate(std::string input_string,
                      std::map<std::string, std::string> translation_table);

// trim white spaces from the left end of an input string
std::string ltrim(std::string input_string);

// trim white spaces from right end of an input string
std::string rtrim(std::string input_string);

// trim white spaces from either end of an input string
std::string trim(std::string input_string);

// Returns true if the two input strings are equal
bool equal(std::string lhs, std::string rhs);

// generic find function
// if sub-string is found, returns the index
// if sub-string is not found, returns std::string::npos
size_t find(std::string input_string, std::string search_string);

// finds first occurrence of sub-string in input string
size_t find_first(std::string input_string, std::string search_string);

// finds last occurrence of sub-string in input string
size_t find_last(std::string input_string, std::string search_string);

// performs std regex search and returns a vector of matched results
std::vector<std::string> find_regex(std::string input_string, std::string regex_string);

} // namespace walnut