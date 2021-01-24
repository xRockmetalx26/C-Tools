#ifndef TOOLS_H
#define TOOLS_H

#include <stdint.h>

//------------ macro ------------//

#define true 1
#define false 0

#define print(src) printf("%s", src);
#define println(src) printf("%s\n", src);

//------------ typedef ------------//

typedef unsigned char bool;

typedef char* bool_list;
typedef const char* const_bool_list;

typedef char* string;
typedef const char* const_string;

typedef string* ptr_string;

typedef char** string_list;
typedef const char** const_string_list;

typedef short* short_list;
typedef const short* const_short_list;

typedef int* int_list;
typedef const int* const_int_list;

typedef long* long_list;
typedef const long* const_long_list;

typedef size_t* size_t_list;
typedef const size_t* const_size_t_list;

typedef float* float_list;
typedef const float* const_float_list;

typedef double* double_list;
typedef const double* const_double_list;

//------------ memory manager ------------//

void delete_memory(void *memory);

//------------ string ------------//

string new_string(const_string src);
string add(string *ptr_dst, const_string src);
string copy(string *ptr_dst, const_string src);
string replace(ptr_string ptr_dst, const_string old_value, const_string new_value);
size_t len(const_string src);
size_t count_substring(const_string dst, const_string src);
size_t count_first_digits(const_string src);
size_t count_all_digits(const_string src);
void print_string_floyd(const_string src);

//------------ utilities ------------//

bool is_digit(char _char);
int char_to_digit(char _char);
char digit_to_char(int digit);

//------------ print list ------------//

void print_bool_list(const_bool_list list, size_t size);
void print_short_list(const_short_list list, size_t size);
void print_int_list(const_int_list list, size_t size);
void print_long_list(const_long_list list, size_t size);
void print_size_t_list(const_size_t_list list, size_t size);
void print_float_list(const_float_list list, size_t size);
void print_double_list(const_double_list list, size_t size);

//------------ string to type ------------//

bool to_bool(const_string src);
short to_short(const_string src);
int to_int(const_string src);
long to_long(const_string src);
size_t to_size_t(const_string src);
float to_float(const_string src);
double to_double(const_string src);

//------------ type to string ------------//

const_string bool_to_string(bool value);
const_string short_to_string(short value);
const_string int_to_string(int value);
const_string long_to_string(long value);
const_string size_t_to_string(size_t value);
const_string float_to_string(float value);
const_string double_to_string(double value);

//------------ list ------------//

bool_list new_bool_list(size_t size);
short_list new_short_list(size_t size);
int_list new_int_list(size_t size);
long_list new_long_list(size_t size);
size_t_list new_size_t_list(size_t size);
float_list new_float_list(size_t size);
double_list new_double_list(size_t size);

//------------ string to list ------------//

bool_list string_to_bool_list(const_string src);
int_list string_to_int_list(const_string src);

#endif //TOOLS_H