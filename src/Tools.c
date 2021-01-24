#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <Tools.h>

char static_string_dst[1024];

//------------ memory manager ------------//

void delete_memory(void *memory) { free(memory); }

//------------ string ------------//

string new_string(const_string src) {
    string dst = (string) calloc(len(src) + 1, sizeof(char));

    return dst ? strcpy(dst, src) : NULL;
}
size_t len(const_string src) { return src ? strlen(src) : 0; }
string add(ptr_string ptr_dst, const_string src) {
    const size_t dst_size = len(*ptr_dst);
    const size_t src_size = len(src);

    if(src_size) {
        *ptr_dst = (string) realloc(*ptr_dst, dst_size + src_size + 1);

        if(!dst_size) *ptr_dst = strcpy(*ptr_dst, src);
        else *ptr_dst = strcat(*ptr_dst, src);
    }

    return *ptr_dst;
}
string copy(ptr_string ptr_dst, const_string src) {
    const size_t size = len(src) + 1;
    *ptr_dst = (string) realloc(*ptr_dst, size);

    memset(*ptr_dst, 0, size);

    return add(ptr_dst, src);
}
string replace(ptr_string ptr_dst, const_string old_value, const_string new_value) {
    const size_t new_value_size = new_value ? len(new_value) : 1;
    const size_t old_value_size = len(old_value);
    const size_t counter = count_substring(*ptr_dst, old_value);

    if(!*ptr_dst || !old_value || !counter) return *ptr_dst;

    string  result = (string) calloc(len(*ptr_dst) + counter * (new_value_size - old_value_size) + 1, sizeof(char));
    const_string it_dst = *ptr_dst;
    size_t i = 0;

    while (*it_dst) {
        if (strstr(it_dst, old_value) == it_dst) {
            strcpy(result + i, new_value);
            i += new_value_size;
            it_dst += old_value_size;
        }
        else result[i++] = *it_dst++;
    }

    delete_memory(*ptr_dst);

    return *ptr_dst = result;
}
size_t count_substring(const_string dst, const_string src) {
    size_t count = 0;
    const_string it_dst = dst;
    const size_t src_size = len(src);

    if(!len(dst)) return 0;

    while(it_dst = strstr(it_dst, src)) {
            it_dst += src_size;
            count++;
        }

    return count;
}
size_t count_first_digits(const_string src) {
    const size_t src_size = len(src);
    size_t size = 0;

    while(size < src_size && is_digit(*src++)) size++;

    return size;
}
size_t count_all_digits(const_string src) {
    const size_t src_size = len(src);
    size_t size = 0;

    for(size_t i = 0; i < src_size; i++)
        if(is_digit(*src++))
            size++;

    return size;
}
void print_string_floyd(const_string src) {
    const size_t size = len(src);
    for(size_t i = 1; i <= size; i++)
        printf("%.*s\n", i, src);
}

//------------ utilities ------------//

bool is_digit(const char _char) { return isdigit(_char); }
int char_to_digit(const char _char) { return _char - '0'; }
char digit_to_char(const int digit) { return (char) (digit + '0'); }

//------------ print list ------------//

void print_bool_list(const_bool_list list, const size_t size) { for(size_t i = 0; i < size; i++) printf("%s, ", list[i] ? "true" : "false"); }
void print_short_list(const_short_list list, const size_t size) { for(size_t i = 0; i < size; i++) printf("%hi, ", list[i]); }
void print_int_list(const_int_list list, const size_t size) { for(size_t i = 0; i < size; i++) printf("%i, ", list[i]); }
void print_long_list(const_long_list list, const size_t size) { for(size_t i = 0; i < size; i++) printf("%li, ", list[i]); }
void print_size_t_list(const_size_t_list list, const size_t size) { for(size_t i = 0; i < size; i++) printf("%llu, ", list[i]); }
void print_float_list(const_float_list list, const size_t size) { for(size_t i = 0; i < size; i++) printf("%f, ", list[i]); }
void print_double_list(const_double_list list, const size_t size) { for(size_t i = 0; i < size; i++) printf("%lf, ", list[i]); }

//------------ string to type ------------//

bool to_bool(const_string src) { return !strcmp(src, "true") ? true : false; }
short to_short(const_string src) { return (short) strtol(src, NULL, 10); }
int to_int(const_string src) { return (int) strtol(src, NULL, 10); }
long to_long(const_string src) { return strtol(src, NULL, 10); }
size_t to_size_t(const_string src) { return (size_t) strtoull(src, NULL, 10); }
float to_float(const_string src) { return strtof(src, NULL); }
double to_double(const_string src) { return strtod(src, NULL); }

//------------ type to string ------------//

const_string bool_to_string(const bool value) { return value ? "true" : "false"; }
const_string short_to_string(const short value) { sprintf(static_string_dst, "%hi", value); return static_string_dst; }
const_string int_to_string(const int value) { sprintf(static_string_dst, "%i", value); return static_string_dst; }
const_string long_to_string(const long value) { sprintf(static_string_dst, "%li", value); return static_string_dst; }
const_string size_t_to_string(const size_t value) { sprintf(static_string_dst, "%llu", value); return static_string_dst; }
const_string float_to_string(const float value) { sprintf(static_string_dst, "%f", value); return static_string_dst; }
const_string double_to_string(const double value) { sprintf(static_string_dst, "%lf", value); return static_string_dst; }

//------------ list ------------//

bool_list new_bool_list(size_t size) {  return (bool_list) calloc(size, sizeof(bool)); }
short_list new_short_list(size_t size) {  return (short_list) calloc(size, sizeof(short)); }
int_list new_int_list(const size_t size) { return (int_list) calloc(size, sizeof(int)); }
long_list new_long_list(size_t size) {  return (long_list) calloc(size, sizeof(long)); }
size_t_list new_size_t_list(size_t size) {  return (size_t_list) calloc(size, sizeof(size_t)); }
float_list new_float_list(size_t size) {  return (float_list) calloc(size, sizeof(float)); }
double_list new_double_list(size_t size) {  return (double_list) calloc(size, sizeof(double )); }

//------------ string to list ------------//

bool_list string_to_bool_list(const_string src) {
    const size_t src_size = count_first_digits(src);

    if(src_size) {
        bool_list dst = new_bool_list(src_size);
        char *it_dst = dst;
        const char *it_src = src;
        const char *it_end = src + src_size;

        while(it_src != it_end)
            if(is_digit(*it_src))
                *it_dst++ = *it_src++ != '0' ? true : false;
            else break;

        return dst;
    }

    return NULL;
}
int_list string_to_int_list(const_string src) {
    const size_t src_size = count_first_digits(src);

    if(src_size) {
        int_list dst = new_int_list(src_size);
        int *it_dst = dst;
        const char *it_src = src;
        const char *it_end = src + src_size;

        while(it_src != it_end)
            if(is_digit(*it_src))
                *it_dst++ = char_to_digit(*it_src++);
            else break;

        return dst;
    }

    return NULL;
}