#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED


#include <stdexcept>


struct Invalid_String : std::runtime_error
{
    Invalid_String() :
        std::runtime_error("Invalid string passed to function!\n") {}
};


struct Null_Pointer : std::runtime_error
{
    Null_Pointer() :
        std::runtime_error("Attempt to use a NULL pointer!\n") {}
};


struct Invalid_Position : std::invalid_argument
{
    Invalid_Position() :
        std::invalid_argument("Invalid position error!\n") {}
};


struct Invalid_Image  : std::runtime_error {};
struct Invalid_Font   : std::runtime_error {};



#endif // EXCEPTIONS_H_INCLUDED
