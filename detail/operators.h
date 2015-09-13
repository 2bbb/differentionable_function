//
//  operators.h
//  differentionable_function
//
//  Created by ISHII 2bit on 2015/09/13.
//
//

#ifndef differentionable_function_operators_h
#define differentionable_function_operators_h

#include "constants.h"
#include "function_types.h"
#include "types.h"

BEGIN_DIFFERENTIONABLE_FUNCTION_NAMESPACE

#pragma mark +

inline FunctionPtr operator+(FunctionPtr f) {
    return f;
}

inline FunctionPtr operator+(FunctionPtr f, FunctionPtr g) {
    return ref<Add>(f, g);
}

inline FunctionPtr operator+(FunctionPtr f, double a) {
    return f + c(a);
}

inline FunctionPtr operator+(double a, FunctionPtr f) {
    return c(a) + f;
}

#pragma mark -

inline FunctionPtr operator-(FunctionPtr f) {
    if(f->type == Type::Constant) {
        return c(-f->apply(0));
    }
    return ref<Neg>(f);
}

inline FunctionPtr operator-(FunctionPtr f, FunctionPtr g) {
    if(f == c0) {
        return -g;
    } else if(g == c0) {
        return f;
    }
    return f + (-g);
}

inline FunctionPtr operator-(FunctionPtr f, double a) {
    return f - c(a);
}

inline FunctionPtr operator-(double a, FunctionPtr f) {
    return c(a) - f;
}

#pragma mark *

inline FunctionPtr operator*(FunctionPtr f, FunctionPtr g) {
    if(f == c0 || g == c0) {
        return c0;
    } else if(g == c1) {
        return f;
    } else if(f == c1) {
        return g;
    } else if(f->type == Type::Constant && g->type == Type::Constant) {
        return c(f->apply(0) * g->apply(0));
    }
    return ref<Mul>(f, g);
}

inline FunctionPtr operator*(FunctionPtr f, double a) {
    return (a == 0.0) ? c0 : (a == 1.0) ? c1 : (f * c(a));
}

inline FunctionPtr operator*(double a, FunctionPtr f) {
    return (a == 0.0) ? c0 : (a == 1.0) ? c1 : (c(a) * f);
}

#pragma mark /

inline FunctionPtr operator/(FunctionPtr f, FunctionPtr g) {
    return ref<Div>(f, g);
}

inline FunctionPtr operator/(FunctionPtr f, double a) {
    return (a == 1.0) ? f : (f / c(a));
}

inline FunctionPtr operator/(double a, FunctionPtr f) {
    return c(a) / f;
}

#pragma mark ^

inline FunctionPtr operator^(FunctionPtr f, FunctionPtr g) {
    if(g->type == Type::Constant && g->apply(0) == 1.0) {
        return f;
    }
    return ref<Pow>(f, g);
}

inline FunctionPtr operator^(FunctionPtr f, double a) {
    if(a == 0.0) {
        /// TODO: 0^0
        return c1;
    }
    return f ^ c(a);
}

inline FunctionPtr operator^(double a, FunctionPtr f) {
    if(a == 0.0) {
        /// TODO: 0^0
        return c0;
    }
    return c(a) ^ f;
}

#pragma mark .

inline FunctionPtr operator|(FunctionPtr f, FunctionPtr g) {
    return ref<Compose>(f, g);
}

#pragma mark overload

inline FunctionPtr exp(FunctionPtr f = Variable()) {
    return ref<Exp>(f);
}

inline FunctionPtr sqrt(FunctionPtr f = Variable()) {
    return ref<Sqrt>(f);
}

inline FunctionPtr pow(double n) {
    return ref<Pow>(Variable(), c(n));
}

inline FunctionPtr pow(FunctionPtr f, FunctionPtr g) {
    return f ^ g;
}

inline FunctionPtr pow(double a, FunctionPtr f) {
    return a ^ f;
}

inline FunctionPtr pow(FunctionPtr f, double a) {
    return f ^ a;
}

inline FunctionPtr log(FunctionPtr f = Variable()) {
    return ref<Log>(f);
}

inline FunctionPtr sin(FunctionPtr f = Variable()) {
    return ref<Sin>(f);
}

inline FunctionPtr cos(FunctionPtr f = Variable()) {
    return ref<Cos>(f);
}

inline FunctionPtr tan(FunctionPtr f = Variable()) {
    return ref<Tan>(f);
}

inline FunctionPtr asin(FunctionPtr f = Variable()) {
    return ref<Asin>(f);
}

inline FunctionPtr acos(FunctionPtr f = Variable()) {
    return ref<Acos>(f);
}

inline FunctionPtr atan(FunctionPtr f = Variable()) {
    return ref<Atan>(f);
}

#pragma mark user definition literal

inline FunctionPtr operator ""_c(unsigned long long int a) {
    return c(a);
}

inline FunctionPtr operator ""_c(long double a) {
    return c(a);
}

END_DIFFERENTIONABLE_FUNCTION_NAMESPACE

#endif
