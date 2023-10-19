//
//  String.cpp
//
//  Created by DiCode77.
//


#include "String.hpp"

void uString::init(){
    this->u_capacity = STR_CAPACITY;
    this->u_size = null;
    this->arr = nullptr;
    this->arr = createNewArr(this->u_capacity +1);
}

ulong_t uString::getStrLen(c_char_p_t str) const{
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

char *uString::createNewArr(ulong_t size){
    return new char [size]{};
}

char *uString::resizeNewArr(char_pp_t arr_, ulong_t size){
    if (*arr_ == nullptr){
        return new char[size]{};
    }
    else{
        delete [] *arr_;
        *arr_ = nullptr;
        return new char[size]{};
    }
}

void uString::copyStrToArr(c_char_p_t str, char_p_t arr, c_ulong_t size){
    if (!(str && arr && size)){
        return;
    }
    else{
        for (ulong_t i = 0; i < size; i++){
            arr[i] = str[i];
        }
    }
}

void uString::copyRevertStrToArr(c_char_p_t str, char_p_t arr_, c_ulong_t size){
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

void uString::copyStrToArrIndex(ulong_t index, c_char_p_t str, char_p_t arr, ulong_t size){
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

ulong_t uString::sumANCI(c_char_p_t arr_, ulong_t size_) const{
    ulong_t sum = 0;
    for (ulong_t i = 0; i < size_; i++){
        sum += arr_[i];
    }
    return sum;
}

bool uString::compareSymbols(c_char_p_t arr, ulong_t size, c_char_p_t arr_, ulong_t size_) const{
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


void uString::addStrToArrExp(c_char_p_t str, ulong_t size, const short cout) noexcept{
    if ((this->u_size + size) > this->u_capacity){
        resizeCapacity(this->u_size + size);
        
        char *arr_ = new char[this->u_capacity +1]{};

        copyStrToArr(this->arr, arr_, this->u_size +1);
        copyStrToArrIndex(this->u_size, str, arr_, (this->u_size + size) +cout);
        
        this->u_size = this->u_size + size;
        
        if (cout == 0)
            arr_[this->u_size] = '\0';
        
        deleteAndTransfer(&this->arr, &arr_);
    }
    else if (this->u_capacity >= (this->u_size + size)){
        copyStrToArrIndex(this->u_size, str, this->arr, (this->u_size + size) +cout);
        this->u_size = this->u_size + size;
        
        if (cout == 0)
            this->arr[this->u_size] = '\0';
    }
}

void uString::addStrToArrInsert(c_char_p_t str, ulong_t pos){
    if (str){
        ulong_t str_len = getStrLen(str);
        resizeCapacity(str_len + this->u_size);
        
        char_p_t arr_ = createNewArr(this->u_capacity +1);
        ((pos > this->u_size) ? (pos = str_len) : 0);
        ulong_t j(0), drop(0);
        for (ulong_t i = 0; i <= this->u_size +1; i++){
            if (i != pos){
                arr_[i + ((j != 0) ? j -1 : j)] = this->arr[i - drop];
            }
            else{
                for (; j < str_len; j++){
                    arr_[i + j] = str[j];
                }
                drop = one;
            }
        }
        this->u_size += str_len;
        deleteAndTransfer(&this->arr, &arr_);
    }
}

void uString::overwrite(c_char_p_t ext_arr, c_ulong_t ext_size, c_ulong_t ext_capacity){
    if (ext_capacity > this->u_capacity){
        this->u_capacity = ext_capacity;
        this->arr = resizeNewArr(&this->arr, this->u_capacity +1);
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

uString::uString(c_char_p_t str) : uString(){
    if (str == nullptr){
        return;
    }
    else{
        this->u_size = getStrLen(str);
        if (this->u_size){
            if (this->u_capacity < this->u_size){
                resizeCapacity(this->u_size);
                this->arr = resizeNewArr(&this->arr, this->u_capacity +1);
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
    this->arr = resizeNewArr(&this->arr, this->u_capacity +1);
    copyStrToArr(str.arr, this->arr, str.u_size +1);
}

c_char_p_t uString::c_str() const{
    return ((this->arr != nullptr) ? this->arr : STR_NULL);
}

uString uString::s_str() const{
    return ((this->arr != nullptr) ? *this : STR_NULL);
}

std::string uString::std_str() const{
    return std::string((this->arr != nullptr) ? this->arr : STR_NULL);
}

c_ulong_t uString::size() const{
    return this->u_size;
}

c_ulong_t uString::capacity() const{
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
        this->arr = resizeNewArr(&this->arr, this->u_capacity +1);
        deleteAndTransfer(&this->arr, &arr_);
    }
}

bool uString::strcmp(const uString &in1, const uString &in2){
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
    addStrToArrExp(ext.arr, ext.u_size, one);
}

void uString::append(c_char_t ext){
    const int symbol = 1;
    char ch_[2]{ext, '\0'};
    
    addStrToArrExp(ch_, symbol, one);
}

void uString::append(c_ulong_t size, const uString &ext){
    for (ulong_t i = 0; i < size; i++){
        addStrToArrExp(ext.arr, ext.u_size, one);
    }
}

void uString::append(c_ulong_t size, c_char_t ext){
    const int symbol = 1;
    char ch_[2]{ext, '\0'};
    
    for (ulong_t i = 0; i < size; i++){
        addStrToArrExp(ch_, symbol, one);
    }
}

void uString::append(const uString &ext, c_ulong_t cout){
    addStrToArrExp(ext.arr, ((cout > ext.u_size) ? ext.u_size : cout), null);
}

void uString::append(const uString &ext, c_ulong_t begin, c_ulong_t cout){
    const ulong_t remained = ext.u_size - ((begin < ext.u_size) ? begin : ext.u_size);
    
    if (begin < ext.u_size){
        addStrToArrExp(&ext.arr[begin], ((cout <= remained) ? cout : remained), null);
    }
}

void uString::insert(const uString &str){
    addStrToArrInsert(str.arr, null);
}

void uString::insert(c_ulong_t pos, const uString &str){
    addStrToArrInsert(str.arr, pos);
}

void uString::revert(){
    if (this->u_size){
        char *arr_ = new char[this->u_capacity +1]{};
        copyRevertStrToArr(this->arr, arr_, this->u_size -1);
        deleteAndTransfer(&this->arr, &arr_);
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

uString::operator c_char_p_t(){
    return ((this->arr != nullptr) ? this->arr : STR_NULL);
}

uString &uString::operator= (const uString &ext){
    overwrite(ext.arr, ext.u_size, ext.u_capacity);
    return *this;
}

uString &uString::operator= (c_char_t ext){
    char arr_[2] = {ext, '\0'};
    overwrite(arr_, one, this->u_capacity);
    return *this;
}

uString &uString::operator+= (const uString &ext){
    addStrToArrExp(ext.arr, ext.u_size, one);
    return *this;
}

uString &uString::operator+= (const char ext){
    const int symbol = 1;
    char ch_[2]{ext, '\0'};
    
    addStrToArrExp(ch_, symbol, one);
    return *this;
}

uString uString::operator+ (const char ext){
    uString str = this->arr;
    str.append(ext);
    
    return str;
}

const bool uString::operator== (c_char_p_t ext) const{
    return (sumANCI(this->arr, this->u_size) == sumANCI(ext, getStrLen(ext)));
}

const bool uString::operator== (const uString &ext) const{
    return compareSymbols(this->arr, this->u_size, ext.arr, ext.u_size);
}

const bool uString::operator!= (const uString &ext) const{
    return !compareSymbols(this->arr, this->u_size, ext.arr, ext.u_size);
}

char &uString::operator[] (c_ulong_t index) const{
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

void uString::deleteAndTransfer(char_pp_t arr, char_pp_t arr_){
    if (arr_){
        delete [] *arr;
        *arr = nullptr;
        *arr = *arr_;
    }
}
