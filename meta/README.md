`template` metaprogramming

# Synopsis

## base.hpp

```C++
template <class T, T t> struct constant;

using true_type  = constant<bool, true>;
using false_type = constant<bool, false>;
```

## check.hpp

```C++
template <class T, class U> struct is_same;
template <class T, class U> constexpr inline bool is_same_v = is_same<T, U>::value;

template <class T> struct is_void;
template <class T> constexpr inline bool is_void_v = is_void<T>::value;

template <class Base, class Derived> struct is_base_of;
template <class B, class D> constexpr inline bool is_base_of_v = is_base_of<B, D>::value;

template <class T> struct is_class;
template <class T> constexpr inline bool is_class_v = is_class<T>::value;

template <class T> struct is_empty;
template <class T> constexpr inline bool is_empty_v = is_empty<T>::value;

template <class T, template <class...> class Template> struct is_instance_of;
template <class T, template <class...> class Template> constexpr inline bool is_instance_of_v = is_instance_of<T, Template>::value;
```

## common_type.hpp

```C++
template <class ...Args> struct common_type;

template <class ...Args>
using common_type_t = typename common_type<Args...>::type;
```

## condition.hpp

```C++
template <bool B, class T, class F> struct condition;

template <bool B, class T, class F>
using condition_t = typename condition<B, T, F>::type;
```

## constructible.hpp

```C++
template <class T, class ...Args> struct is_constructible;
```

## cv.hpp

```C++
template <class T> struct remove_const;
template <class T> using remove_const_t = typename remove_const<T>::type;

template <class T> struct remove_volatile;
template <class T> using remove_volatile_t = typename remove_volatile<T>::type;

template <class T> struct remove_cv;
template <class T> using remove_cv_t = typename remove_cv<T>::type;

template <class T> struct add_const;
template <class T> using add_const_t = typename add_const<T>::type;

template <class T> struct add_volatile;
template <class T> using add_volatile_t = typename add_volatile<T>::type;

template <class T> struct is_const;
template <class T> constexpr inline bool is_const_v = is_const<T>::value;

template <class T> struct is_volatile;
template <class T> constexpr inline bool is_volatile_v = is_volatile<T>::value;
```

## decay.hpp

```C++
template<class T> struct decay;

template <class T> using decay_t = typename decay<T>::type;
```

## identity.hpp

```C++
template <class T> struct identity;

template <class T>
using identity_t = typename identity<T>::type;
```

## index_sequence.hpp

```C++
template <unsigned...> struct index_sequence;

template <unsigned N>
using make_index_sequence_t = typename make_index_sequence<N>::type;
```

## is_function.hpp

```C++
template <class T> struct is_function;
```

## logic.hpp

```C++
template <class B> struct not_;
template <class...> struct or_ ;
template <class...> struct and_;
```

## ref.hpp

```C++
template <class T> struct remove_extent;
template <class T> using  remove_extent_t = typename remove_extent<T>::type;

template <class T> struct remove_reference;
template <class T> using  remove_reference_t = typename remove_reference<T>::type;

template <class T> struct remove_pointer;
template <class T> using  remove_pointer_t = typename remove_pointer<T>::type;

template <class T> struct add_pointer;
template <class T> using  add_pointer_t = typename add_pointer<T>::type;

template <class T> struct add_reference;
template <class T> using  add_reference_t = typename add_reference<T>::type;

template <class T> struct add_rvalue_reference;
template <class T> using  add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

template <class T> struct is_reference;
template <class T> constexpr inline bool is_reference_v = is_reference<T>::value;

template <class T> struct is_lvalue_reference;
template <class T> constexpr inline bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

template <class T> struct is_rvalue_reference;
template <class T> constexpr inline bool is_rvalue_reference_v = is_rvalue_reference<T>::value;

template <class T> struct is_pointer;
template <class T> constexpr inline bool is_pointer_v = is_pointer<T>::value;

template <class T> struct is_array;
template <class T> constexpr inline bool is_array_v = is_array<T>::value;
```

## sfinae.hpp

```C++
template <class...> struct void_type;
template <class ...Args> using void_t = typename void_type<Args...>::type;

template <bool B, class T = void> struct enable_if;
template <bool B, class T = void>
using enable_if_t = typename enable_if<B, T>::type;

template <class ...Args>
using satisfied = typename enable_if<
    and_<Args...>::value
>::type;

template <template <class...> class Detector, class ...Args>
struct is_detected;

template <template <class...> class Detector, class ...Args>
constexpr inline bool is_detected_v = is_detected<Detector, Args...>::value;
```

## variadic_concat.hpp

```C++
template <class, class> struct variadic_concat;
```
