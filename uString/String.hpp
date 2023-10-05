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

class uString{
    unsigned u_capacity;
    unsigned u_size;
    char *arr;
public:
    using iterator = char*;
    using const_iterator = const char*;
    
public:
    
   ~uString();
    uString();
    uString(const char*);
    uString(const uString&);
    
    const char *c_str();
    uString s_str();
    std::string std_str();
    
    
    const unsigned size();
    const unsigned capacity();
    const bool isEmpty();
    const bool isNull();
    
    void print();
    void printn();
    void reserve(const unsigned);
    
    bool strcmp(const uString&, const uString&);
    
    void clear();
    void set(const uString&);
    void append(const uString&);
    void append(const char);
    
    uString concatenate(const uString&, const uString&);
    
    iterator begin();
    iterator end();
    const_iterator cbegin();
    const_iterator cend();
    
    operator const char *();
    uString &operator= (const uString&);
    uString &operator= (const char);
    uString &operator+= (const uString&);
    uString operator+ (const char);
    
    const bool operator== (const char*) const;
    const bool operator== (const uString&) const;
    const bool operator!= (const uString&) const;
    char &operator[] (const unsigned) const;
    
    friend std::ostream &operator<< (std::ostream&, const uString&);
    friend uString operator+ (const uString&, const uString&);
    
private:
    void init();
    unsigned getStrLen(const char*) const; // визначає розмір рядка
    void resizeCapacity(unsigned); // перевизначає довжину капасіті
    void createNewArr(unsigned); // створює новий масив
    void resizeNewArr(unsigned); // перевизначає довжину масиву
    void copyStrToArr(const char*, char*, const unsigned); // записує інформацію в масив із 0 елементу
    void copyStrToArrIndex(unsigned, const char*, char*, unsigned);
    void toClear(unsigned); // очищає масив
    unsigned sumANCI(const char*, unsigned) const; // рахує суму всіх символів
    bool compareSymbols(const char*, unsigned, const char*, unsigned) const; // рахує суму всіх символів
    void addStrToArr(const char*, unsigned); // добавляємо новий рядок до існуючого рядка
    void addStrToArrExp(const char*, unsigned) noexcept; // добавляємо новий рядок до існуючого рядка
    void overwrite(const char*, const unsigned, const unsigned); // перезаписуємо рядок
};

#endif /* String_hpp */


