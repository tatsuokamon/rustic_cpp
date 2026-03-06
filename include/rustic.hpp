#include <variant>
#include <utility>

template<class T>
struct Ok {
    T _value;
    Ok(T&&);
};

template<class E>
struct Err {
    E _value;
    Err(E&&);
};

template<class T, class E>
class Result {

    std::variant<Ok<T>, Err<E>> data;

public:

    Result(Ok<T>&&);
    Result(Err<E>&& err);

    bool is_ok() const;
    bool is_err() const;

    T unwrap() &&;
    T expect(const char*) &&;

};
