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
#define VERSION_STRING "0.0.8"
#define STR_NULL "\0"
#define ONE 1
#define ZERO 0

using ulong_t = unsigned long;

#define ULONG_T_MAX ULONG_MAX

class uString{
    ulong_t u_capacity;
    ulong_t u_size;
    char *arr;
public:
    using iterator = char*;
    using const_iterator = const char*;
    
public:
    
   ~uString();
    uString();
    uString(const char*);
    uString(const uString&);
    
    const char *c_str() const;
    uString s_str() const;
    std::string std_str() const;
    
    
    const ulong_t size() const;
    const ulong_t capacity() const;
    const bool isEmpty();
    const bool isNull();
    
    void print();
    void printn();
    void reserve(const ulong_t);
    
    bool strcmp(const uString&, const uString&);
    
    void clear();
    void set(const uString&);
    void append(const uString&);
    void append(const char);
    void append(const ulong_t, const uString&);
    void append(const ulong_t, const char);
    void append(const uString&, const ulong_t);
    void append(const uString&, const ulong_t, const ulong_t);
    
    void revert();
    
    uString concatenate(const uString&, const uString&);
    
    iterator begin();
    iterator end();
    const_iterator cbegin();
    const_iterator cend();
    
    operator const char *();
    uString &operator= (const uString&);
    uString &operator= (const char);
    uString &operator+= (const uString&);
    uString &operator+= (const char);
    uString operator+ (const char);
    
    const bool operator== (const char*) const;
    const bool operator== (const uString&) const;
    const bool operator!= (const uString&) const;
    char &operator[] (const ulong_t) const;
    
    friend std::ostream &operator<< (std::ostream&, const uString&);
    friend uString operator+ (const uString&, const uString&);
    
private:
    void init();
    ulong_t getStrLen(const char*) const; // визначає розмір рядка
    void resizeCapacity(ulong_t); // перевизначає довжину капасіті
    char *createNewArr(ulong_t); // створює новий масив
    char *resizeNewArr(char**, ulong_t); // перевизначає довжину масиву
    void copyStrToArr(const char*, char*, const ulong_t); // записує інформацію в масив із 0 елементу
    void copyRevertStrToArr(const char*, char*, const ulong_t); // переставляємо символи зворотньо, працює тільки з ASCII.
    void copyStrToArrIndex(ulong_t, const char*, char*, ulong_t);
    void toClear(ulong_t); // очищає масив
    ulong_t sumANCI(const char*, ulong_t) const; // рахує суму всіх символів
    bool compareSymbols(const char*, ulong_t, const char*, ulong_t) const; // рахує суму всіх символів
    void addStrToArrExp(const char*, ulong_t, const short) noexcept; // добавляємо новий рядок до існуючого рядка
    void overwrite(const char*, const ulong_t, const ulong_t); // перезаписуємо рядок
};

#endif /* String_hpp */


