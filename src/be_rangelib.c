#include "be_rangelib.h"

static int m_init(bvm *vm)
{
    be_pushvalue(vm, 2);
    be_setmember(vm, 1, "__lower__");
    be_pop(vm, 1);
    be_pushvalue(vm, 3);
    be_setmember(vm, 1, "__upper__");
    return be_noreturn(vm);
}

static int m_print(bvm *vm)
{
    be_printf("(");
    be_getmember(vm, 1, "__lower__");
    be_printvalue(vm, 0, -1);
    be_printf("..");
    be_pop(vm, 1);
    be_getmember(vm, 1, "__upper__");
    be_printvalue(vm, 0, -1);
    be_printf(")");
    return be_noreturn(vm);
}

static int m_upper(bvm *vm)
{
    be_getmember(vm, 1, "__upper__");
    return be_return(vm);
}

static int m_lower(bvm *vm)
{
    be_getmember(vm, 1, "__lower__");
    return be_return(vm);
}

static int m_setrange(bvm *vm)
{
    be_pushvalue(vm, 2);
    be_setmember(vm, 1, "__lower__");
    be_pop(vm, 1);
    be_pushvalue(vm, 3);
    be_setmember(vm, 1, "__upper__");
    return be_noreturn(vm);
}

static int i_init(bvm *vm)
{
    be_pushvalue(vm, 2);
    be_setmember(vm, 1, "__obj__");
    return be_noreturn(vm);
}

static int i_hashnext(bvm *vm)
{
    be_getmember(vm, 1, "__obj__");
    be_getmember(vm, 1, "__it__");
    be_getmember(vm, -2, "__upper__");
    if (!be_isint(vm, -2) || be_toint(vm, -2) < be_toint(vm, -1)) {
        be_pushbool(vm, btrue);
    } else {
        be_pushbool(vm, bfalse);
    }
    return be_return(vm);
}

static int i_next(bvm *vm)
{
    be_getmember(vm, 1, "__it__");
    if (!be_isint(vm, -1)) {
        be_getmember(vm, 1, "__obj__");
        be_getmember(vm, -1, "__lower__");
        be_setmember(vm, 1, "__it__");
    } else {
        be_getmember(vm, 1, "__it__");
        be_pushint(vm, be_toint(vm, -1) + 1);
        be_setmember(vm, 1, "__it__");
    }
    return be_return(vm);
}

static int m_iter(bvm *vm)
{
    static const bmemberinfo members[] = {
        { "__obj__", NULL },
        { "__it__", NULL },
        { "init", i_init },
        { "hasnext", i_hashnext },
        { "next", i_next },
        { NULL, NULL }
    };
    be_pushclass(vm, "iterator", members);
    be_pushvalue(vm, 1);
    be_call(vm, 1);
    be_pop(vm, 1);
    return be_return(vm);
}

void be_range_init(bvm *vm)
{
    static const bmemberinfo members[] = {
        { "__lower__", NULL },
        { "__upper__", NULL },
        { "init", m_init },
        { "print", m_print },
        { "upper", m_upper },
        { "lower", m_lower },
        { "setrange", m_setrange },
        { "iter", m_iter },
        { NULL, NULL }
    };
    be_regclass(vm, "range", members);
}
