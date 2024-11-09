#pragma once

#include <tuple>
#include <functional>

template <typename... Args>
using args = std::tuple<std::function<Args()>...>;

template <typename... Args, std::size_t... I>
std::tuple<Args...> generate_args_for(args<Args...> arguments, std::index_sequence<I...> indices) {
  return std::tuple<Args...> { std::get<I>(arguments)()... };
}

template <typename... Args>
std::tuple<Args...> generate_args(args<Args...> arguments) {
  return generate_args_for<Args...>(arguments, std::index_sequence_for<Args...>());
}

template <typename Res, typename... Args>
void magictest(
  std::type_identity_t<std::function<void(Res, Args...)>> check,
  std::type_identity_t<std::function<Res(Args...)>> function,
  args<Args...> arguments
) {
  std::tuple<Args...> args = generate_args(arguments);
  Res result = std::apply(function, args);
  std::tuple<Res, Args...> check_args = std::tuple_cat(
    std::tuple<Res> { result },
    args
  );
  std::apply(check, check_args);
}
