//
//  String.cpp
//
//  Created by DiCode77.
//


#include "String.hpp"

void uString::init(){
    this->u_capacity = STR_CAPACITY;
    this->u_size = 0;
    this->arr = nullptr;
    
    createNewArr(this->u_capacity +1);
}

ulong_t uString::getStrLen(const char *str) const{
    ulong_t size = 0;
    while (str[size] != '\0') size++;
    return size;
}

void uString::resizeCapacity(ulong_t size){
    if (this->u_capacity < size){
        while (this->u_capacity < size){
            this->u_capacity *= 2;
        }
    }
}

void uString::createNewArr(ulong_t size){
    if (this->arr == nullptr){
        this->arr = new char[size]{};
    }
}

void uString::resizeNewArr(ulong_t size){
    if (this->arr == nullptr){
        this->arr = new char[size]{};
    }
    else{
        delete [] this->arr;
        this->arr = nullptr;
        this->arr = new char[size]{};
    }
}

void uString::copyStrToArr(const char *str, char *arr, const ulong_t size){
    if (!(str && arr && size)){
        return;
    }
    else{
        for (ulong_t i = 0; i < size; i++){
            arr[i] = str[i];
        }
    }
}

void uString::copyRevertStrToArr(const char *str, char *arr_, const ulong_t size){
    if (!(str && arr_ && size)){
        return;
    }
    else{
        for (long i = size; i > -1; i--){
            arr_[size - i] = str[i];
        }
        arr_[this->u_size] = '\0';
    }
}

void uString::copyStrToArrIndex(ulong_t index, const char *str, char *arr, ulong_t size){
    if (!(str && arr && size)){
        return;
    }
    
    for (ulong_t i = index; i < size; i++){
        arr[i] = str[i - index];
    }
}

void uString::toClear(ulong_t range){
    for (ulong_t i = 0; i < range; i++){
        this->arr[i] = '\0';
    }
}

ulong_t uString::sumANCI(const char *arr_, ulong_t size_) const{
    ulong_t sum = 0;
    for (ulong_t i = 0; i < size_; i++){
        sum += arr_[i];
    }
    return sum;
}

bool uString::compareSymbols(const char *arr, ulong_t size, const char *arr_, ulong_t size_) const{
    if (size != size_){
        return false;
    }
    else{
        for (ulong_t i = 0; i < size; i++){
            if (arr[i] != arr_[i])
                return false;
        }
    }
    return true;
}

void uString::addStrToArr(const char *str, ulong_t size){
    if ((this->u_size + size) > this->u_capacity){
        char *arr_ = new char[this->u_capacity +1]{};
        copyStrToArr(this->arr, arr_, this->u_size +1);
        
        resizeCapacity(this->u_size + size);
        resizeNewArr(this->u_capacity +1);
        
        copyStrToArr(arr_, this->arr, this->u_size +1);
        copyStrToArrIndex(this->u_size, str, this->arr, (this->u_size + size) +1);
        
        this->u_size = this->u_size + size;
        
        delete [] arr_;
    }
    else if (this->u_capacity >= (this->u_size + size)){
        copyStrToArrIndex(this->u_size, str, this->arr, (this->u_size + size) +1);
        this->u_size = this->u_size + size;
    }
}

void uString::addStrToArrExp(const char *str, ulong_t size, const short cout) noexcept{
    if ((this->u_size + size) > this->u_capacity){
        resizeCapacity(this->u_size + size);
        
        char *arr_ = new char[this->u_capacity +1]{};

        copyStrToArr(this->arr, arr_, this->u_size +1);
        copyStrToArrIndex(this->u_size, str, arr_, (this->u_size + size) +cout);
        
        this->u_size = this->u_size + size;
        
        if (cout == 0)
            arr_[this->u_size] = '\0';
        
        delete [] this->arr;
        this->arr = arr_;
    }
    else if (this->u_capacity >= (this->u_size + size)){
        copyStrToArrIndex(this->u_size, str, this->arr, (this->u_size + size) +cout);
        this->u_size = this->u_size + size;
        
        if (cout == 0)
            this->arr[this->u_size] = '\0';
    }
}

void uString::overwrite(const char *ext_arr, const ulong_t ext_size, const ulong_t ext_capacity){
    if (ext_capacity > this->u_capacity){
        this->u_capacity = ext_capacity;
        resizeNewArr(this->u_capacity +1);
    }
    else if (ext_capacity <= this->u_capacity){
        toClear(this->u_size +1);
    }
    
    this->u_size = ext_size;
    copyStrToArr(ext_arr, this->arr, ext_size +1);
}

uString::~uString(){
    delete [] this->arr;
}

uString::uString(){
    init();
}

uString::uString(const char *str) : uString(){
    if (str == nullptr){
        return;
    }
    else{
        this->u_size = getStrLen(str);
        if (this->u_size){
            if (this->u_capacity < this->u_size){
                resizeCapacity(this->u_size);
                resizeNewArr(this->u_capacity +1);
            }
            copyStrToArr(str, this->arr, this->u_size +1);
        }
        else{
            return;
        }
    }
}


uString::uString(const uString &str) : uString(){
    this->u_size = str.u_size;
    this->u_capacity = str.u_capacity;
    createNewArr(this->u_capacity +1);
    copyStrToArr(str.arr, this->arr, str.u_size +1);
}

const char *uString::c_str() const{
    return ((this->arr != nullptr) ? this->arr : STR_NULL);
}

uString uString::s_str() const{
    return ((this->arr != nullptr) ? *this : STR_NULL);
}

std::string uString::std_str() const{
    return std::string((this->arr != nullptr) ? this->arr : STR_NULL);
}

const ulong_t uString::size() const{
    return this->u_size;
}

const ulong_t uString::capacity() const{
    return this->u_capacity;
}

const bool uString::isEmpty(){
    return this->u_size;
}

const bool uString::isNull(){
    return this->arr == nullptr;
}

void uString::print(){
    if (this->u_size)
    write(true, this->arr, this->u_size);
}

void uString::printn(){
    if (this->u_size){
        write(true, this->arr, this->u_size);
        write(true, "\n", 1);
    }
}

void uString::reserve(const ulong_t size){
    if (STR_CAPACITY < size){
        resizeCapacity(size);
        char *arr_ = new char [this->u_capacity +1]{};
        copyStrToArr(this->arr, arr_, this->u_size +1);
        resizeNewArr(this->u_capacity +1);
        delete [] this->arr;
        this->arr = arr_;
    }
}

bool uString::strcmp(const uString &in1, const uString &in2){
 //   return (in1.sumANCI(in1.arr, in1.u_size) == in2.sumANCI(in2.arr, in2.u_size));
    return compareSymbols(in1.arr, in1.u_size, in2.arr, in2.u_size);
}

void uString::clear(){
    toClear(this->u_size);
    this->u_size = 0;
}

void uString::set(const uString &ext){
    overwrite(ext.arr, ext.u_size, ext.u_capacity);
}

void uString::append(const uString &ext){
    addStrToArrExp(ext.arr, ext.u_size, ONE);
}

void uString::append(const char ext){
    const int symbol = 1;
    char ch_[2]{ext, '\0'};
    
    addStrToArrExp(ch_, symbol, ONE);
}

void uString::append(const ulong_t size, const uString &ext){
    for (ulong_t i = 0; i < size; i++){
        addStrToArrExp(ext.arr, ext.u_size, ONE);
    }
}

void uString::append(const ulong_t size, const char ext){
    const int symbol = 1;
    char ch_[2]{ext, '\0'};
    
    for (ulong_t i = 0; i < size; i++){
        addStrToArrExp(ch_, symbol, ONE);
    }
}

void uString::append(const uString &ext, const ulong_t cout){
    addStrToArrExp(ext.arr, ((cout > ext.u_size) ? ext.u_size : cout), ZERO);
}

void uString::append(const uString &ext, const ulong_t begin, const ulong_t cout){
    const ulong_t remained = ext.u_size - ((begin < ext.u_size) ? begin : ext.u_size);
    
    if (begin < ext.u_size){
        addStrToArrExp(&ext.arr[begin], ((cout <= remained) ? cout : remained), ZERO);
    }
}

void uString::revert(){
    if (this->u_size){
        char *arr_ = new char[this->u_capacity +1]{};
        copyRevertStrToArr(this->arr, arr_, this->u_size -1);
        
        delete [] this->arr;
        this->arr = nullptr;
        this->arr = arr_;
    }
}

uString uString::concatenate(const uString &in1, const uString &in2){
    return (in1 + in2);
}

uString::iterator uString::begin(){
    return this->arr;
}

uString::iterator uString::end(){
    return &this->arr[u_size];
}

uString::const_iterator uString::cbegin(){
    return this->arr;
}

uString::const_iterator uString::cend(){
    return &this->arr[u_size];
}

uString::operator const char *(){
    return ((this->arr != nullptr) ? this->arr : STR_NULL);
}

uString &uString::operator= (const uString &ext){
    overwrite(ext.arr, ext.u_size, ext.u_capacity);
    return *this;
}

uString &uString::operator= (const char ext){
    this->u_size = 1;
    
    resizeCapacity(this->u_size);
    resizeNewArr(this->u_capacity +1);
    
    char arr_[2]{ext, '\0'};
    
    copyStrToArr(arr_, this->arr, getStrLen(arr_) +1);
    
    return *this;
}

uString &uString::operator+= (const uString &ext){
    addStrToArrExp(ext.arr, ext.u_size, ONE);
    return *this;
}

uString &uString::operator+= (const char ext){
    const int symbol = 1;
    char ch_[2]{ext, '\0'};
    
    addStrToArrExp(ch_, symbol, ONE);
    return *this;
}

uString uString::operator+ (const char ext){
    uString str = this->arr;
    str.append(ext);
    
    return str;
}

const bool uString::operator== (const char *ext) const{
    return (sumANCI(this->arr, this->u_size) == sumANCI(ext, getStrLen(ext)));
}

const bool uString::operator== (const uString &ext) const{
   // return (sumANCI(this->arr, this->u_size) == sumANCI(ext.arr, ext.u_size));
    return compareSymbols(this->arr, this->u_size, ext.arr, ext.u_size);
}

const bool uString::operator!= (const uString &ext) const{
   // return (sumANCI(this->arr, this->u_size) != sumANCI(ext.arr, ext.u_size));
    return !compareSymbols(this->arr, this->u_size, ext.arr, ext.u_size);
}

char &uString::operator[] (const ulong_t index) const{
    return this->arr[index];
}

std::ostream &operator<< (std::ostream &ost, const uString &ext){
    return ((ext.arr == nullptr) ? ost << STR_NULL : ost << ext.arr);
}

uString operator+ (const uString &in1, const uString &in2){
    uString str = in1;
    str.append(in2);
    return str;
}
