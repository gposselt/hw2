#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords) {
    std::set<std::string> strings{};

    string lowerString = convToLower(rawWords);
    string trimmed = trim(lowerString);

    size_t i = 0;
    while (true) {
        if (trimmed.empty()) {
            break;
        }
        if (i == trimmed.length()) {
            strings.insert(trimmed);
            break;
        }

        if (!ispunct(trimmed[i]) && !isspace(trimmed[i])) {
            i++;
            continue;
        }

        if (i < 2) {
            trimmed = trim(trimmed.erase(0, i + 1));
            i = 0;
            continue;
        }

        std::string agh = trimmed.substr(0, i);
        agh = trim(agh);

        if (agh.length() > 2) {
            strings.insert(trim(agh));
        }


        trimmed = trim(trimmed.erase(0, i));
        i = 0;
        if (trimmed.empty()) {
            break;
        }
        i++;
    }


    return strings;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
