#include <functional>
#include <type_traits>
#include "gtest.h"
#include "observable/detail/function_traits.hpp"

namespace observable { namespace detail { namespace test {

TEST(function_traits_test, can_get_function_return_type)
{
    using type = typename function_traits<double()>::return_type;
    ASSERT_TRUE((std::is_same<type, double>::value));
}

TEST(function_traits_test, can_get_function_pointer_return_type)
{
    using type = typename function_traits<double(*)()>::return_type;
    ASSERT_TRUE((std::is_same<type, double>::value));
}

TEST(function_traits_test, can_get_lambda_return_type)
{
    auto lambda = [=]() -> double { return 5.0; };
    using type = typename function_traits<decltype(lambda)>::return_type;
    ASSERT_TRUE((std::is_same<type, double>::value));
}

TEST(function_traits_test, can_get_function_arity)
{
    auto arity = function_traits<void(int, double, char)>::arity;
    ASSERT_EQ(arity, 3u);
}

TEST(function_traits_test, can_get_function_pointer_arity)
{
    auto arity = function_traits<void(*)(int, double, char)>::arity;
    ASSERT_EQ(arity, 3u);
}

TEST(function_traits_test, can_get_lambda_arity)
{
    auto lambda = [=](int, double, char) { };
    auto arity = function_traits<decltype(lambda)>::arity;
    ASSERT_EQ(arity, 3u);
}

TEST(function_traits_test, arity_is_zero_for_no_args)
{
    auto arity = function_traits<void()>::arity;
    ASSERT_EQ(arity, 0u);
}

TEST(function_traits, normalized_removes_function_pointer)
{
    using normalized = typename function_traits<void(*)(int)>::normalized;
    ASSERT_TRUE((std::is_same<normalized, void(int)>::value));
}

TEST(function_traits, normalized_extracts_lambda_signature)
{
    auto lambda = [=](int) { };
    using normalized = typename function_traits<decltype(lambda)>::normalized;
    ASSERT_TRUE((std::is_same<normalized, void(int)>::value));
}

TEST(function_traits_test, normalized_strips_parameter_refs)
{
    using normalized = typename function_traits<void(int &)>::normalized;
    ASSERT_TRUE((std::is_same<normalized, void(int &)>::value));
}

TEST(function_traits_test, normalized_strips_parameter_const)
{
    using normalized = typename function_traits<void(int const)>::normalized;
    ASSERT_TRUE((std::is_same<normalized, void(int)>::value));
}

TEST(function_traits_test, normalized_stripts_parameter_const_ref)
{
    using normalized = typename function_traits<void(int const &)>::normalized;
    ASSERT_TRUE((std::is_same<normalized, void(int)>::value));
}

TEST(function_traits_test, normalized_preserves_parameter_pointer)
{
    using normalized = typename function_traits<void(int *)>::normalized;
    ASSERT_TRUE((std::is_same<normalized, void(int *)>::value));
}

TEST(function_traits_test, normalized_preserves_parameter_const_pointer)
{
    using normalized = typename function_traits<void(int const *)>::normalized;
    ASSERT_TRUE((std::is_same<normalized, void(int const *)>::value));
}

TEST(function_traits_test, normalized_preserves_parameter_non_const_reference)
{
    using normalized = typename function_traits<void(int &)>::normalized;
    ASSERT_TRUE((std::is_same<normalized, void(int &)>::value));
}

TEST(function_traits_test, normalized_strips_parameter_pointer_const)
{
    using normalized = typename function_traits<void(int * const)>::normalized;
    ASSERT_TRUE((std::is_same<normalized, void(int *)>::value));
}

TEST(function_traits_test, normalized_strips_parameter_pointer_const_reference)
{
    using normalized = typename function_traits<void(int * const &)>::normalized;
    ASSERT_TRUE((std::is_same<normalized, void(int *)>::value));
}

TEST(function_traits_test, signature_removes_function_pointer)
{
    using signature = typename function_traits<void(*)()>::signature;
    ASSERT_TRUE((std::is_same<signature, void()>::value));
}

TEST(function_traits_test, signature_is_extracted_from_lambda)
{
    auto lambda = [=](int, double) -> char { return 'a'; };
    using signature = typename function_traits<decltype(lambda)>::signature;
    ASSERT_TRUE((std::is_same<signature, char(int, double)>::value));
}

TEST(function_traits_test, signature_preserves_arguments)
{
    using signature = typename function_traits<void(int const, char const &)>::signature;
    ASSERT_TRUE((std::is_same<signature, void(int const, char const &)>::value));
}

} } }