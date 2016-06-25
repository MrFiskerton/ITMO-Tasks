#pragma once

#include <string>
#include <iostream>
#include <memory>

class lazy_string {
    struct get_char {
    public:
        friend class lazy_string;
        operator char() const;
        get_char &operator=(char);
    private:
        get_char(lazy_string *, size_t);
        const size_t index;
        lazy_string *const lazy_str;
    };

private:
    size_t begin, end;
    std::shared_ptr<std::string> data;
    lazy_string(size_t begin, size_t size, std::shared_ptr<string> str);

public:
    lazy_string();                  //Create empty lazy string
    lazy_string(const std::string &str); //Create lazy string from std::string
    operator std::string();         //Create string copy from lazy string
    size_t size() const;            //Return length of lazy sting
    size_t length() const;          //Return length of lazy sting

    //Return the substring from position begin to begin + length (or to the end of a lazy string)
    lazy_string substr(size_t begin, size_t length = std::string::npos);
    //Read lazy string from input stream
    friend std::istream &operator>>(std::istream &input, lazy_string &str);
    //Sends lazy string to output stream
    friend std::ostream &operator<<(std::ostream &output, lazy_string &str);

    get_char at(size_t i);          //Return the character of lazy string
    char at(size_t i) const;
    get_char operator[](size_t i);
    char operator[](size_t i) const;

};

