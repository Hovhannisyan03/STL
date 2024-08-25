#ifndef CONCEPT_H
#define CONCEPT_H

#include "../Type traits/type_traits.h"
                                        // === same_as === //
template <typename T, typename U>
concept same_as = is_same_v<T, U> || is_same_v<U,T>;

                                        // === derived_from === //
template <typename Derived, typename Base>
concept derived_from = std::is_base_of_v<Base, Derived> && !std::is_same_v<Derived, Base>;

                                        // === convertible_to === //
template <typename From, typename To>
concept convertible_to = std::is_convertible_v<From, To>;
                                        // === integral === //
template <typename T>
concept integral = is_integral_v<T>;

                                        // === common_reference_with=== //
template <typename T, typename U>
concept common_reference_with = std::same_as<std::common_reference_t<T, U>, std::common_reference_t<U, T>> && std::convertible_to<T, std::common_reference_t<T, U>> && std::convertible_to<U, std::common_reference_t<T, U>>;
                                        // === signed_integral === //
template <typename T>
concept signed_integral = is_integral_v<T> && is_signed_v<T>;


                                        // === unsigned_integral === //
template <typename T>
concept unsigned_integral = is_integral_v<T> && is_unsigned_v<T>;


                                        // === floating_point === //
template <typename T>
concept floating_point = is_floating_point_v<T>;


                                        // === destructable === //
template <typename T>
concept destructable = std::is_nothrow_destructible_v<T>;


                                        // === default_initializable === //
template <typename T>
concept default_initializable = is_default_constructible_v<T> && requires {T{}; new T;};


                                        // === move_constructible === //
template <typename T>
concept  move_constructible = is_move_constructible_v<T> && requires(T ob1 , T ob2) {ob1 = std::move(ob2);};



                                        // === copy_constructible === //
template <typename T>
concept copy_constructible  = is_copy_constructible_v<T> and requires(T ob1 , T ob2) {ob1 = ob2;};  


                                        // === moveable === //
template <typename T>
concept moveable = is_object_v<T>
                    && move_constructible<T> 
                    && std::assignable_from<T&, T> 
                    && std::swappable<T>;

                                        // === copyable === //
template <typename T>
concept copyable = is_object_v<T>
                    && std::copy_constructible<T>
                    && moveable<T> 
                    && std::assignable_from<T&, T&> 
                    && std::assignable_from<T&, const T&>
                    && std::assignable_from<T&, const T>;


                                        // === semiregular === //
template <typename T>
concept semiregular = copyable<T> && default_initializable<T>;

#endif  