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
    return (char_p_t)std::memchr(str, '\0', ULONG_T_MAX) - str;
}

void uString::resizeCapacity(ulong_t size){
    if (this->u_capacity < size){
        while (this->u_capacity < size){
            this->u_capacity *= 2;
        }
    }
}

char *uString::createNewArr(ulong_t size){
    return new char [size];
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
        std::memcpy(arr, str, size);
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
    std::memcpy(arr + index, str, size - index);
}

void uString::copyStrIndexToArrIndex(ulong_t index, c_char_p_t str, char_p_t arr, c_ulong_t arr_index, c_ulong_t size){
    if (!(str && arr && size)){
        return;
    }
    
    for (ulong_t i = index; i < size; i++){
        arr[i] = str[(i - index) + arr_index];
    }
}

void uString::copyStrIndexToArrIndexV2(char_p_t arr_, char_p_t str, c_ulong_t index, c_ulong_t len, c_ulong_t size){
    c_ulong_t s = ((this->u_size >= index) ? ((this->u_size - index) > len) ? len : this->u_size - index : 0);
    std::memcpy(arr_ + (index + size), this->arr + (index + s), this->u_size - (index + s));
}

void uString::copyStrToArrIterator(iterator begin, iterator end, char_p_t arr, c_ulong_t pos){
    if (!(begin && end && arr)){
        return;
    }
    
    ulong_t val = 0;
    for (iterator i = begin; i < end; i++){
        arr[pos + val++] = *i;
    }
}

void uString::toClear(ulong_t beg, ulong_t range){
    std::memset(this->arr, '\0', this->u_size);
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
        
        char_p_t arr_ = createNewArr(this->u_capacity +1);

        copyStrToArr(this->arr, arr_, this->u_size +1);
        copyStrToArrIndex(this->u_size, str, arr_, this->u_size + size);
        
        this->u_size = this->u_size + size;
        
        if (cout == 0)
            arr_[this->u_size] = '\0';
        
        deleteAndTransfer(&this->arr, &arr_);
    }
    else if (this->u_capacity >= (this->u_size + size)){
        copyStrToArrIndex(this->u_size, str, this->arr, this->u_size + size);
        this->u_size = this->u_size + size;
        
        if (cout == 0)
            this->arr[this->u_size] = '\0';
    }
}

void uString::addStrToArrInsert(c_char_p_t str, ulong_t pos){
    if (str && pos <= this->u_size){
        ulong_t str_len = getStrLen(str);
        resizeCapacity(str_len + this->u_size);
        
        char_p_t arr_ = createNewArr(this->u_capacity +1);
        ((pos > this->u_size) ? (pos = str_len) : 0);
        
        std::memcpy(arr_, this->arr, pos);
        std::memcpy(arr_ + pos, str, str_len);
        std::memcpy(arr_ + pos + str_len, this->arr + pos, this->u_size - pos);
        
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
        toClear(null, this->u_size +1);
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

#if defined(__APPLE__) || defined(_WIN32)
std::string uString::std_str() const{
    return std::string((this->arr != nullptr) ? this->arr : STR_NULL);
}
#endif

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
#if defined(__APPLE__) || defined(_WIN32)
        printf("%s", this->arr);
#elif defined(ARDUINO)
    Serial.print(this->arr);
#endif
}

void uString::printn(){
    if (this->u_size){
#if defined(__APPLE__) || defined(_WIN32)
        printf("%s\n", this->arr);
#elif defined(ARDUINO)
        Serial.println(this->arr);
#endif
    }
}

void uString::reserve(c_ulong_t size){
    if (STR_CAPACITY < size){
        resizeCapacity(size);
        char_p_t arr_ = createNewArr(this->u_capacity +1);
        copyStrToArr(this->arr, arr_, this->u_size +1);
        this->arr = resizeNewArr(&this->arr, this->u_capacity +1);
        deleteAndTransfer(&this->arr, &arr_);
    }
}

bool uString::strcmp(const uString &in){
    return compareSymbols(this->arr, this->u_size, in.arr, in.u_size);
}

bool uString::strcmp(const uString &in1, const uString &in2){
    return compareSymbols(in1.arr, in1.u_size, in2.arr, in2.u_size);
}

void uString::clear(){
    toClear(null, this->u_size);
    this->u_size = 0;
}

void uString::clear(ulong_t begin){
    toClear(begin, this->u_size);
    this->u_size = begin;
}

void uString::clear(ulong_t left, ulong_t right){
    if (left < this->u_size && right){
        char_p_t arr_ = createNewArr(this->u_capacity +1);
        ulong_t size = 0;
        
        copyStrToArrIterator(begin(), (this->arr + left), arr_);
        copyStrToArrIterator(this->arr + (right + left), end(), arr_, left);
        deleteAndTransfer(&this->arr, &arr_);
        
        ((this->u_size > left) ? size += left : 0);
        (((left + right) < this->u_size) ? size += this->u_size - (left + right) : 0);
        
        this->u_size = size;
    }
    
}

void uString::set(const uString &ext){
    overwrite(ext.arr, ext.u_size, ext.u_capacity);
}

void uString::append(const uString &ext){
    addStrToArrExp(ext.arr, ext.u_size, one);
}

void uString::append(c_char_i_t arr){
    addStrToArrExp(arr, getStrLen(arr), one);
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

void uString::insert(c_ulong_t pos, c_char_i_t str){
    addStrToArrInsert(str, pos);
}

void uString::revert(){
    if (this->u_size){
        char_p_t arr_ = createNewArr(this->u_capacity +1);
        copyRevertStrToArr(this->arr, arr_, this->u_size -1);
        deleteAndTransfer(&this->arr, &arr_);
    }
}

void uString::ascii(c_char_t ascii){
    char ch[2] = {ascii, '\0'};
    overwrite(ch, 1, this->u_capacity);
}

uString uString::toString(const int num){
    char buffer[sizeof(int) *3]{};
    if (convertNumToStr(buffer, sizeof(buffer), "%d", &num)){
        return buffer;
    }
    return STR_NULL;
}

uString uString::toString(const unsigned num){
    char buffer[sizeof(unsigned) *3]{};
    if (convertNumToStr(buffer, sizeof(buffer), "%u", &num)){
        return buffer;
    }
    return STR_NULL;
}

uString uString::toString(const long num){
    char buffer[sizeof(long) *3]{};
    if (convertNumToStr(buffer, sizeof(buffer), "%ld", &num)){
        return buffer;
    }
    return STR_NULL;
}

uString uString::toString(const long long num){
    char buffer[sizeof(long long) *3]{};
    if (convertNumToStr(buffer, sizeof(buffer), "%lld", &num)){
        return buffer;
    }
    return STR_NULL;
}

uString uString::toString(const unsigned long num){
    char buffer[sizeof(unsigned long) *3]{};
    if (convertNumToStr(buffer, sizeof(buffer), "%lu", &num)){
        return buffer;
    }
    return STR_NULL;
}

uString uString::toString(const unsigned long long num){
    char buffer[sizeof(unsigned long long) *3]{};
    if (convertNumToStr(buffer, sizeof(buffer), "%llu", &num)){
        return buffer;
    }
    return STR_NULL;
}

uString uString::toString(const double num){
    char buffer[sizeof(double) *3]{};
    if (convertNumToStr(buffer, sizeof(buffer), "%.2f", &num)){
        return buffer;
    }
    return STR_NULL;
}

uString uString::toString(const char num){
    char buffer[sizeof(char) *3]{};
    if (convertNumToStr(buffer, sizeof(buffer), "%c", &num)){
        return buffer;
    }
    return STR_NULL;
}

ulong_t uString::toInt(){
    if (this->arr)
        return atol(this->arr);
    return 0;
}

double uString::toDouble(){
    if (this->arr)
        return atof(this->arr);
    return 0;
}

char uString::at(ulong_t at){
    return ((at < this->u_size) ? this->arr[at] : '\0');
}

void uString::trim(){
    if (this->arr && this->u_size){
        char_p_t arr_ = createNewArr(this->u_capacity +1);
        
        ulong_t number = this->u_size;
        for (ulong_t i = 0, j = 0; i < this->u_size; i++){
            if (this->arr[i] != ' ' && this->arr[i] != '\n' && this->arr[i] != '\t'){
                arr_[j++] = this->arr[i];
            }
            else{
                number--;
            }
        }
        this->u_size = number;
        arr_[this->u_size] = '\0';
        deleteAndTransfer(&this->arr, &arr_);
    }
}

void uString::trimIs(char_p_t arr, int size){
    if (this->arr && this->u_size){
        char_p_t arr_ = createNewArr(this->u_capacity +1);
        
        ulong_t number = this->u_size;
        bool aud = false;
        for (ulong_t i = 0, j = 0; i < this->u_size; i++){
            aud = false;
            for (ulong_t l = 0; l < size; l++){
                if (arr[l] == this->arr[i]){
                    aud = true;
                }
            }
            if (!aud){
                arr_[j++] = this->arr[i];
            }
            else{
                number--;
            }
        }
        this->u_size = number;
        arr_[this->u_size] = '\0';
        deleteAndTransfer(&this->arr, &arr_);
    }
}

void uString::replace(c_ulong_t index, c_ulong_t len, uString str){
    replace_(index, len, str.arr, str.u_size);
}

ulong_t uString::find(const uString &str){
    return find_(str);
}

ulong_t uString::rfind(const uString &other){
    return rfind_(other);
}

uString uString::concatenate(const uString &in1, const uString &in2){
    return (in1 + in2);
}

uString::iterator uString::begin(){
    return this->arr;
}

uString::iterator uString::end(){
    return &this->arr[this->u_size];
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

uString &uString::operator= (c_char_i_t str){
    c_ulong_t size = getStrLen(str);
    overwrite(str, size, size);
    
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

uString &uString::operator+= (c_char_i_t arr){
    addStrToArrExp(arr, getStrLen(arr), one);
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

#if defined(__APPLE__) || defined(_WIN32)
std::ostream &operator<< (std::ostream &ost, const uString &ext){
    return ((ext.arr == nullptr) ? ost << STR_NULL : ost << ext.arr);
}
#endif

uString operator+ (const uString &in1, const uString &in2){
    uString str = in1;
    str.append(in2);
    return str;
}

 uString operator+ (uString &in, c_char_i_t str){
    in.append(str);
    return in;
}

uString operator+ (c_char_i_t str, uString &in){
    in.insert(str);
    return in;
}

void uString::deleteAndTransfer(char_pp_t arr, char_pp_t arr_){
    if (arr_){
        delete [] *arr;
        *arr = nullptr;
        *arr = *arr_;
    }
}

ulong_t uString::find_(const uString &str){
    for (ulong_t i = 0; ((i < this->u_size) && str.u_size != 0); i++){
        if (this->arr[i] == str.arr[0]){
            if (this->arr[i + (str.u_size -1)] == str.arr[str.u_size -1]){
                for (ulong_t l = 0; l < str.u_size; l++){
                    if (this->arr[i + l] == str.arr[l]){
                        if (l == (str.u_size -1)){
                            return i;
                        }
                    }
                    else{
                        break;
                    }
                }
            }
        }
    }
    return -1;
}

ulong_t uString::rfind_(const uString &str){
    for (ulong_t i = (this->u_size -1); (i != ULONG_T_MAX && str.u_size != 0); i--){
        if (this->arr[i] == str.arr[str.u_size -1]){
            if (this->arr[i - (str.u_size -1)] == str.arr[0]){
                for (ulong_t l = 0; l < str.u_size; l++){
                    if (this->arr[(i - (str.u_size -1)) + l] == str.arr[l]){
                        if (l == (str.u_size -1)){
                            return (i - (str.u_size -1));
                        }
                    }
                    else{
                        break;
                    }
                }
            }
        }
    }
    return -1;
}

bool uString::convertNumToStr(char_p_t buffer, const int sizeBuffer, c_char_p_t par, const void *number){
    if (compareSymbols(par, getStrLen(par), "%d", getStrLen("%d"))){
        return snprintf(buffer, sizeBuffer, par, (*(int*)number));
    }
    else if (compareSymbols(par, getStrLen(par), "%ld", getStrLen("%ld"))){
        return snprintf(buffer, sizeBuffer, par, (*(long*)number));
    }
    else if (compareSymbols(par, getStrLen(par), "%lld", getStrLen("%lld"))){
        return snprintf(buffer, sizeBuffer, par, (*(long long*)number));
    }
    else if (compareSymbols(par, getStrLen(par), "%hd", getStrLen("%hd"))){
        return snprintf(buffer, sizeBuffer, par, (*(short*)number));
    }
    else if (compareSymbols(par, getStrLen(par), "%u", getStrLen("%u"))){
        return snprintf(buffer, sizeBuffer, par, (*(unsigned*)number));
    }
    else if (compareSymbols(par, getStrLen(par), "%lu", getStrLen("%lu"))){
        return snprintf(buffer, sizeBuffer, par, (*(unsigned long*)number));
    }
    else if (compareSymbols(par, getStrLen(par), "%llu", getStrLen("%llu"))){
        return snprintf(buffer, sizeBuffer, par, (*(unsigned long long*)number));
    }
    else if (compareSymbols(par, getStrLen(par), "%.2f", getStrLen("%.2f"))){
        return snprintf(buffer, sizeBuffer, par, (*(double*)number));
    }
    else if (compareSymbols(par, getStrLen(par), "%c", getStrLen("%c"))){
        return snprintf(buffer, sizeBuffer, par, (*(char*)number));
    }
    
    return null;
}

void uString::replace_(c_ulong_t index, c_ulong_t len, c_char_p_t str, c_ulong_t size){
    if (this->arr && this->u_size && index <= this->u_size && index != ULONG_T_MAX){
        resizeCapacity(this->u_size + size);
        
        char_p_t arr_ = createNewArr(this->u_capacity +1);
        copyStrToArr(this->arr, arr_, index);
        copyStrToArrIndex(index, str, arr_, index + size);
        copyStrIndexToArrIndexV2(arr_, this->arr, index, len, size);
        
//       copyStrIndexToArrIndex(index + size, this->arr, arr_, index + len,
//                               (index + size) + (((this->u_size - index) >= len) ? (this->u_size - index) - len : 0) +1);
        
        this->u_size = (this->u_size - ((this->u_size <= len) ? this->u_size : len)) + size;
        deleteAndTransfer(&this->arr, &arr_);
    }
}
