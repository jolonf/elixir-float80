#include <math.h>
#include <stdio.h>
#include <string.h>

#include "erl_nif.h"

const int FLOAT80_SIZE = 10;

/**
 * See the website for a description of how to write a NIF:
 * https://andrealeopardi.com/posts/using-c-from-elixir-with-nifs/
 * 
 * Terms:
 * - Float80: An Elixir value represented using a 10-byte binary
 * - long double: A C type using an 80-bit extended precision double
 */

/**
 * Debug function to print bytes in Float80 binary.
 */
static void printBytes(char *label, ErlNifBinary *bin) {
    printf("%s: \n", label);
    printf("\tsize: %ld bytes\n", bin->size);

    printf("\t<<");
    for (int i = 0; i < bin->size; i++) {
        printf("%d,", bin->data[i]);
    }
    printf(">>\n");
}

/**
 * Convenience function used by most NIF functions to return
 * a Float80 value.
 */
static ERL_NIF_TERM
long_double_to_term(ErlNifEnv *env, long double value) {
    ERL_NIF_TERM term;
    unsigned char *data = enif_make_new_binary(env, FLOAT80_SIZE, &term);
    memcpy(data, &value, FLOAT80_SIZE);
    return term;
}

/**
 * Converts a binary term to a long double.
 */
static long double
term_to_long_double(ErlNifEnv *env, ERL_NIF_TERM term) {

    long double result = 0;
    ErlNifBinary bin;

    if (enif_term_to_binary(env, term, &bin)) {

        if (bin.size >= FLOAT80_SIZE) {
            // The size is 16 with the 10 byte data right aligned.
            // So increase pointer by the difference.
            // Should take into account endianness?
            unsigned char *data = bin.data + (bin.size - FLOAT80_SIZE);

            long double *value = (long double *) data;
            result = *value;
        }

        enif_release_binary(&bin);
    }

    return result;
}

/**
 * Takes an Erlang float and returns a binary Float80.
 */
static ERL_NIF_TERM
from_float(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
    double a = 0;
    enif_get_double(env, argv[0], &a);
    long double result = a;
    return long_double_to_term(env, result);
}

/**
 * Takes an Erlang integer and returns a binary Float80.
 */
static ERL_NIF_TERM
from_integer(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
    long a = 0;
    enif_get_int64(env, argv[0], &a);
    long double result = a;
    return long_double_to_term(env, result);
}

/**
 * Takes a binary Float80 and returns an Erlang float.
 * Note that this will result in a loss of prevision.
 */
static ERL_NIF_TERM
to_float(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
    long double a = term_to_long_double(env, argv[0]);
    double result = a;
    return enif_make_double(env, result);
}

/**
 * Takes two Float80 arguments and returns the sum as a Float80.
 */
static ERL_NIF_TERM
add(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {

    long double a = term_to_long_double(env, argv[0]);
    long double b = term_to_long_double(env, argv[1]);

    long double result = a + b;

    return long_double_to_term(env, result);
}

/**
 * Takes two Float80 arguments and returns the difference (a-b) as a Float80.
 */
static ERL_NIF_TERM
subtract(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {

    long double a = term_to_long_double(env, argv[0]);
    long double b = term_to_long_double(env, argv[1]);

    long double result = a - b;

    return long_double_to_term(env, result);
}

/**
 * Takes two Float80 arguments and returns the product as a Float80.
 */
static ERL_NIF_TERM
multiply(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {

    long double a = term_to_long_double(env, argv[0]);
    long double b = term_to_long_double(env, argv[1]);

    long double result = a * b;

    return long_double_to_term(env, result);
}

/**
 * Takes two Float80 arguments and returns the division (a/b) as a Float80.
 */
static ERL_NIF_TERM
divide(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {

    long double a = term_to_long_double(env, argv[0]);
    long double b = term_to_long_double(env, argv[1]);

    long double result = a / b;

    return long_double_to_term(env, result);
}

/**
 * Absolute value of Float80, returns Float80 result.
 */
static ERL_NIF_TERM
abs80(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
    long double a = term_to_long_double(env, argv[0]);
    long double result = fabsl(a);
    return long_double_to_term(env, result);
}

/**
 * PI returned as Float80.
 */
static ERL_NIF_TERM
pi(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
    long double result = M_PI;
    return long_double_to_term(env, result);
}

/**
 * Arcosine of Float80, returns Float80 result.
 */
static ERL_NIF_TERM
acos80(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {

    long double a = term_to_long_double(env, argv[0]);

    long double result = acosl(a);

    return long_double_to_term(env, result);
}

/**
 * Arcsine of Float80, returns Float80 result.
 */
static ERL_NIF_TERM
asin80(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {

    long double a = term_to_long_double(env, argv[0]);

    long double result = asinl(a);

    return long_double_to_term(env, result);
}

/**
 * Arctangent of Float80, returns Float80 result.
 */
static ERL_NIF_TERM
atan80(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {

    long double a = term_to_long_double(env, argv[0]);

    long double result = atanl(a);

    return long_double_to_term(env, result);
}

/**
 * Cosine of Float80 (in radians), returns Float80 result.
 */
static ERL_NIF_TERM
cos80(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {

    long double a = term_to_long_double(env, argv[0]);

    long double result = cosl(a);

    return long_double_to_term(env, result);
}

/**
 * Sine of Float80 (in radians), returns Float80 result.
 */
static ERL_NIF_TERM
sin80(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {

    long double a = term_to_long_double(env, argv[0]);

    long double result = sinl(a);

    return long_double_to_term(env, result);
}

/**
 * Tangent of Float80, returns Float80 result.
 */
static ERL_NIF_TERM
tan80(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {

    long double a = term_to_long_double(env, argv[0]);

    long double result = tanl(a);

    return long_double_to_term(env, result);
}

/**
 * e to the xth power, returns Float80 result.
 */
static ERL_NIF_TERM
exp80(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {

    long double a = term_to_long_double(env, argv[0]);

    long double result = expl(a);

    return long_double_to_term(env, result);
}

/**
 * Natural logarithm, returns Float80 result.
 */
static ERL_NIF_TERM
log80(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {

    long double a = term_to_long_double(env, argv[0]);

    long double result = logl(a);

    return long_double_to_term(env, result);
}

/**
 * Base 10 logarithm, returns Float80 result.
 */
static ERL_NIF_TERM
log1080(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {

    long double a = term_to_long_double(env, argv[0]);

    long double result = log10l(a);

    return long_double_to_term(env, result);
}

/**
 * Base 2 logarithm, returns Float80 result.
 */
static ERL_NIF_TERM
log280(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {

    long double a = term_to_long_double(env, argv[0]);

    long double result = log2l(a);

    return long_double_to_term(env, result);
}

/**
 * a to the power of b, returns Float80 result.
 */
static ERL_NIF_TERM
pow80(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {

    long double a = term_to_long_double(env, argv[0]);
    long double b = term_to_long_double(env, argv[1]);

    long double result = powl(a, b);

    return long_double_to_term(env, result);
}

/**
 * Square root, returns Float80 result.
 */
static ERL_NIF_TERM
sqrt80(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {

    long double a = term_to_long_double(env, argv[0]);

    long double result = sqrtl(a);

    return long_double_to_term(env, result);
}

/**
 * Round up, returns Float80 result.
 */
static ERL_NIF_TERM
ceil80(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {

    long double a = term_to_long_double(env, argv[0]);

    long double result = ceill(a);

    return long_double_to_term(env, result);
}

/**
 * Round down, returns Float80 result.
 */
static ERL_NIF_TERM
floor80(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {

    long double a = term_to_long_double(env, argv[0]);

    long double result = floorl(a);

    return long_double_to_term(env, result);
}

/**
 * Round to nearest, returns Float80 result.
 */
static ERL_NIF_TERM
round80(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {

    long double a = term_to_long_double(env, argv[0]);

    long double result = roundl(a);

    return long_double_to_term(env, result);
}

// Let's define the array of ErlNifFunc beforehand:
static ErlNifFunc nif_funcs[] = {
    // {erl_function_name, erl_function_arity, c_function}
    {"from_float", 1, from_float},
    {"from_integer", 1, from_integer},
    {"to_float", 1, to_float},
    // Arithmetic
    {"add", 2, add},
    {"subtract", 2, subtract},
    {"multiply", 2, multiply},
    {"divide", 2, divide},
    {"abs", 1, abs80},
    // Constants
    {"pi", 0, pi},
    // Trigonometry
    {"acos", 1, acos80},
    {"asin", 1, asin80},
    {"atan", 1, atan80},
    {"cos", 1, cos80},
    {"sin", 1, sin80},
    {"tan", 1, tan80},
    // Powers
    {"exp", 1, exp80},
    {"log", 1, log80},
    {"log10", 1, log1080},
    {"log2", 1, log280},
    {"pow", 2, pow80},
    {"sqrt", 1, sqrt80},
    // Rounding
    {"ceil", 1, ceil80},
    {"floor", 1, floor80},
    {"round", 1, round80},
};

ERL_NIF_INIT(Elixir.Float80, nif_funcs, NULL, NULL, NULL, NULL)
