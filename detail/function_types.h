//
//  function_types.h
//  differentionable_function
//
//  Created by ISHII 2bit on 2015/09/13.
//
//

#ifndef differentionable_function_function_types_h
#define differentionable_function_function_types_h

#include "constants.h"

BEGIN_DIFFERENTIONABLE_FUNCTION_NAMESPACE

enum class Type {
    Function,
    Constant,
    Id,
    Compose,
    Add,
    Neg,
    Mul,
    Div,
    Exp,
    Sqrt,
    Pow,
    Log,
    Sin,
    Cos,
    Tan,
    Asin,
    Acos,
    Atan
};

END_DIFFERENTIONABLE_FUNCTION_NAMESPACE

#endif
