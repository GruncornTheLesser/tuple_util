#pragma once
#ifndef TUPLE_UTIL_NAMESPACE
#define TUPLE_UTIL_NAMESPACE tuple_util
#endif
#ifndef TUPLE_UTIL_DEFAULT_CONTAINER
#define TUPLE_UTIL_DEFAULT_CONTAINER std::tuple
#endif
#ifndef TUPLE_UTIL_DEFAULT_ATTRIBUTER
#define TUPLE_UTIL_DEFAULT_ATTRIBUTER get_value
#endif

#define CONTAINER template<typename...> typename // has n type args... eg std::tuple
#define ATTRIBUTER template<typename> typename // describes an attribute of a class. eg std::tuple_size
#define TRANSFORM template<typename> typename // has 'type' eg std::add_const
#define PREDICATE template<typename> typename // has bool 'value' eg std::is_const
#define COMPARE template<typename, typename> typename // has bool 'value' eg std::is_same

// TODO: descriptions