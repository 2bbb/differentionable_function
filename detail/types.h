//
//  types.h
//  differentionable_function
//
//  Created by ISHII 2bit on 2015/09/13.
//
//

#ifndef differentionable_function_types_h
#define differentionable_function_types_h

#include "constants.h"
#include "function_types.h"

BEGIN_DIFFERENTIONABLE_FUNCTION_NAMESPACE

#define Define(BODY) virtual double apply(double x) BODY;

struct Function;

using FunctionPtr = Ref<Function>;

struct Function {
    Define({ return 0.0; });
    
    const Type type;
    Function(Type type = Type::Function,
             FunctionPtr f = FunctionPtr(),
             FunctionPtr g = FunctionPtr())
    : type(type)
    , f(f)
    , g(g) {}
    
    FunctionPtr f, g;
    int rank = 0;
};

struct Constant : Function {
    Define({ return a; });
    
    const double a;
    Constant(double a)
    : a(a)
    , Function(Type::Constant) {}
};

static FunctionPtr c0 = ref<Constant>(0);
static FunctionPtr c1 = ref<Constant>(1);

FunctionPtr c(double a) {
    if(a == 0.0 || a == 0.0f || a == 0) {
        return c0;
    } else if(a == 1.0 || a == 1.0f || a == 1) {
        return c1;
    }
    return ref<Constant>(a);
}

struct Id : Function {
    Define({ return x; });
    
    Id()
    : Function(Type::Id) {}
};

static FunctionPtr var = ref<Id>();

FunctionPtr Variable() {
    return var;
}

struct Neg : Function {
    Define({ return -f->apply(x); });
    
    Neg(FunctionPtr f)
    : Function(Type::Neg, f) {}
};

struct Compose : Function {
    Define({ return f->apply(g->apply(x)); });
    
    Compose(FunctionPtr f, FunctionPtr g)
    : Function(Type::Id, f, g) {}
};

struct Add : Function {
    Define({ return f->apply(x) + g->apply(x); });
    
    Add(FunctionPtr f, FunctionPtr g)
    : Function(Type::Add, f, g) {}
};

struct Mul : Function {
    Define({ return f->apply(x) * g->apply(x); });
    
    Mul(FunctionPtr f, FunctionPtr g)
    : Function(Type::Mul, f, g) {}
};

struct Div : Function {
    Define({ return f->apply(x) / g->apply(x); });
    
    Div(FunctionPtr f, FunctionPtr g)
    : Function(Type::Div, f, g) {}
};

struct Exp : Function {
    Define({ return exp(f->apply(x)); });
    
    Exp(FunctionPtr f)
    : Function(Type::Exp, f) {}
};

struct Sqrt : Function {
    Define({ return sqrt(f->apply(x)); });
    
    Sqrt(FunctionPtr f)
    : Function(Type::Sqrt, f) {}
};

struct Pow : Function {
    Define({ return pow(f->apply(x), g->apply(x)); });
    
    Pow(FunctionPtr f, FunctionPtr g)
    : Function(Type::Pow, f, g) {}
};

struct Log : Function {
    Define({ return log(f->apply(x)); });
    
    Log(FunctionPtr f)
    : Function(Type::Log, f) {}
};

struct Sin : Function {
    Define({ return sin(f->apply(x)); });
    
    Sin(FunctionPtr f)
    : Function(Type::Sin, f) {}
};

struct Cos : Function {
    Define({ return cos(f->apply(x)); });
    
    Cos(FunctionPtr f)
    : Function(Type::Cos, f) {}
};

struct Tan : Function {
    Define({ return tan(f->apply(x)); });
    
    Tan(FunctionPtr f)
    : Function(Type::Tan, f) {}
};

struct Asin : Function {
    Define({ return asin(f->apply(x)); });
    
    Asin(FunctionPtr f)
    : Function(Type::Asin, f) {}
};

struct Acos : Function {
    Define({ return acos(f->apply(x)); });
    
    Acos(FunctionPtr f)
    : Function(Type::Acos, f) {}
};

struct Atan : Function {
    Define({ return atan(f->apply(x)); });
    
    Atan(FunctionPtr f)
    : Function(Type::Atan, f) {}
};


END_DIFFERENTIONABLE_FUNCTION_NAMESPACE

#endif
