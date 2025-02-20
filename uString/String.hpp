//
//  String.hpp
//
//  Created by DiCode77.
//

#ifndef String_hpp
#define String_hpp

#if defined(__APPLE__) || defined(_WIN32)
#include <ostream>
#include <string>
#include <ostream>

#elif defined(ARDUINO)
#include <Arduino.h>
#include <limits.h>

#endif

#define STR_CAPACITY 35
#define VERSION_STRING "0.1.1"
#define STR_NULL "\0"
#define one 1
#define null 0

#if defined(__APPLE__) || defined(_WIN32)
using ulong_t    = unsigned long;
using c_ulong_t  = const unsigned long;
#define ULONG_T_MAX ULONG_MAX

#elif defined(ARDUINO)
using ulong_t    = unsigned int;
using c_ulong_t  = const unsigned int;
#define ULONG_T_MAX UINT_MAX

#endif

using c_char_p_t = const char*;
using char_p_t   = char*;
using char_pp_t  = char**;
using c_char_t   = const char;
using c_char_i_t = const char[];

class uString{
    ulong_t u_capacity;
    ulong_t u_size;
    char_p_t arr;
public:
    using iterator       = char_p_t;
    using const_iterator = c_char_p_t;
    
public:
    
   ~uString();
    uString();
    uString(c_char_p_t);
    uString(const uString&);

    c_char_p_t c_str() const;
    uString s_str() const;
#if defined(__APPLE__) || defined(_WIN32)
    std::string std_str() const;
#endif

    
    c_ulong_t size() const;
    c_ulong_t capacity() const;
    const bool isEmpty();
    const bool isNull();
    
    void print();
    void printn();
    void reserve(c_ulong_t);
    
    bool strcmp(const uString&);
    bool strcmp(const uString&, const uString&);
    
    void clear();
    void clear(ulong_t);
    void clear(ulong_t, ulong_t);
    
    void set(const uString&);
    void append(const uString&);
    void append(c_char_i_t);
    void append(c_char_t);
    void append(const ulong_t, const uString&);
    void append(const ulong_t, c_char_t);
    void append(const uString&, c_ulong_t);
    void append(const uString&, c_ulong_t, c_ulong_t);
    
    void insert(const uString&);
    void insert(c_ulong_t, const uString&);
    void insert(c_ulong_t, c_char_i_t);
    
    void revert();
    void ascii(c_char_t);
    
    uString toString(const int num);
    uString toString(const unsigned num);
    uString toString(const long num);
    uString toString(const long long num);
    uString toString(const unsigned long num);
    uString toString(const unsigned long long num);
    uString toString(const double num);
    uString toString(const char num);
    
    ulong_t toInt();
    double toDouble();
    char at(ulong_t at);
    void trim();
    void trimIs(char_p_t, int);
    
    void replace(c_ulong_t, c_ulong_t, uString);
    ulong_t find(const uString&);
    ulong_t rfind(const uString&);
    
    uString concatenate(const uString&, const uString&);
    
    iterator begin();
    iterator end();
    const_iterator cbegin();
    const_iterator cend();
    
    operator c_char_p_t();
    uString &operator= (const uString&);
    uString &operator= (c_char_i_t);
    uString &operator= (c_char_t);
    uString &operator+= (const uString&);
    uString &operator+= (c_char_i_t);
    uString &operator+= (c_char_t);
    uString operator+ (c_char_t);
    
    const bool operator== (c_char_p_t) const;
    const bool operator== (const uString&) const;
    const bool operator!= (const uString&) const;
    char &operator[] (c_ulong_t) const;
    
#if defined(__APPLE__) || defined(_WIN32)
    friend std::ostream &operator<< (std::ostream&, const uString&);
#endif
    friend uString operator+ (const uString&, const uString&);
    friend uString operator+ ( uString&, c_char_i_t);
    
    friend uString operator+ (c_char_i_t, uString&);
    
    
private:
    void init();
    ulong_t getStrLen(c_char_p_t) const; // визначає розмір рядка
    void resizeCapacity(ulong_t); // перевизначає довжину капасіті
    char_p_t createNewArr(ulong_t); // створює новий масив
    char_p_t resizeNewArr(char_pp_t, ulong_t); // перевизначає довжину масиву
    void copyStrToArr(c_char_p_t, char_p_t, c_ulong_t); // записує інформацію в масив із 0 елементу
    void copyRevertStrToArr(c_char_p_t, char_p_t, c_ulong_t); // переставляємо символи зворотньо, працює тільки з ASCII.
    void copyStrToArrIndex(ulong_t, c_char_p_t, char_p_t, c_ulong_t); // копіюємо рядок із заданими координатами першого масиву
    void copyStrIndexToArrIndex(ulong_t, c_char_p_t, char_p_t, c_ulong_t, c_ulong_t); // копіюємо рядок із заданими координатами першого масиву та другого
    void copyStrToArrIterator(iterator, iterator, char_p_t, c_ulong_t pos = 0);
    void toClear(ulong_t, ulong_t); // очищає масив
    ulong_t sumANCI(c_char_p_t, ulong_t) const; // рахує суму всіх символів
    bool compareSymbols(c_char_p_t, ulong_t, c_char_p_t, ulong_t) const; // рахує суму всіх символів
    void addStrToArrExp(c_char_p_t, ulong_t, const short) noexcept; // добавляємо новий рядок до існуючого рядка
    void addStrToArrInsert(c_char_p_t, ulong_t);
    void overwrite(c_char_p_t, c_ulong_t, c_ulong_t); // перезаписуємо рядок
    void deleteAndTransfer(char_pp_t, char_pp_t);
    ulong_t find_(const uString&); // робимо пошук рядка з нульового символу
    ulong_t rfind_(const uString&); // робимо пошук рядка з останнього символу
    bool convertNumToStr(char_p_t, const int, c_char_p_t, const void*); // конвертуємо числа в рядок
    void replace_(c_ulong_t, c_ulong_t, c_char_p_t, c_ulong_t);
};

#endif /* String_hpp */


