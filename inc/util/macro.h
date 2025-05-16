#pragma once
#define ATTRIBUTER template<typename> typename // describes an attribute of a class. eg std::tuple_size
#define TRANSFORM template<typename> typename // has 'type' eg std::add_const
#define PREDICATE template<typename> typename // has bool 'value' eg std::is_const
#define COMPARE template<typename, typename> typename // has bool 'value' eg std::is_same
#define CONTAINER template<typename...> typename // has n type args... eg std::tuple

// TODO: descriptions