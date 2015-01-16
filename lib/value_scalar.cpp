#include <cmath>
#include <iostream>
#include "atidlas/array.h"
#include "atidlas/value_scalar.h"

namespace atidlas
{

void value_scalar::init(scalar const & s)
{
  switch(dtype_)
  {
    case CHAR_TYPE: values_.int8 = s;
    case UCHAR_TYPE: values_.uint8 = s;
    case SHORT_TYPE: values_.int16 = s;
    case USHORT_TYPE: values_.uint16 = s;
    case INT_TYPE: values_.int32 = s;
    case UINT_TYPE: values_.uint32 = s;
    case LONG_TYPE: values_.int64 = s;
    case ULONG_TYPE: values_.uint64 = s;
    case FLOAT_TYPE: values_.float32 = s;
    case DOUBLE_TYPE: values_.float64 = s;
    default: throw;
  }
}

value_scalar::value_scalar(cl_char value) : dtype_(CHAR_TYPE) { values_.int8 = value; }
value_scalar::value_scalar(cl_uchar value) : dtype_(UCHAR_TYPE) { values_.uint8 = value; }
value_scalar::value_scalar(cl_short value) : dtype_(SHORT_TYPE) { values_.int16 = value; }
value_scalar::value_scalar(cl_ushort value) : dtype_(USHORT_TYPE) { values_.uint16 = value; }
value_scalar::value_scalar(cl_int value) : dtype_(INT_TYPE) { values_.int32 = value; }
value_scalar::value_scalar(cl_uint value) : dtype_(UINT_TYPE) { values_.uint32 = value; }
value_scalar::value_scalar(cl_long value) : dtype_(LONG_TYPE) { values_.int64 = value; }
value_scalar::value_scalar(cl_ulong value) : dtype_(ULONG_TYPE) { values_.uint64 = value; }
//value_scalar::value_scalar(cl_half value) : dtype_(HALF_TYPE) { values_.float16 = value; }
value_scalar::value_scalar(cl_float value) : dtype_(FLOAT_TYPE) { values_.float32 = value; }
value_scalar::value_scalar(cl_double value) : dtype_(DOUBLE_TYPE) { values_.float64 = value; }
value_scalar::value_scalar(numeric_type dtype) : dtype_(dtype) {}
value_scalar::value_scalar(scalar const & s) : dtype_(s.dtype()) { init(s); }
value_scalar::value_scalar(array_expression const &expr) : dtype_(expr.dtype()) { init(scalar(expr)); }

values_holder value_scalar::values() const
{ return values_; }

numeric_type value_scalar::dtype() const
{ return dtype_; }

template<class T>
T value_scalar::cast() const
{
  switch(dtype_)
  {
    case CHAR_TYPE: return values_.int8;
    case UCHAR_TYPE: return values_.uint8;
    case SHORT_TYPE: return values_.int16;
    case USHORT_TYPE: return values_.uint16;
    case INT_TYPE: return values_.int32;
    case UINT_TYPE: return values_.uint32;
    case LONG_TYPE: return values_.int64;
    case ULONG_TYPE: return values_.uint64;
//    case HALF_TYPE: return values_.float16;
    case FLOAT_TYPE: return values_.float32;
    case DOUBLE_TYPE: return values_.float64;
    default: throw; //unreachable
  }
}

#define INSTANTIATE(type) value_scalar::operator type() const { return cast<type>(); }
  INSTANTIATE(cl_char)
  INSTANTIATE(cl_uchar)
  INSTANTIATE(cl_short)
  INSTANTIATE(cl_ushort)
  INSTANTIATE(cl_int)
  INSTANTIATE(cl_uint)
  INSTANTIATE(cl_long)
  INSTANTIATE(cl_ulong)
  INSTANTIATE(cl_float)
  INSTANTIATE(cl_double)
#undef INSTANTIATE

value_scalar int8(cl_char v) { return value_scalar(v); }
value_scalar uint8(cl_uchar v) { return value_scalar(v); }
value_scalar int16(cl_short v) { return value_scalar(v); }
value_scalar uint16(cl_ushort v) { return value_scalar(v); }
value_scalar int32(cl_int v) { return value_scalar(v); }
value_scalar uint32(cl_uint v) { return value_scalar(v); }
value_scalar int64(cl_long v) { return value_scalar(v); }
value_scalar uint64(cl_ulong v) { return value_scalar(v); }
value_scalar float32(cl_float v) { return value_scalar(v); }
value_scalar float64(cl_double v) { return value_scalar(v); }

#define VALUE(type, OP, x, y) (type)x OP y
#define INSTANTIATE(NAME, LDEC, RDEC, OP)\
value_scalar NAME(LDEC, RDEC)\
{\
  switch(x.dtype())\
  {\
  case CHAR_TYPE: return VALUE(cl_char, OP, x, y);\
  case UCHAR_TYPE: return VALUE(cl_uchar, OP, x, y);\
  case SHORT_TYPE: return VALUE(cl_short, OP, x, y);\
  case USHORT_TYPE: return VALUE(cl_ushort, OP, x, y);\
  case INT_TYPE: return VALUE(cl_int, OP, x, y);\
  case UINT_TYPE: return VALUE(cl_uint, OP, x, y);\
  case LONG_TYPE: return VALUE(cl_long, OP, x, y);\
  case ULONG_TYPE: return VALUE(cl_ulong, OP, x, y);\
  case FLOAT_TYPE: return VALUE(cl_float, OP, x, y);\
  case DOUBLE_TYPE: return VALUE(cl_double, OP, x, y);\
  default: throw;\
  }\
}

#define INSTANTIATE_ALL(NAME, EXPR)\
  INSTANTIATE(NAME, value_scalar const & x, cl_char y, EXPR)\
  INSTANTIATE(NAME, value_scalar const & x, cl_uchar y, EXPR)\
  INSTANTIATE(NAME, value_scalar const & x, cl_short y, EXPR)\
  INSTANTIATE(NAME, value_scalar const & x, cl_ushort y, EXPR)\
  INSTANTIATE(NAME, value_scalar const & x, cl_int y, EXPR)\
  INSTANTIATE(NAME, value_scalar const & x, cl_uint y, EXPR)\
  INSTANTIATE(NAME, value_scalar const & x, cl_long y, EXPR)\
  INSTANTIATE(NAME, value_scalar const & x, cl_ulong y, EXPR)\
  INSTANTIATE(NAME, value_scalar const & x, cl_float y, EXPR)\
  INSTANTIATE(NAME, value_scalar const & x, cl_double y, EXPR)\
  INSTANTIATE(NAME, cl_char y,   value_scalar const & x, EXPR)\
  INSTANTIATE(NAME, cl_uchar y,  value_scalar const & x, EXPR)\
  INSTANTIATE(NAME, cl_short y,  value_scalar const & x, EXPR)\
  INSTANTIATE(NAME, cl_ushort y, value_scalar const & x, EXPR)\
  INSTANTIATE(NAME, cl_int y,    value_scalar const & x, EXPR)\
  INSTANTIATE(NAME, cl_uint y,   value_scalar const & x, EXPR)\
  INSTANTIATE(NAME, cl_long y,   value_scalar const & x, EXPR)\
  INSTANTIATE(NAME, cl_ulong y,  value_scalar const & x, EXPR)\
  INSTANTIATE(NAME, cl_float y,  value_scalar const & x, EXPR)\
  INSTANTIATE(NAME, cl_double y, value_scalar const & x, EXPR)

INSTANTIATE_ALL(operator+, +)
INSTANTIATE_ALL(operator-, -)
INSTANTIATE_ALL(operator*, *)
INSTANTIATE_ALL(operator/, /)
INSTANTIATE_ALL(operator>,  > )
INSTANTIATE_ALL(operator>=, >=)
INSTANTIATE_ALL(operator<,  < )
INSTANTIATE_ALL(operator<=, <=)
INSTANTIATE_ALL(operator==, ==)
INSTANTIATE_ALL(operator!=, !=)

#undef VALUE
#define VALUE(type, OP, x, y) OP((type)x,(type)y)
INSTANTIATE_ALL(max, std::max)
INSTANTIATE_ALL(min, std::min)

#undef VALUE
#define VALUE(type, OP, x, y) OP((type)x, y)
INSTANTIATE_ALL(pow, std::pow)

#undef INSTANTIATE_ALL
#undef INSTANTIATE

std::ostream & operator<<(std::ostream & os, value_scalar const & s)
{
  switch(s.dtype())
  {
    case CHAR_TYPE: return os << static_cast<cl_char>(s);
    case UCHAR_TYPE: return os << static_cast<cl_uchar>(s);
    case SHORT_TYPE: return os << static_cast<cl_short>(s);
    case USHORT_TYPE: return os << static_cast<cl_ushort>(s);
    case INT_TYPE: return os << static_cast<cl_int>(s);
    case UINT_TYPE: return os << static_cast<cl_uint>(s);
    case LONG_TYPE: return os << static_cast<cl_long>(s);
    case ULONG_TYPE: return os << static_cast<cl_ulong>(s);
    case FLOAT_TYPE: return os << static_cast<cl_float>(s);
    case DOUBLE_TYPE: return os << static_cast<cl_double>(s);
    default: throw "";
  }
}

}
