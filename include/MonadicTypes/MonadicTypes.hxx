// ============================================================================
// File: MonadicTypes.hxx
//
// Description:
//   Functional programming utilities providing Either monad and Result type
//   for C++.
//
//   This header provides a lightweight implementation of the Either monad,
//   commonly used in functional programming for error handling without
//   exceptions. The Either type represents a value that can be one of two
//   types: Left (conventionally used for errors) or Right (conventionally
//   used for success values).
//
// Key concepts:
//   - Either<L, R>: A sum type holding either a Left value of type L or a
//                   Right value of type R
//   - Result<T>: A specialized Either where Left is std::runtime_error
//   - mbind: Monadic bind operation for chaining computations that may fail
//   - fmap: Functor map operation for transforming the Right value
//
// Example:
//     using namespace MonadicTypes;
//
//     Result<int> divide(int a, int b) {
//         if (b == 0) {
//             return Result<int>(std::in_place_index<0>,
//                                std::runtime_error("Division by zero"));
//         }
//         return validate(a / b);
//     }
//
//     auto result = divide(10, 2)
//         | [](int x) { return validate(x * 2); }
//         | [](int x) { return validate(x + 1); };
//
//     if (isRight(result)) {
//         std::cout << "Result: " << value(result) << std::endl;
//         // Output: Result: 11
//     }
//
// ============================================================================

#pragma once

#include <functional>   // std::invoke
#include <stdexcept>    // std::runtime_error
#include <type_traits>  // std::invoke_result_t
#include <utility>      // std::forward, std::move
#include <variant>      // std::variant, std::get, std::in_place_index

namespace MonadicTypes {

    // ------------------------------------------------------------------------
    // DefaultErr
    // ------------------------------------------------------------------------
    // Description:
    //   Default error type used by the Result type alias.
    //   Using std::runtime_error allows for descriptive error messages.
    // ------------------------------------------------------------------------
    using DefaultErr = std::runtime_error;

    // ------------------------------------------------------------------------
    // Either<L, R>
    // ------------------------------------------------------------------------
    // Description:
    //   A sum type representing a value that is either Left (L) or Right (R).
    //   Either is the fundamental building block for railway-oriented
    //   programming.
    //
    //   By convention:
    //     - Left (index 0) holds error/failure values
    //     - Right (index 1) holds success values
    //
    //   This follows the Haskell convention where "right" is "correct".
    //
    // Template parameters:
    //   L - The type of the Left value (typically an error type)
    //   R - The type of the Right value (typically a success type)
    //
    // Example:
    //     Either<std::string, int> success =
    //         Either<std::string, int>(std::in_place_index<1>, 42);
    //     Either<std::string, int> failure =
    //         Either<std::string, int>(std::in_place_index<0>, "error");
    // ------------------------------------------------------------------------
    template <typename L, typename R>
    using Either = std::variant<L, R>;

    // ------------------------------------------------------------------------
    // Result<T>
    // ------------------------------------------------------------------------
    // Description:
    //   A specialized Either type for computations that may fail with a
    //   runtime error. Result<T> is a convenient alias for Either<DefaultErr,
    //   T>, providing a standard way to represent operations that may fail
    //   with an error message.
    //
    // Template parameters:
    //   T - The type of the success value
    //
    // Example:
    //     Result<int> parseNumber(const std::string& s) {
    //         try {
    //             return validate(std::stoi(s));
    //         } catch (...) {
    //             return Result<int>(std::in_place_index<0>,
    //                                std::runtime_error("Invalid number"));
    //         }
    //     }
    //
    // ------------------------------------------------------------------------
    template <typename T>
    using Result = Either<DefaultErr, T>;

    // ------------------------------------------------------------------------
    // isRight
    // ------------------------------------------------------------------------
    // Description:
    //   Checks if the Either contains a Right value (success case).
    //
    // Template parameters:
    //   L - The Left type of the Either
    //   R - The Right type of the Either
    //
    // Parameters:
    //   either - The Either instance to check
    //
    // Returns:
    //   true if the Either contains a Right value, false otherwise
    //
    // Example:
    //     Either<std::string, int> e =
    //         Either<std::string, int>(std::in_place_index<1>, 42);
    //     if (isRight(e)) {
    //         std::cout << "Success!" << std::endl;
    //     }
    // ------------------------------------------------------------------------
    template <typename L, typename R>
    constexpr bool isRight(Either<L, R> const& either) {
        return either.index() == 1;
    }

    // ------------------------------------------------------------------------
    // isLeft
    // ------------------------------------------------------------------------
    // Description:
    //   Checks if the Either contains a Left value (error case).
    //
    // Template parameters:
    //   L - The Left type of the Either
    //   R - The Right type of the Either
    //
    // Parameters:
    //   either - The Either instance to check
    //
    // Returns:
    //   true if the Either contains a Left value, false otherwise
    //
    // Example:
    //     Either<std::string, int> e =
    //         Either<std::string, int>(std::in_place_index<0>, "error");
    //     if (isLeft(e)) {
    //         std::cout << "Failure!" << std::endl;
    //     }
    // ------------------------------------------------------------------------
    template <typename L, typename R>
    constexpr bool isLeft(Either<L, R> const& either) {
        return either.index() == 0;
    }

    // ------------------------------------------------------------------------
    // getRight
    // ------------------------------------------------------------------------
    // Description:
    //   Extracts the Right value from an Either.
    //
    // Warning:
    //   This function does not check if the Either actually contains a Right
    //   value. Calling this on an Either containing a Left value results in
    //   undefined behavior. Always use isRight() to check before calling.
    //
    // Template parameters:
    //   L - The Left type of the Either
    //   R - The Right type of the Either
    //
    // Parameters:
    //   either - The Either instance to extract from
    //
    // Returns:
    //   A const reference to the Right value
    //
    // Example:
    //     Either<std::string, int> e =
    //         Either<std::string, int>(std::in_place_index<1>, 42);
    //     if (isRight(e)) {
    //         int val = getRight(e);  // val == 42
    //     }
    // ------------------------------------------------------------------------
    template <typename L, typename R>
    constexpr const R& getRight(Either<L, R> const& either) {
        return std::get<1>(either);
    }

    // ------------------------------------------------------------------------
    // value
    // ------------------------------------------------------------------------
    // Description:
    //   Alias for getRight() - extracts the success value from an Either.
    //   This function provides more semantic meaning when working with Result
    //   types, where the Right value represents the successful computation
    //   result.
    //
    // Template parameters:
    //   L - The Left type of the Either
    //   R - The Right type of the Either
    //
    // Parameters:
    //   either - The Either instance to extract from
    //
    // Returns:
    //   A const reference to the Right (success) value
    //
    // See also: getRight()
    // ------------------------------------------------------------------------
    template <typename L, typename R>
    constexpr const R& value(Either<L, R> const& either) {
        return getRight(either);
    }

    // ------------------------------------------------------------------------
    // getLeft
    // ------------------------------------------------------------------------
    // Description:
    //   Extracts the Left value from an Either.
    //
    // Warning:
    //   This function does not check if the Either actually contains a Left
    //   value. Calling this on an Either containing a Right value results in
    //   undefined behavior. Always use isLeft() to check before calling.
    //
    // Template parameters:
    //   L - The Left type of the Either
    //   R - The Right type of the Either
    //
    // Parameters:
    //   either - The Either instance to extract from
    //
    // Returns:
    //   A const reference to the Left value
    //
    // Example:
    //     Either<std::string, int> e =
    //         Either<std::string, int>(std::in_place_index<0>, "oops");
    //     if (isLeft(e)) {
    //         std::string err = getLeft(e);  // err == "oops"
    //     }
    // ------------------------------------------------------------------------
    template <typename L, typename R>
    constexpr const L& getLeft(Either<L, R> const& either) {
        return std::get<0>(either);
    }

    // ------------------------------------------------------------------------
    // error
    // ------------------------------------------------------------------------
    // Description:
    //   Alias for getLeft() - extracts the error value from an Either.
    //   This function provides more semantic meaning when working with Result
    //   types, where the Left value represents the error.
    //
    // Template parameters:
    //   L - The Left type of the Either
    //   R - The Right type of the Either
    //
    // Parameters:
    //   either - The Either instance to extract from
    //
    // Returns:
    //   A const reference to the Left (error) value
    //
    // See also: getLeft()
    // ------------------------------------------------------------------------
    template <typename L, typename R>
    constexpr const L& error(Either<L, R> const& either) {
        return getLeft(either);
    }

    // ------------------------------------------------------------------------
    // mbind (lvalue reference version)
    // ------------------------------------------------------------------------
    // Description:
    //   Monadic bind operation for Either.
    //
    //   The bind operation (also known as flatMap or >>=) is the core of
    //   monadic composition. It applies a function to the Right value of an
    //   Either, where the function itself returns an Either. This enables
    //   chaining of computations that may fail.
    //
    //   If the Either contains a Right value, the function f is applied to it.
    //   If the Either contains a Left value, it is propagated unchanged.
    //
    // Template parameters:
    //   L - The Left type of the input Either
    //   R - The Right type of the input Either
    //   F - A callable type that takes R and returns Either<L, NewR>
    //
    // Parameters:
    //   either - The Either instance to bind over
    //   f      - The function to apply to the Right value
    //
    // Returns:
    //   The result of applying f to the Right value, or the propagated Left
    //
    // Note:
    //   The function f must return an Either with the same Left type as the
    //   input.
    //
    // Example:
    //     Result<int> safeDivide(int a, int b) {
    //         if (b == 0) {
    //             return Result<int>(std::in_place_index<0>,
    //                                std::runtime_error("div by zero"));
    //         }
    //         return validate(a / b);
    //     }
    //
    //     auto result = mbind(validate(100),
    //                         [](int x) { return safeDivide(x, 5); });
    //     // result contains 20
    // ------------------------------------------------------------------------
    template <typename L, typename R, typename F>
    constexpr auto mbind(Either<L, R> const& either, F&& f)
    -> std::invoke_result_t<F, R> {
        if (isRight(either)) {
            return std::invoke(std::forward<F>(f), std::get<1>(either));
        } else {
            using ResultType = std::invoke_result_t<F, R>;
            return ResultType(std::in_place_index<0>, std::get<0>(either));
        }
    }

    // ------------------------------------------------------------------------
    // mbind (rvalue reference version)
    // ------------------------------------------------------------------------
    // Description:
    //   Monadic bind operation for Either (rvalue reference version).
    //   This overload enables move semantics for temporary Either values,
    //   avoiding unnecessary copies when the Either is an rvalue.
    //
    // Template parameters:
    //   L - The Left type of the input Either
    //   R - The Right type of the input Either
    //   F - A callable type that takes R and returns Either<L, NewR>
    //
    // Parameters:
    //   either - The Either rvalue to bind over (will be moved from)
    //   f      - The function to apply to the Right value
    //
    // Returns:
    //   The result of applying f to the Right value, or the propagated Left
    //
    // Warning:
    //   After this function returns, the input either is in a moved-from
    //   state and should not be used.
    //
    // See also: mbind(Either<L, R> const&, F&&)
    // ------------------------------------------------------------------------
    template <typename L, typename R, typename F>
    constexpr auto mbind(Either<L, R>&& either, F&& f)
    -> std::invoke_result_t<F, R> {
        if (isRight(either)) {
            return std::invoke(std::forward<F>(f), std::get<1>(either));
        } else {
            using ResultType = std::invoke_result_t<F, R>;

            // After moving from 'either', do not use 'either' again!
            return ResultType(
                std::in_place_index<0>,
                std::get<0>(std::move(either))
            );
        }
    }

    // ------------------------------------------------------------------------
    // fmap
    // ------------------------------------------------------------------------
    // Description:
    //   Functor map operation for Either.
    //
    //   The fmap operation applies a function to the Right value of an Either,
    //   wrapping the result in a new Either. Unlike mbind, the function f
    //   returns a plain value (not an Either), and fmap wraps it automatically.
    //
    //   If the Either contains a Right value, f is applied and the result is
    //   wrapped in Right. If the Either contains a Left value, it is
    //   propagated unchanged.
    //
    // Template parameters:
    //   L - The Left type of the input Either
    //   R - The Right type of the input Either
    //   F - A callable type that takes R and returns a new value
    //
    // Parameters:
    //   either - The Either instance to map over
    //   f      - The function to apply to the Right value
    //
    // Returns:
    //   Either<L, invoke_result_t<F, R>> containing the transformed value or
    //   the original Left
    //
    // Example:
    //     Either<std::string, int> e =
    //         Either<std::string, int>(std::in_place_index<1>, 21);
    //     auto result = fmap(e, [](int x) { return x * 2; });
    //     // result contains Right(42)
    // ------------------------------------------------------------------------
    template <typename L, typename R, typename F>
    constexpr auto fmap(Either<L, R> const& either, F&& f)
    -> Either<L, std::invoke_result_t<F, R>> {
        if (isRight(either)) {
            return std::invoke(std::forward<F>(f), std::get<1>(either));
        } else {
            return Either<L, std::invoke_result_t<F, R>>(
                std::in_place_index<0>,
                std::get<0>(either)
            );
        }
    }

    // ------------------------------------------------------------------------
    // operator| (lvalue version)
    // ------------------------------------------------------------------------
    // Description:
    //   Pipe operator for monadic bind.
    //   Provides a convenient infix syntax for chaining monadic operations.
    //   This operator is equivalent to calling mbind(either, f).
    //
    // Template parameters:
    //   L - The Left type of the input Either
    //   R - The Right type of the input Either
    //   F - A callable type that takes R and returns Either<L, NewR>
    //
    // Parameters:
    //   either - The Either instance to bind over
    //   f      - The function to apply to the Right value
    //
    // Returns:
    //   The result of mbind(either, f)
    //
    // Example:
    //     auto result = validate(10)
    //         | [](int x) { return validate(x * 2); }
    //         | [](int x) { return validate(x + 5); };
    //     // result contains Right(25)
    // ------------------------------------------------------------------------
    template <typename L, typename R, typename F>
    constexpr auto operator|(Either<L, R> const& either, F&& f) {
        return mbind(either, std::forward<F>(f));
    }

    // ------------------------------------------------------------------------
    // operator| (rvalue version)
    // ------------------------------------------------------------------------
    // Description:
    //   Pipe operator for monadic bind (rvalue version).
    //   Provides a convenient infix syntax for chaining monadic operations
    //   with move semantics for temporary Either values.
    //
    // Template parameters:
    //   L - The Left type of the input Either
    //   R - The Right type of the input Either
    //   F - A callable type that takes R and returns Either<L, NewR>
    //
    // Parameters:
    //   either - The Either rvalue to bind over
    //   f      - The function to apply to the Right value
    //
    // Returns:
    //   The result of mbind(std::move(either), f)
    //
    // See also: operator|(Either<L, R> const&, F&&)
    // ------------------------------------------------------------------------
    template <typename L, typename R, typename F>
    constexpr auto operator|(Either<L, R>&& either, F&& f) {
        return mbind(std::move(either), std::forward<F>(f));
    }

    // -------------------------------------------------------------------------
    // validate
    // -------------------------------------------------------------------------
    // Description:
    //   Creates a successful Result containing the given value.
    //   This is a convenience function for creating a Result in the success state.
    //   It wraps the given value in a Right (success) variant of Result<T>.
    //
    // Template parameters:
    //   T - The type of the value to wrap
    //
    // Parameters:
    //   val - The value to wrap (copied)
    //
    // Returns:
    //   A Result<T> containing the value in the Right position
    //
    // Example:
    //     auto result = validate(42);
    //     // result is Result<int> containing Right(42)
    //
    //     std::string s = "hello";
    //     auto strResult = validate(s);  // s is copied
    // -------------------------------------------------------------------------
    template<typename T>
    constexpr MonadicTypes::Result<std::decay_t<T>> validate(T&& val) {
        return MonadicTypes::Result<std::decay_t<T>> (
            std::in_place_index<1>,
            std::forward<T> (val)
        );
    }

}  // namespace MonadicTypes

// End of `MonadicTypes.hxx`