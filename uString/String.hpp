//
//  String.hpp
//
//  Created by DiCode77.
//

#ifndef String_hpp
#define String_hpp

#include <ostream>
#include <unistd.h>

#define STR_CAPACITY 35
#define VERSION_STRING "0.0.9"
#define STR_NULL "\0"
#define one 1
#define null 0

using ulong_t    = unsigned long;
using c_ulong_t  = const unsigned long;
using c_char_p_t = const char*;
using char_p_t   = char*;
using char_pp_t  = char**;
using c_char_t   = const char;

#define ULONG_T_MAX ULONG_MAX

class uString{
    ulong_t u_capacity;
    ulong_t u_size;
    char_p_t arr;
public:
    using iterator = char_p_t;
    using const_iterator = c_char_p_t;
    
public:
    
   ~uString();
    uString();
    uString(c_char_p_t);
    uString(const uString&);
    
    c_char_p_t c_str() const;
    uString s_str() const;
    std::string std_str() const;
    
    
    c_ulong_t size() const;
    c_ulong_t capacity() const;
    const bool isEmpty();
    const bool isNull();
    
    void print();
    void printn();
    void reserve(c_ulong_t);
    
    bool strcmp(const uString&, const uString&);
    
    void clear();
    void set(const uString&);
    void append(const uString&);
    void append(c_char_t);
    void append(const ulong_t, const uString&);
    void append(const ulong_t, c_char_t);
    void append(const uString&, c_ulong_t);
    void append(const uString&, c_ulong_t, c_ulong_t);
    
    void insert(const uString&);
    void insert(c_ulong_t, const uString&);
    
    void revert();
    
    uString concatenate(const uString&, const uString&);
    
    iterator begin();
    iterator end();
    const_iterator cbegin();
    const_iterator cend();
    
    operator c_char_p_t();
    uString &operator= (const uString&);
    uString &operator= (c_char_t);
    uString &operator+= (const uString&);
    uString &operator+= (c_char_t);
    uString operator+ (c_char_t);
    
    const bool operator== (c_char_p_t) const;
    const bool operator== (const uString&) const;
    const bool operator!= (const uString&) const;
    char &operator[] (c_ulong_t) const;
    
    friend std::ostream &operator<< (std::ostream&, const uString&);
    friend uString operator+ (const uString&, const uString&);
    
private:
    void init();
    ulong_t getStrLen(c_char_p_t) const; // визначає розмір рядка
    void resizeCapacity(ulong_t); // перевизначає довжину капасіті
    char_p_t createNewArr(ulong_t); // створює новий масив
    char_p_t resizeNewArr(char_pp_t, ulong_t); // перевизначає довжину масиву
    void copyStrToArr(c_char_p_t, char_p_t, c_ulong_t); // записує інформацію в масив із 0 елементу
    void copyRevertStrToArr(c_char_p_t, char_p_t, c_ulong_t); // переставляємо символи зворотньо, працює тільки з ASCII.
    void copyStrToArrIndex(ulong_t, c_char_p_t, char_p_t, ulong_t);
    void toClear(ulong_t); // очищає масив
    ulong_t sumANCI(c_char_p_t, ulong_t) const; // рахує суму всіх символів
    bool compareSymbols(c_char_p_t, ulong_t, c_char_p_t, ulong_t) const; // рахує суму всіх символів
    void addStrToArrExp(c_char_p_t, ulong_t, const short) noexcept; // добавляємо новий рядок до існуючого рядка
    void addStrToArrInsert(c_char_p_t, ulong_t);
    void overwrite(c_char_p_t, c_ulong_t, c_ulong_t); // перезаписуємо рядок
    void deleteAndTransfer(char_pp_t, char_pp_t);
};

#endif /* String_hpp */


