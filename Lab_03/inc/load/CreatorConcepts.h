#pragma once

#include <concepts>
#include <type_traits>

template <typename Derived, typename Base>
concept Derivative = std::is_abstract_v<Base> && std::derived_from<Derived, Base>;

template <typename Type>
concept NotAbstract = !std::is_abstract_v<Type>;
