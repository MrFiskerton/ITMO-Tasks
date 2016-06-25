#include "lazy_string.h"

using namespace std;

lazy_string::lazy_string() {
    (*this).begin = (*this).end = 0;
    this->data = make_shared<string>("");
}

lazy_string::lazy_string(const string &str) {
    (*this).begin = 0;
    (*this).end = str.size();
    (*this).data = make_shared<string>(str);
}

lazy_string::lazy_string(size_t begin, size_t size, shared_ptr<string> str) {
    (*this).begin = begin;
    (*this).end = size;
    (*this).data = str;
}

size_t lazy_string::size() const { return end; }

size_t lazy_string::length() const {  return end; }

istream &operator>>(istream &input, lazy_string &str) {
    auto s = make_shared<string>();
    input >> *s;
    str.data = s;
    str.begin = 0;
    str.end = (*s).size();
    return input;
}

ostream &operator<<(ostream &output, lazy_string &str) {
    for (size_t i = str.begin; i < str.begin + str.size(); i++) { output << str[i]; }
    return output;
}
 


lazy_string lazy_string::substr(size_t pos, size_t length) {
    return lazy_string(begin + pos, (pos + length > end) ? (end - pos) : length, data);
}

lazy_string::operator std::string() {
    return (*data).substr(begin, end);
}

char lazy_string::at(size_t i) const {
    return (*data)[begin + i];
}

lazy_string::get_char lazy_string::at(size_t i) {
    return get_char(this, i);
}

char lazy_string::operator[](size_t i) const {
    return (*data)[begin + i];
}

lazy_string::get_char lazy_string::operator[](size_t i) {
    return get_char(this, i);
}

lazy_string::get_char::get_char(lazy_string *str, size_t i) : lazy_str(str), index(i) { }

lazy_string::get_char &lazy_string::get_char::operator=(char c) {
    if ((*lazy_str).data.use_count() > 1) {
        (*lazy_str).begin = 0;
        (*lazy_str).data = make_shared<string>(lazy_str->data->substr((*lazy_str).begin, (*lazy_str).end));
    }
    (*lazy_str->data)[(*lazy_str).begin + index] = c;
    return *this;
}

lazy_string::get_char::operator char() const {
    return (*lazy_str->data)[lazy_str->begin + index];
}
