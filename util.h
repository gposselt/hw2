#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{

    std::set<T> intersection{};

    for (typename std::set<T>::iterator iter1 = s1.begin(); iter1 != s1.end(); ++iter1){
        if (s2.find(*iter1) != s2.end()) {
            intersection.insert(*iter1);
        }
    }

    return intersection;

}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{

    std::set<T> returnSet = s1;

    for (typename std::set<T>::iterator it = s2.begin(); it != s2.end(); ++it) {
        s1.insert(*it);
    }

    return s1;

}

//push range into queue(From stackoverflow)
template <typename Iter, typename Q>
void push_range(Q & q, Iter begin, Iter end)
{
    for ( ; begin != end; ++begin)
        q.push(*begin);
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
