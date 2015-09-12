//
//  constants.h
//  differentionable_function
//
//  Created by ISHII 2bit on 2015/09/13.
//
//

#ifndef differentionable_function_constants_h
#define differentionable_function_constants_h

#include <cmath>
#include <memory>

#define USE_NAMESPACE 0
#define WARNING { char *p = ""; }

#if USE_NAMEPSACE
#   define BEGIN_DIFFERENTIONABLE_FUNCTION_NAMESPACE namespace differentiation_function {
#   define END_DIFFERENTIONABLE_FUNCTION_NAMESPACE };
#else
#   define BEGIN_DIFFERENTIONABLE_FUNCTION_NAMESPACE
#   define END_DIFFERENTIONABLE_FUNCTION_NAMESPACE
#endif

BEGIN_DIFFERENTIONABLE_FUNCTION_NAMESPACE

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename ... Args>
Ref<T> ref(Args&& ...args) {
    return std::make_shared<T>(args ...);
}

const double e = M_E;
const double pi = M_PI;

END_DIFFERENTIONABLE_FUNCTION_NAMESPACE

#endif
