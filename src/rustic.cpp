#include <cstdlib>
#include <iostream>
#include <rustic.hpp>
#include <stdexcept>
#include <utility>
#include <variant>

template<typename T>
Ok<T>::Ok(T&& t) : _value(std::move(t)) {}

template<typename T>
T Ok<T>::value() && {
	return std::move(_value);
}

template<typename T>
Err<T>::Err(T&& t) : _value(std::move(t)) {}

template<typename E>
E Err<E>::value() && {
	return std::move(_value);
}

template <typename T, typename E>
bool Result<T, E>::is_ok() const {
        return std::holds_alternative<Ok<T>>(data);
}

template <typename T, typename E>
bool Result<T, E>::is_err() const {
        return std::holds_alternative<Ok<T>>(data);
}

template <typename T, typename E>
T Result<T, E>::unwrap() && {
        if (is_err()) {
		std::cout << "failed: " << std::get<Err<E>>(data).value() ;
		std::exit(1);
        }

        return std::move(std::get<Ok<T>>(data).value);
}

template<typename T, typename E>
T Result<T, E>::expect(const char* msg) && {
        if (is_err()) {
            throw std::runtime_error(msg);
        }

        return std::move(std::get<Ok<T>>(data).value);
}

template<typename T, typename E>
Result<T, E>::Result(Ok<T>&& ok) : data(std::move(ok)) {}

template<typename T, typename E>
Result<T, E>::Result(Err<E>&& err) : data(std::move(err)) {}

template<typename T, typename E>
T Result<T, E>::propagate() && {
        if (is_err()) {
            throw std::runtime_error("called unwrap on Err");
        }

        return std::move(std::get<Ok<T>>(data).value);
}
