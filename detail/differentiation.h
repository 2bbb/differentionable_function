//
//  differentiation.h
//  differentionable_function
//
//  Created by ISHII 2bit on 2015/09/13.
//
//

#ifndef differentionable_function_differentiation_h
#define differentionable_function_differentiation_h

#include "constants.h"
#include "function_types.h"
#include "types.h"
#include "operators.h"

#include <type_traits>

BEGIN_DIFFERENTIONABLE_FUNCTION_NAMESPACE

template <typename FP>
typename std::enable_if<std::is_same<FP, FunctionPtr>::value, FunctionPtr>::type diff(FP f) {
#define Case(type) case Type::type: return diff(dynamic_pointer_cast<type>(f)); break;
    switch(f->type) {
            Case(Constant);
            Case(Id);
            Case(Compose);
            Case(Add);
            Case(Neg);
            Case(Mul);
            Case(Div);
            Case(Exp);
            Case(Sqrt);
            Case(Pow);
            Case(Log);
            Case(Sin);
            Case(Cos);
            Case(Tan);
            Case(Asin);
            Case(Acos);
            Case(Atan);
        default:
            return f;
    }
}


// Constant'
inline FunctionPtr diff(Ref<Constant> a) {
    return c0;
}

// x'
inline FunctionPtr diff(Ref<Id> x) {
    return c1;
}

// (-f)'
inline FunctionPtr diff(Ref<Neg> f) {
    if(f->f->type == Type::Neg) {
        return diff(f->f->f);
    } else {
        return -diff(f->f);
    }
}

// (f | g)'
inline FunctionPtr diff(Ref<Compose> f) {
    return diff(f->g) * (diff(f->f) | f->g);
}

// (f + g)'
inline FunctionPtr diff(Ref<Add> f) {
    if(f->f == c0) {
        return diff(f->g);
    } else if(f->g == c0) {
        return diff(f->f);
    }
    return diff(f->f) + diff(f->g);
}

// (f * g)'
inline FunctionPtr diff(Ref<Mul> f) {
    if(f->f == c1) {
        return diff(f->g);
    } else if(f->g == c1) {
        return diff(f->f);
    }
    return (diff(f->f) * f->g) + (f->f * diff(f->g));
}

// (f / g)'
inline FunctionPtr diff(Ref<Div> f) {
    if(f->g == c1) {
        return diff(f->f);
    }
    return ((diff(f->f) * f->g) - (f->f * diff(f->g))) / (f->g ^ 2);
}

// (e^f)'
inline FunctionPtr diff(Ref<Exp> f) {
    if(f->f->type == Type::Id) {
        return f;
    }
    return diff(f->f) * exp(f->f);
}

// sqrt(f)'
inline FunctionPtr diff(Ref<Sqrt> f) {
    if(f->f->type == Type::Id) {
        return 1 / (2 * f);
    }
    return diff(f->f) / (2 * sqrt(f->f));
}

// (f ^ g)'
inline FunctionPtr diff(Ref<Pow> f) {
    if(f->g->type == Type::Constant) {
        if(f->f->type == Type::Id) {
            return f->g * (f->f ^ c(f->g->apply(0) - 1));
        }
        return f->g * ((f->f ^ c(f->g->apply(0) - 1)) * diff(f->f));
    }
    return 	(f->f ^ (f->g - 1)) * (f->g * diff(f->f) + ((f->f * log(f->f)) * diff(f->g)));
}

// (log(f))'
inline FunctionPtr diff(Ref<Log> f) {
    if(f->f->type == Type::Id) {
        return 1 / var;
    }
    return 	diff(f->f) / f->f;
}

// (sin(f))'
inline FunctionPtr diff(Ref<Sin> f) {
    if(f->f->type == Type::Id) {
        return cos(f->f);
    }
    return cos(f->f) * diff(f->f);
}

// (cos(f))'
inline FunctionPtr diff(Ref<Cos> f) {
    if(f->f->type == Type::Id) {
        return -sin(f->f);
    }
    return (-(sin(f->f))) * diff(f->f);
}

// (tan(f))'
inline FunctionPtr diff(Ref<Tan> f) {
    return diff(f->f) / (cos(f->f) ^ 2);
}

// (asin(f))'
inline FunctionPtr diff(Ref<Asin> f) {
    return diff(f->f) / sqrt(1 - pow(f->f, 2_c));
}

// (acos(f))'
inline FunctionPtr diff(Ref<Acos> f) {
    return diff(f->f) / sqrt(1 - pow(f->f, 2_c));
}

// (atan(f))'
inline FunctionPtr diff(Ref<Atan> f) {
    return diff(f->f) / ((f->f ^ 2)  - 1);
}

#pragma mark dn

inline FunctionPtr diff_n(FunctionPtr f, unsigned int n) {
    return (n == 0) ? f : diff_n(diff(f), n - 1);
}

END_DIFFERENTIONABLE_FUNCTION_NAMESPACE

#endif
