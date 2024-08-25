#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H
#include <iostream>
#include <type_traits>
                                       //=== Helpers ===//
template<class T, T v>
struct integral_constant
{
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant;
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

template <bool val>
using bool_constant = integral_constant<bool,val>;

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;
                                        //=== is_same ===//

template <typename T, typename U>
struct is_same : false_type {};

template<typename T>
struct is_same<T,T> : true_type {};

template <class T, class U>
constexpr bool is_same_v = is_same<T,U>::value; 
                                        //=== remove_const, remove_volatile ===//
template <typename T>
struct remove_const 
{
    using type = T;
};

template<typename T>
struct remove_const<const T>
{
    using type = T;
};

template <typename T>
struct remove_volatile
{
    using type = T;
};

template<typename T>
struct remove_volatile<volatile T>
{
    using type = T;
};


template <class T>
using remove_const_t = typename remove_const<T>::type;

template <class T>
using remove_volatile_t = typename remove_volatile<T>::type; 

                                        //=== remove_cv ===//
template <typename T>
struct remove_cv
{
    using type = typename remove_volatile<typename remove_const<T>::type>::type;
};

template <class T>
using remove_cv_t = typename remove_cv<T>::type;

                                        //=== add_cv, add_const, add_volatile ===//

template <typename T>
struct add_const
{
    using type = const typename remove_const<T>::type;
};

template <typename T>
struct add_volatile
{
    using type = volatile typename remove_volatile<T>::type;
};

template <typename T>
struct add_cv
{
    using type = const volatile typename remove_cv<T>::type;
};

template <class T>
using add_cv_t = typename add_cv<T>::type; 

template <class T>
using add_const_t = typename add_const<T>::type; 

template <class T>
using add_volatile_t = typename add_volatile<T>::type; 
                                        //=== remove_reference ===//
template <typename T>
struct remove_reference
{
    using type = T;
};

template <typename T>
struct remove_reference<T&>
{
    using type = T;
};

template <typename T>
struct remove_reference<T&&>
{
    using type = T;
};

template <class T>
using remove_reference_t = typename remove_reference<T>::type; 

                                        //=== add lvalue_reference ===//
template <typename T>
struct add_lvalue_reference
{
    using type = typename remove_reference<T>::type &;
};

template <typename T>
using add_lvalue_reference_t = add_lvalue_reference<T>::type; 

                                        //=== add_rvalue_reference ===//
template <typename T>
struct add_rvalue_reference
{
    using type = typename remove_reference<T>::type &&;
};

template <typename T>
using add_rvalue_reference_t = add_rvalue_reference<T>::type; 

                                        //=== remove_pointer ===//
template <typename T>
struct remove_pointer
{
    using type = T;
};

template <typename T>
struct remove_pointer<T*>
{
    using type = T;
};


template <typename T>
using remove_pointer_t = remove_pointer<T>::type; 
                                        //=== add_pointer ===//
template <typename T>
struct add_pointer
{
    using type = typename remove_pointer<T>::type *;
};

template <typename T>
using add_pointer_t = add_pointer<T>::type; 

                                        //=== is_void ===//
template <typename T>
struct is_void : is_same<void, typename remove_cv<T>::type> {};

template<class T>
constexpr bool is_void_v = is_void<T>::value; 
                                        //=== is_pointer ===//
template <typename T>
struct is_pointer : false_type {};

template <typename T>
struct is_pointer<T*> : true_type {};

template <typename T>
struct is_pointer<T* const> : true_type {};

template <typename T>
struct is_pointer<T* volatile> : true_type {};

template <typename T>
struct is_pointer<T* const volatile> : true_type {};

template <class T>
constexpr bool is_pointer_v = is_pointer<T>::value; 
                                        //=== is_nullptr_t ===//
template <typename T>
struct is_nullptr_pointer : is_same<std::nullptr_t, typename remove_cv<T>::type> {};

template<class T>
constexpr bool is_null_pointer_v = std::is_null_pointer<T>::value;
                                        //=== is_integral ===//
template<class T>
struct is_integral : bool_constant<  
requires (T ob, T* ptr, void (*f)(T))
{

    ptr + ob;
    reinterpret_cast<T>(ob); 
    f(0);
}> {};
template< class T >
constexpr bool is_integral_v = is_integral<T>::value;

                                        //=== is_floating_point ===//
template <typename T>
struct is_floating_point
{
    static constexpr bool value = is_same<float,typename remove_cv<T>::type>::value ||  is_same<double,typename remove_cv<T>::type>::value || is_same<long double,typename remove_cv<T>::type>::value;
}; 

template<class T>
constexpr bool is_floating_point_v = is_floating_point<T>::value; 

                                        //=== is_array ===//
template <typename T>
struct is_array : false_type {};

template <typename T>
struct is_array<T[]> : true_type {};

template <typename T, size_t N>
struct is_array<T[N]> : true_type {};

template <class T>
constexpr bool is_array_v = is_array<T>::value; 

                                        //=== is_lvalue_reference ===//
template <typename T>
struct is_lvalue_reference : false_type {};

template <typename T>
struct is_lvalue_reference<T&> : true_type {};

template <typename T>
struct is_lvalue_reference<T&&> : false_type {};

template <class T>
constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value; 

                                        //=== is_rvalue_reference ===//
template <typename T>
struct is_rvalue_reference : false_type {};

template <typename T>
struct is_rvalue_reference<T&> : false_type {};

template <typename T>
struct is_rvalue_reference<T&&> : true_type {};

template <class T>
constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value; 


                                        //=== is_reference ===//
template <typename T>
struct is_reference : false_type {};

template <typename T>
struct is_reference<T&> : true_type {};

template <typename T>
struct is_reference<T&&> : true_type {};

template <class T>
constexpr bool is_reference_v = is_reference<T>::value; 

                                        //=== is_member_object_pointer ===//
template <typename T>
struct is_member_object_pointer : std::integral_constant<bool , std::is_member_pointer_v<T> && !std::is_member_function_pointer_v<T>>
{};

template <class T>
constexpr bool is_member_object_pointer_v = is_member_object_pointer<T>::value;
                                        //=== is_member_function_pointer ===//
template <typename T>
struct is_member_function_pointer : false_type {};

template <typename T, typename U>
struct is_member_function_pointer<T U::*> : std::is_member_function_pointer<T> {};

template <class T>
constexpr bool is_member_function_pointer_v = is_member_function_pointer<T>::value;
                                        //=== is_member_pointer ===//
template <typename T>
struct is_member_pointer : false_type {};

template <typename T, typename U>
struct is_member_pointer<T U::*> : true_type {};

template <class T>
constexpr bool is_member_pointer_v = is_member_pointer<T>::value; 

                                        //=== is_fundamental ===//
template <typename T>
struct is_fundamental  : integral_constant<bool,std::is_arithmetic_v<T> || is_void_v<T> || std::is_same_v<std::nullptr_t , std::remove_cv_t<T>>>
{}; 

template <class T>
constexpr bool is_fundamental_v = is_fundamental<T>::value; 
                                        //=== is_arithmetic ===//
template <typename T>
struct is_arithmetic : std::integral_constant<bool, std::is_integral_v<T> || std::is_floating_point_v<T>> {};
                                        //=== is_scalar ===//
template <typename T>
struct is_scalar : std::integral_constant<bool,std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_pointer_v<T> || std::is_enum_v<T>> {};
                                        //=== is_object ===//
template <typename T>
struct is_object : std::integral_constant<bool,std::is_array_v<T> || std::is_enum_v<T> || std::is_class_v<T> || std::is_union_v<T>> {};

template <class T>
constexpr bool is_object_v = is_object<T>::value;
                                        //=== is_signed ===//
template <typename T>
struct is_signed : std::integral_constant<bool,std::is_signed_v<T>>{};

template <typename T>
constexpr bool is_signed_v = is_signed<T>::value;

                                        //=== is_unsigned ===//

template <typename T>
struct is_unsigned : std::integral_constant<bool , std::is_unsigned_v<T>>{};

template <class T>
constexpr bool is_unsigned_v = is_unsigned<T>::value; 

                                        //=== is_const ===//
template <typename T>
struct is_const : false_type {};

template <typename T>
struct is_const<const T> : true_type {};

                                        //=== is_volatile ===//
template <typename T>
struct is_volatile : false_type {};

template <typename T>
struct is_volatile<volatile T> : true_type {};

                                        //=== enable_if ===//
template<bool B, class T = void>
struct enable_if 
{
    using type = T;
};

template<typename T>
struct enable_if<false, T> {};

template <bool B , typename T = void>
using enable_if_t = typename enable_if<B,T>::type; 

                                        //=== remove_cvref ===//
template <typename T>
struct remove_cvref
{
    using type = typename remove_cv<typename remove_reference<T>::type>::type;
};

template <typename T>
using remove_cvref_t = remove_cvref<T>::type; 


                                        //=== conditional ===//

template <bool value , typename U , typename T>
struct conditional 
{
    using type = U; 
}; 

template <typename U, typename T>
struct conditional<false , U , T>
{
    using type = T;
};

template <bool B, typename U, typename T>
using conditional_t = conditional<B,U,T>::type; 


                                        //=== remove_extent ===//
template <typename T>
struct remove_extent 
{
    using type = T;
};

template <typename T>
struct remove_extent<T[]> 
{
    using type = T;
};

template <typename T, std::size_t N>
struct remove_extent<T[N]> 
{
    using type = T;
};

template <typename  T>
using remove_extent_t = remove_extent<T>::type;


                                        //=== remove_all_extent ===//
template <typename T>
struct remove_all_extents 
{
    using type = T;
};

template <typename T>
struct remove_all_extents<T[]> 
{
    typedef typename remove_all_extents<T>::type type;
};

template <typename T, std::size_t N>
struct remove_all_extents<T[N]> 
{
    typedef typename remove_all_extents<T>::type type;
};

template <typename T>
using remove_all_extents_t = typename remove_all_extents<T>::type;


                                        //=== decay ===//
template <typename T>
struct decay {
private:
    using U = std::remove_reference_t<T>;
    using V = std::remove_cv_t<U>;
    
public:
    using type = std::conditional_t<
        std::is_function_v<V>,
        add_pointer_t<V>, 
        conditional_t<
            is_array_v<V>, 
            add_pointer_t<remove_extent_t<V>>, 
            V
        >
    >;
};

template <typename T>
using decay_t = typename decay<T>::type;


                                        //===  is_default_constructible  ===//
template <typename T>
struct is_default_constructible : std::is_constructible<T> {};

                                        //=== is_trivially_default_constructible ===//
template <typename T>
struct is_trivially_default_constructible : std::is_trivially_constructible<T> {};

                                        //=== is_nothrow_default_constructible ===//
template <typename T>
struct is_nothrow_default_constructible : std::is_nothrow_constructible<T> {};

template< class T >
constexpr bool is_default_constructible_v = is_default_constructible<T>::value;

template< class T >
constexpr bool is_trivially_default_constructible_v = is_trivially_default_constructible<T>::value;

template< class T >
constexpr bool is_nothrow_default_constructible_v =  is_nothrow_default_constructible<T>::value;


                                        //=== is_copy_constructible ===//

template <typename T>
struct is_copy_constructible : std::is_constructible<T, add_lvalue_reference_t<add_const_t<T>>> {};
                                        //=== is_trivially_copy_constructible ===//

template <typename T>
struct is_trivially_copy_constructible : std::is_trivially_constructible<T, add_lvalue_reference_t<add_const_t<T>>> {};
                                        //=== is_nothrow_copy_constructible ===//

template <typename T>
struct is_nothrow_copy_constructible : std::is_nothrow_constructible<T, add_lvalue_reference_t<add_const_t<T>>>  {};


template< class T >
constexpr bool is_copy_constructible_v = is_copy_constructible<T>::value;

template< class T >
constexpr bool is_trivially_copy_constructible_v =is_trivially_copy_constructible<T>::value;

template< class T >
constexpr bool is_nothrow_copy_constructible_v = is_nothrow_copy_constructible<T>::value;

                                        //=== is_move_constructible ===//

template <typename T>
struct is_move_constructible : std::is_constructible<T, add_rvalue_reference_t<T>> {};
                                        //=== is_trivially_move_constructible ===//

template <typename T>
struct is_trivially_move_constructible : std::is_trivially_constructible<T, add_rvalue_reference_t<T>> {};
                                        //=== is_nothrow_move_constructible ===//

template <typename T>
struct is_nothrow_move_constructible: std::is_nothrow_constructible<T, add_rvalue_reference_t<T>> {};

template< class T >
constexpr bool is_move_constructible_v = is_move_constructible<T>::value;

template< class T >
constexpr bool is_trivially_move_constructible_v = is_trivially_move_constructible<T>::value;

template< class T >
constexpr bool is_nothrow_move_constructible_v = is_nothrow_move_constructible<T>::value;


                                        //=== is_copy_assignable ===//
template <typename T>
struct is_copy_assignable : std::is_assignable<add_lvalue_reference_t<T> , add_lvalue_reference_t<const T>>{};
                                        //=== is_trivially_copy_assignable ===//
template <typename T>
struct is_trivially_copy_assignable : std::is_trivially_assignable<add_lvalue_reference_t<T>, add_lvalue_reference_t<const T>>{};
                                        //=== is_nothrow_copy_assignable ===//
template <typename T>
struct is_nothrow_copy_assignable : std::is_nothrow_assignable<add_lvalue_reference_t<T> , add_lvalue_reference_t<const T>> {};

template< class T >
constexpr bool is_copy_assignable_v = is_copy_assignable<T>::value;

template< class T >
constexpr bool is_trivially_copy_assignable_v = is_trivially_copy_assignable<T>::value;

template< class T >
constexpr bool is_nothrow_copy_assignable_v = is_nothrow_copy_assignable<T>::value;


                                        //=== is_move_assignable ===//

template <typename T>
struct is_move_assignable : std::is_assignable<add_lvalue_reference_t<T> , add_rvalue_reference_t<T>> {};
                                        //=== is_trivially_move_assignable ===//

template <typename T>
struct is_trivially_move_assignable : std::is_trivially_assignable<add_lvalue_reference_t<T> , add_rvalue_reference_t<T>>{};
                                        //=== is_nothrow_move_assignable ===//

template <typename T>
struct is_nothrow_move_assignable : std::is_nothrow_assignable<add_lvalue_reference_t<T> , add_rvalue_reference_t<T>>{};

template< class T >
constexpr bool is_move_assignable_v =  is_move_assignable<T>::value;

template< class T >
constexpr bool is_trivially_move_assignable_v = is_trivially_move_assignable<T>::value;

template< class T >
constexpr bool is_nothrow_move_assignable_v = is_nothrow_move_assignable<T>::value;

                                        //=== is_nothrow_move_assignable ===//
template <typename T>
struct is_compound : integral_constant<bool , !is_fundamental_v<T>>{};

template< class T >
constexpr bool is_compound_v = is_compound<T>::value;

                                        //=== is_polymorphic ===//

template <typename T>
struct is_polymorphic_helper {
private:

    struct Derived : T {
        virtual void dummy() {}
    };

    static std::true_type test(Derived*);
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test(static_cast<T*>(nullptr)))::value;
};

template <typename T>
struct is_polymorphic : integral_constant<bool , is_polymorphic_helper<T>::value>
{};

template< class T >
constexpr bool is_polymorphic_v = is_polymorphic<T>::value;

#endif