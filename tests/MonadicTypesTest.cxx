// ============================================================================
// File: MonadicTypesTest.cxx
//
// Description:
//   Comprehensive unit tests for MonadicTypes library including Either monad,
//   Result type, monadic bind, functor map, and pipe operator.
//   Tests cover both lvalue and rvalue semantics, error propagation, and
//   proper object lifecycle using DummyClass with TraceableLoggingService.
// ============================================================================

#include "MonadicTypes/MonadicTypes.hxx"
#include "DummyClass/DummyClass.hxx"

#include <gtest/gtest.h>
#include <functional>
#include <numeric>
#include <optional>
#include <string>
#include <tuple>
#include <vector>

using namespace MonadicTypes;
using namespace LoggingService;

// ============================================================================
// Test Fixtures
// ============================================================================

class MonadicTypesTest : public testing::Test {
protected:
    void SetUp() override {
        logger_ = TraceableLoggingService{"MONADIC_TEST"};
        DummyClass::SetLogger(&logger_);
    }

    void TearDown() override {
        DummyClass::SetLogger(nullptr);
    }

    // LogRecord GetLogRecord() const {
    //     return std::visit(Record{}, logger_);
    // }

    // void ResetLogRecord() {
    //     std::visit(Reset{}, logger_);
    // }

    Logger logger_;
};

// ============================================================================
// Either Type Creation Tests
// ============================================================================

TEST(EitherCreationTest, CreateRightWithInt) {
    Either<std::string, int> e(std::in_place_index<1>, 42);

    EXPECT_TRUE(isRight(e));
    EXPECT_FALSE(isLeft(e));
    EXPECT_EQ(42, getRight(e));
}

TEST(EitherCreationTest, CreateLeftWithString) {
    Either<std::string, int> e(std::in_place_index<0>, "error message");

    EXPECT_TRUE(isLeft(e));
    EXPECT_FALSE(isRight(e));
    EXPECT_EQ("error message", getLeft(e));
}

TEST(EitherCreationTest, CreateRightWithDouble) {
    Either<int, double> e(std::in_place_index<1>, 3.14159);

    EXPECT_TRUE(isRight(e));
    EXPECT_DOUBLE_EQ(3.14159, getRight(e));
}

TEST(EitherCreationTest, CreateLeftWithInt) {
    Either<int, double> e(std::in_place_index<0>, -1);

    EXPECT_TRUE(isLeft(e));
    EXPECT_EQ(-1, getLeft(e));
}

TEST(EitherCreationTest, CreateWithVector) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    Either<std::string, std::vector<int>> e(std::in_place_index<1>, vec);

    EXPECT_TRUE(isRight(e));
    EXPECT_EQ(vec, getRight(e));
}

// ============================================================================
// Result Type Tests
// ============================================================================

TEST(ResultTypeTest, CreateSuccessResult) {
    Result<int> r(std::in_place_index<1>, 100);

    EXPECT_TRUE(isRight(r));
    EXPECT_EQ(100, value(r));
}

TEST(ResultTypeTest, CreateErrorResult) {
    Result<int> r(std::in_place_index<0>, std::runtime_error("test error"));

    EXPECT_TRUE(isLeft(r));
    EXPECT_STREQ("test error", error(r).what());
}

TEST(ResultTypeTest, ResultWithString) {
    Result<std::string> r(std::in_place_index<1>, "success value");

    EXPECT_TRUE(isRight(r));
    EXPECT_EQ("success value", value(r));
}

// ============================================================================
// Accessor Function Tests
// ============================================================================

TEST(AccessorTest, GetRightReturnsCorrectValue) {
    Either<std::string, int> e(std::in_place_index<1>, 42);
    EXPECT_EQ(42, getRight(e));
}

TEST(AccessorTest, GetLeftReturnsCorrectValue) {
    Either<std::string, int> e(std::in_place_index<0>, "error");
    EXPECT_EQ("error", getLeft(e));
}

TEST(AccessorTest, ValueAliasForGetRight) {
    Either<std::string, int> e(std::in_place_index<1>, 99);
    EXPECT_EQ(getRight(e), value(e));
}

TEST(AccessorTest, ErrorAliasForGetLeft) {
    Either<std::string, int> e(std::in_place_index<0>, "failure");
    EXPECT_EQ(getLeft(e), error(e));
}

TEST(AccessorTest, ConstCorrectness) {
    const Either<std::string, int> e(std::in_place_index<1>, 42);
    const int& val = getRight(e);
    EXPECT_EQ(42, val);
}

// ============================================================================
// validate Function Tests
// ============================================================================

TEST(ValidateTest, ValidateLvalueInt) {
    int x = 42;
    auto result = validate(x);

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(42, value(result));
}

TEST(ValidateTest, ValidateRvalueInt) {
    auto result = validate(42);

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(42, value(result));
}

TEST(ValidateTest, ValidateLvalueString) {
    std::string s = "hello";
    auto result = validate(s);

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ("hello", value(result));
    // Original string should be unchanged (copied)
    EXPECT_EQ("hello", s);
}

TEST(ValidateTest, ValidateRvalueString) {
    auto result = validate(std::string("world"));

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ("world", value(result));
}

TEST(ValidateTest, ValidateMoveString) {
    std::string s = "moveable";
    auto result = validate(std::move(s));

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ("moveable", value(result));
    // Original string should be empty after move
    EXPECT_TRUE(s.empty());
}

TEST(ValidateTest, ValidateVector) {
    std::vector<int> vec = {1, 2, 3};
    auto result = validate(vec);

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(std::vector<int>({1, 2, 3}), value(result));
}

TEST(ValidateTest, ValidateMoveVector) {
    std::vector<int> vec = {10, 20, 30};
    auto result = validate(std::move(vec));

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(std::vector<int>({10, 20, 30}), value(result));
    EXPECT_TRUE(vec.empty());
}

// ============================================================================
// mbind Tests - Lvalue Reference Version
// ============================================================================

TEST(MbindLvalueTest, BindSuccessToSuccess) {
    Either<std::string, int> e(std::in_place_index<1>, 10);

    auto result = mbind(e, [](int x) {
        return Either<std::string, int>(std::in_place_index<1>, x * 2);
    });

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(20, getRight(result));
}

TEST(MbindLvalueTest, BindSuccessToFailure) {
    Either<std::string, int> e(std::in_place_index<1>, 10);

    auto result = mbind(e, [](int) {
        return Either<std::string, int>(
            std::in_place_index<0>, "computation failed"
        );
    });

    EXPECT_TRUE(isLeft(result));
    EXPECT_EQ("computation failed", getLeft(result));
}

TEST(MbindLvalueTest, BindFailurePropagates) {
    Either<std::string, int> e(std::in_place_index<0>, "initial error");

    bool functionCalled = false;
    auto result = mbind(e, [&functionCalled](int x) {
        functionCalled = true;
        return Either<std::string, int>(std::in_place_index<1>, x * 2);
    });

    EXPECT_TRUE(isLeft(result));
    EXPECT_EQ("initial error", getLeft(result));
    EXPECT_FALSE(functionCalled);
}

TEST(MbindLvalueTest, BindWithTypeTransformation) {
    Either<std::string, int> e(std::in_place_index<1>, 42);

    auto result = mbind(e, [](int x) {
        return Either<std::string, std::string>(
            std::in_place_index<1>, "Number: " + std::to_string(x)
        );
    });

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ("Number: 42", getRight(result));
}

TEST(MbindLvalueTest, OriginalEitherUnchanged) {
    Either<std::string, int> e(std::in_place_index<1>, 100);

    auto result = mbind(e, [](int x) {
        return Either<std::string, int>(std::in_place_index<1>, x + 1);
    });

    // Original should be unchanged
    EXPECT_EQ(100, getRight(e));
    EXPECT_EQ(101, getRight(result));
}

// ============================================================================
// mbind Tests - Rvalue Reference Version
// ============================================================================

TEST(MbindRvalueTest, BindRvalueSuccess) {
    auto result = mbind(
        Either<std::string, int>(std::in_place_index<1>, 5),
        [](int x) {
            return Either<std::string, int>(std::in_place_index<1>, x * 3);
        }
    );

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(15, getRight(result));
}

TEST(MbindRvalueTest, BindRvalueFailurePropagates) {
    auto result = mbind(
        Either<std::string, int>(std::in_place_index<0>, "rvalue error"),
        [](int x) {
            return Either<std::string, int>(std::in_place_index<1>, x);
        }
    );

    EXPECT_TRUE(isLeft(result));
    EXPECT_EQ("rvalue error", getLeft(result));
}

TEST(MbindRvalueTest, BindMovedEither) {
    Either<std::string, std::vector<int>> e(
        std::in_place_index<1>, std::vector<int>{1, 2, 3}
    );

    auto result = mbind(std::move(e), [](std::vector<int> vec) {
        vec.push_back(4);
        return Either<std::string, std::vector<int>>(
            std::in_place_index<1>, std::move(vec)
        );
    });

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(std::vector<int>({1, 2, 3, 4}), getRight(result));
}

// ============================================================================
// fmap Tests
// ============================================================================

TEST(FmapTest, MapOverRight) {
    Either<std::string, int> e(std::in_place_index<1>, 21);

    auto result = fmap(e, [](int x) { return x * 2; });

    EXPECT_EQ(42, value(result));
}

TEST(FmapTest, MapOverLeftPropagatesError) {
    Either<std::string, int> e(std::in_place_index<0>, "error");

    auto result = fmap(e, [](int x) { return x * 2; });

    EXPECT_TRUE(isLeft(result));
    EXPECT_EQ("error", getLeft(result));
}

TEST(FmapTest, MapWithTypeTransformation) {
    Either<int, double> e(std::in_place_index<1>, 3.14);

    auto result = fmap(e, [](double x) {
        return "Value: " + std::to_string(x);
    });

    EXPECT_TRUE(isRight(result));
    EXPECT_TRUE(getRight(result).find("3.14") != std::string::npos);
}

TEST(FmapTest, MapDoesNotCallFunctionOnLeft) {
    Either<std::string, int> e(std::in_place_index<0>, "failure");

    bool called = false;
    auto result = fmap(e, [&called](int x) {
        called = true;
        return x;
    });

    EXPECT_FALSE(called);
    EXPECT_TRUE(isLeft(result));
}

// ============================================================================
// Pipe Operator Tests - Lvalue Version
// ============================================================================

TEST(PipeOperatorLvalueTest, SinglePipe) {
    Either<std::string, int> e(std::in_place_index<1>, 10);

    auto result = e | [](int x) {
        return Either<std::string, int>(std::in_place_index<1>, x + 5);
    };

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(15, getRight(result));
}

TEST(PipeOperatorLvalueTest, ChainedPipes) {
    Either<std::string, int> e(std::in_place_index<1>, 2);

    auto result = e
        | [](int x) {
            return Either<std::string, int>(std::in_place_index<1>, x * 2);
        }
        | [](int x) {
            return Either<std::string, int>(std::in_place_index<1>, x + 1);
        }
        | [](int x) {
            return Either<std::string, int>(std::in_place_index<1>, x * 3);
        };

    // (2 * 2) = 4, (4 + 1) = 5, (5 * 3) = 15
    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(15, getRight(result));
}

TEST(PipeOperatorLvalueTest, ErrorPropagatesInChain) {
    Either<std::string, int> e(std::in_place_index<1>, 10);

    int callCount = 0;
    auto result = e
        | [&callCount](int x) {
            callCount++;
            return Either<std::string, int>(std::in_place_index<1>, x * 2);
        }
        | [&callCount](int) {
            callCount++;
            return Either<std::string, int>(
                std::in_place_index<0>, "error in chain"
            );
        }
        | [&callCount](int x) {
            callCount++;
            return Either<std::string, int>(std::in_place_index<1>, x + 1);
        };

    EXPECT_TRUE(isLeft(result));
    EXPECT_EQ("error in chain", getLeft(result));
    EXPECT_EQ(2, callCount);  // Third function should not be called
}

// ============================================================================
// Pipe Operator Tests - Rvalue Version
// ============================================================================

TEST(PipeOperatorRvalueTest, SinglePipeRvalue) {
    auto result = Either<std::string, int>(std::in_place_index<1>, 7)
        | [](int x) {
            return Either<std::string, int>(std::in_place_index<1>, x * 2);
        };

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(14, getRight(result));
}

TEST(PipeOperatorRvalueTest, ChainedPipesRvalue) {
    auto result = Either<std::string, int>(std::in_place_index<1>, 1)
        | [](int x) {
            return Either<std::string, int>(std::in_place_index<1>, x + 1);
        }
        | [](int x) {
            return Either<std::string, int>(std::in_place_index<1>, x * 2);
        }
        | [](int x) {
            return Either<std::string, int>(std::in_place_index<1>, x + 3);
        };

    // (1 + 1) = 2, (2 * 2) = 4, (4 + 3) = 7
    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(7, getRight(result));
}

TEST(PipeOperatorRvalueTest, ErrorAtStartPropagates) {
    int callCount = 0;
    auto result = Either<std::string, int>(std::in_place_index<0>, "start err")
        | [&callCount](int x) {
            callCount++;
            return Either<std::string, int>(std::in_place_index<1>, x);
        }
        | [&callCount](int x) {
            callCount++;
            return Either<std::string, int>(std::in_place_index<1>, x);
        };

    EXPECT_TRUE(isLeft(result));
    EXPECT_EQ("start err", getLeft(result));
    EXPECT_EQ(0, callCount);
}

// ============================================================================
// Chaining with validate Tests
// ============================================================================

TEST(ValidateChainTest, ChainValidateCalls) {
    auto result = validate(10)
        | [](int x) { return validate(x * 2); }
        | [](int x) { return validate(x + 5); };

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(25, value(result));
}

TEST(ValidateChainTest, ChainWithConditionalError) {
    auto safeDivide = [](int divisor) {
        return [divisor](int dividend) -> Result<int> {
            if (divisor == 0) {
                return Result<int>(
                    std::in_place_index<0>,
                    std::runtime_error("division by zero")
                );
            }
            return validate(dividend / divisor);
        };
    };

    auto result = validate(100)
        | safeDivide(5)
        | safeDivide(2);

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(10, value(result));
}

TEST(ValidateChainTest, ChainWithDivisionByZero) {
    auto safeDivide = [](int divisor) {
        return [divisor](int dividend) -> Result<int> {
            if (divisor == 0) {
                return Result<int>(
                    std::in_place_index<0>,
                    std::runtime_error("division by zero")
                );
            }
            return validate(dividend / divisor);
        };
    };

    auto result = validate(100)
        | safeDivide(5)
        | safeDivide(0)
        | safeDivide(2);

    EXPECT_TRUE(isLeft(result));
    EXPECT_STREQ("division by zero", error(result).what());
}

// ============================================================================
// DummyClass Tests with Tracing
// ============================================================================

TEST_F(MonadicTypesTest, ValidateDummyClassLvalue) {
    LogRecord expected = {
        String{"MONADIC_TEST: DEBUG A->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG A->Copy constructor call"},
    };

    DummyClass::DummyClass obj{"A"};
    auto result = validate(obj);

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(expected, GetRecord(logger_).value());
    ResetRecord(logger_);
}

TEST_F(MonadicTypesTest, ValidateDummyClassRvalue) {
    LogRecord expected = {
        String{"MONADIC_TEST: DEBUG B->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG B->Move constructor call"},
        String{"MONADIC_TEST: DEBUG None->Destructor call"},
    };

    auto result = validate(DummyClass::DummyClass{"B"});

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(expected, GetRecord(logger_).value());
    ResetRecord(logger_);
}

TEST_F(MonadicTypesTest, ValidateDummyClassWithMove) {
    LogRecord expected = {
        String{"MONADIC_TEST: DEBUG C->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG C->Move constructor call"},
    };

    DummyClass::DummyClass obj{"C"};
    auto result = validate(std::move(obj));

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(expected, GetRecord(logger_).value());
    ResetRecord(logger_);
}

TEST_F(MonadicTypesTest, MbindDummyClassLvalue) {
    LogRecord expected = {
        String{"MONADIC_TEST: DEBUG D->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG D->Copy constructor call"},
        String{"MONADIC_TEST: DEBUG E->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG E->Move constructor call"},
        String{"MONADIC_TEST: DEBUG None->Destructor call"},
    };

    DummyClass::DummyClass obj{"D"};
    Result<DummyClass::DummyClass> e = validate(obj);

    auto result = mbind(e, [](const DummyClass::DummyClass&) {
        return validate(DummyClass::DummyClass{"E"});
    });

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(expected, GetRecord(logger_).value());
    ResetRecord(logger_);
}

TEST_F(MonadicTypesTest, MbindDummyClassRvalue) {
    LogRecord expected = {
        String{"MONADIC_TEST: DEBUG F->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG F->Move constructor call"},
        String{"MONADIC_TEST: DEBUG G->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG G->Move constructor call"},
        String{"MONADIC_TEST: DEBUG None->Destructor call"},
        String{"MONADIC_TEST: DEBUG F->Destructor call"},
        String{"MONADIC_TEST: DEBUG None->Destructor call"},
    };

    auto result = mbind(
        validate(DummyClass::DummyClass{"F"}),
        [](const DummyClass::DummyClass&) {
            return validate(DummyClass::DummyClass{"G"});
        }
    );

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(expected, GetRecord(logger_).value());
    ResetRecord(logger_);
}

TEST_F(MonadicTypesTest, PipeOperatorDummyClassChain) {
    LogRecord expected = {
        String{"MONADIC_TEST: DEBUG H->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG H->Move constructor call"},
        String{"MONADIC_TEST: DEBUG I->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG I->Move constructor call"},
        String{"MONADIC_TEST: DEBUG None->Destructor call"},
        String{"MONADIC_TEST: DEBUG J->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG J->Move constructor call"},
        String{"MONADIC_TEST: DEBUG None->Destructor call"},
        String{"MONADIC_TEST: DEBUG I->Destructor call"},
        String{"MONADIC_TEST: DEBUG H->Destructor call"},
        String{"MONADIC_TEST: DEBUG None->Destructor call"},
    };

    auto result = validate(DummyClass::DummyClass{"H"})
        | [](const DummyClass::DummyClass&) {
            return validate(DummyClass::DummyClass{"I"});
        }
        | [](const DummyClass::DummyClass&) {
            return validate(DummyClass::DummyClass{"J"});
        };

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(expected, GetRecord(logger_).value());
    ResetRecord(logger_);
}

TEST_F(MonadicTypesTest, ErrorPropagationSkipsDummyClassConstruction) {
    LogRecord expected = {
        String{"MONADIC_TEST: DEBUG K->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG K->Move constructor call"},
        String{"MONADIC_TEST: DEBUG K->Destructor call"},
        String{"MONADIC_TEST: DEBUG None->Destructor call"},
    };

    auto result = validate(DummyClass::DummyClass{"K"})
        | [](const DummyClass::DummyClass&)
              -> Result<DummyClass::DummyClass> {
            return Result<DummyClass::DummyClass>(
                std::in_place_index<0>,
                std::runtime_error("error after K")
            );
        }
        | [](const DummyClass::DummyClass&) {
            // This should NOT be called
            return validate(DummyClass::DummyClass{"L"});
        }
        | [](const DummyClass::DummyClass&) {
            // This should NOT be called
            return validate(DummyClass::DummyClass{"M"});
        };

    EXPECT_TRUE(isLeft(result));
    EXPECT_STREQ("error after K", error(result).what());
    EXPECT_EQ(expected, GetRecord(logger_).value());
    ResetRecord(logger_);
}

TEST_F(MonadicTypesTest, DummyClassDestructorCalledOnError) {
    ResetRecord(logger_);

    {
        auto result = validate(DummyClass::DummyClass{"N"})
            | [](const DummyClass::DummyClass&)
                  -> Result<DummyClass::DummyClass> {
                return Result<DummyClass::DummyClass>(
                    std::in_place_index<0>,
                    std::runtime_error("intentional error")
                );
            };

        EXPECT_TRUE(isLeft(result));
    }

    LogRecord expected = {
        String{"MONADIC_TEST: DEBUG N->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG N->Move constructor call"},
        String{"MONADIC_TEST: DEBUG N->Destructor call"},
        String{"MONADIC_TEST: DEBUG None->Destructor call"},
    };

    EXPECT_EQ(expected, GetRecord(logger_).value());
    ResetRecord(logger_);
}

// ============================================================================
// Edge Cases and Complex Scenarios
// ============================================================================

TEST(EdgeCaseTest, EmptyStringAsError) {
    Either<std::string, int> e(std::in_place_index<0>, "");

    EXPECT_TRUE(isLeft(e));
    EXPECT_EQ("", getLeft(e));
}

TEST(EdgeCaseTest, ZeroAsRightValue) {
    Either<std::string, int> e(std::in_place_index<1>, 0);

    EXPECT_TRUE(isRight(e));
    EXPECT_EQ(0, getRight(e));
}

TEST(EdgeCaseTest, NegativeNumbers) {
    Either<int, int> e(std::in_place_index<1>, -42);

    auto result = mbind(e, [](int x) {
        return Either<int, int>(std::in_place_index<1>, x * -1);
    });

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(42, getRight(result));
}

TEST(EdgeCaseTest, LongChain) {
    auto result = validate(1);

    for (int i = 0; i < 100; ++i) {
        result = result | [](int x) { return validate(x + 1); };
    }

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(101, value(result));
}

TEST(EdgeCaseTest, NestedEither) {
    using InnerEither = Either<std::string, int>;
    using OuterEither = Either<std::string, InnerEither>;

    OuterEither outer(
        std::in_place_index<1>,
        InnerEither(std::in_place_index<1>, 42)
    );

    EXPECT_TRUE(isRight(outer));
    EXPECT_TRUE(isRight(getRight(outer)));
    EXPECT_EQ(42, getRight(getRight(outer)));
}

TEST(EdgeCaseTest, EitherWithPointer) {
    int value = 42;
    Either<std::string, int*> e(std::in_place_index<1>, &value);

    EXPECT_TRUE(isRight(e));
    EXPECT_EQ(42, *getRight(e));
}

TEST(EdgeCaseTest, MbindReturningDifferentErrorType) {
    // While the Left type must match, the Right type can change
    Either<std::string, int> e(std::in_place_index<1>, 10);

    auto result = mbind(e, [](int x) {
        return Either<std::string, double>(
            std::in_place_index<1>, static_cast<double>(x) / 3.0
        );
    });

    EXPECT_TRUE(isRight(result));
    EXPECT_DOUBLE_EQ(10.0 / 3.0, getRight(result));
}

// ============================================================================
// Constexpr Tests (where applicable)
// ============================================================================

TEST(ConstexprTest, IsRightConstexpr) {
    constexpr Either<int, int> e(std::in_place_index<1>, 42);
    constexpr bool result = isRight(e);
    EXPECT_TRUE(result);
}

TEST(ConstexprTest, IsLeftConstexpr) {
    constexpr Either<int, int> e(std::in_place_index<0>, -1);
    constexpr bool result = isLeft(e);
    EXPECT_TRUE(result);
}

// ============================================================================
// Multiple Either Types in Same Expression
// ============================================================================

TEST(MultipleTypesTest, TransformIntToStringToDouble) {
    Either<std::string, int> start(std::in_place_index<1>, 42);

    auto stringResult = mbind(start, [](int x) {
        return Either<std::string, std::string>(
            std::in_place_index<1>,
            std::to_string(x)
        );
    });

    auto doubleResult = mbind(stringResult, [](const std::string& s) {
        return Either<std::string, double>(
            std::in_place_index<1>,
            std::stod(s) + 0.5
        );
    });

    EXPECT_TRUE(isRight(doubleResult));
    EXPECT_DOUBLE_EQ(42.5, getRight(doubleResult));
}

// ============================================================================
// fmap Tests with DummyClass
// ============================================================================

TEST_F(MonadicTypesTest, FmapDummyClassLvalue) {
    LogRecord expected = {
        String{"MONADIC_TEST: DEBUG A->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG A->Copy constructor call"},
        String{"MONADIC_TEST: DEBUG A->Copy constructor call"},
        String{"MONADIC_TEST: DEBUG A->Move constructor call"},
        String{"MONADIC_TEST: DEBUG None->Destructor call"},
    };

    DummyClass::DummyClass obj{"A"};
    Result<DummyClass::DummyClass> e = validate(obj);

    // fmap transforms but doesn't chain monads
    auto result = fmap(e, [](const DummyClass::DummyClass& d) {
        // return d.getIdentifier();
        return d;
    });

    // EXPECT_EQ("A", result);
    EXPECT_EQ(value(e), value(result));
    EXPECT_EQ(expected, GetRecord(logger_).value());
    ResetRecord(logger_);
}

TEST_F(MonadicTypesTest, FmapDummyClassRvalue) {
    LogRecord expected = {
        String{"MONADIC_TEST: DEBUG B->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG B->Move constructor call"},
        String{"MONADIC_TEST: DEBUG None->Destructor call"},
        String{"MONADIC_TEST: DEBUG B->Copy constructor call"},
        String{"MONADIC_TEST: DEBUG B->Move constructor call"},
        String{"MONADIC_TEST: DEBUG None->Destructor call"},
    };

    auto e = validate(DummyClass::DummyClass{"B"});

    auto result = fmap(e, [](const DummyClass::DummyClass& d) {
        // return d.getIdentifier();
        return d;
    });

    // EXPECT_EQ("B", result);
    EXPECT_EQ(value(e), value(result));
    EXPECT_EQ(expected, GetRecord(logger_).value());
    ResetRecord(logger_);
}

TEST_F(MonadicTypesTest, FmapOnLeftDoesNotCallFunction) {
    LogRecord expected = {};  // No DummyClass should be created

    Result<DummyClass::DummyClass> e(
        std::in_place_index<0>,
        std::runtime_error("error before fmap")
    );

    bool called = false;
    auto result = fmap(e, [&called](const DummyClass::DummyClass&) {
        called = true;
        return std::string("should not see this");
    });

    EXPECT_FALSE(called);
    EXPECT_TRUE(isLeft(result));
    EXPECT_EQ(expected, GetRecord(logger_).value());
    ResetRecord(logger_);
}

// ============================================================================
// Callable Types Tests
// ============================================================================

// Functor class for testing
struct MultiplyByTwo {
    Result<int> operator()(int x) const {
        return validate(x * 2);
    }
};

struct AddOffset {
    int offset;
    explicit AddOffset(int o) : offset(o) {}

    Result<int> operator()(int x) const {
        return validate(x + offset);
    }
};

TEST(CallableTypesTest, FunctorWithMbind) {
    auto e = validate(21);
    MultiplyByTwo functor;

    auto result = mbind(e, functor);

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(42, value(result));
}

TEST(CallableTypesTest, FunctorWithPipeOperator) {
    auto result = validate(10) | MultiplyByTwo{};

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(20, value(result));
}

TEST(CallableTypesTest, StatefulFunctor) {
    AddOffset add5{5};
    AddOffset add10{10};

    auto result = validate(100)
        | add5
        | add10;

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(115, value(result));
}

TEST(CallableTypesTest, StdFunctionWithMbind) {
    std::function<Result<int>(int)> doubler = [](int x) {
        return validate(x * 2);
    };

    auto e = validate(25);
    auto result = mbind(e, doubler);

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(50, value(result));
}

TEST(CallableTypesTest, StdFunctionWithPipeOperator) {
    std::function<Result<std::string>(int)> toString = [](int x) {
        return validate(std::string("Value: ") + std::to_string(x));
    };

    auto result = validate(42) | toString;

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ("Value: 42", value(result));
}

// Function pointer type
Result<int> squareFunction(int x) {
    return validate(x * x);
}

TEST(CallableTypesTest, FunctionPointerWithMbind) {
    auto e = validate(7);
    auto result = mbind(e, squareFunction);

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(49, value(result));
}

TEST(CallableTypesTest, FunctionPointerWithPipeOperator) {
    auto result = validate(5) | squareFunction;

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(25, value(result));
}

// ============================================================================
// Complex Pipeline Composition Tests
// ============================================================================

TEST(ComplexPipelineTest, MixedOperationsChain) {
    auto parseAndDouble = [](const std::string& s) -> Result<int> {
        try {
            return validate(std::stoi(s) * 2);
        } catch (...) {
            return Result<int>(
                std::in_place_index<0>,
                std::runtime_error("parse failed")
            );
        }
    };

    auto addTen = [](int x) { return validate(x + 10); };

    auto toString = [](int x) {
        return validate(std::string("Result: ") + std::to_string(x));
    };

    auto result = validate(std::string("21"))
        | parseAndDouble
        | addTen
        | toString;

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ("Result: 52", value(result));
}

TEST(ComplexPipelineTest, ConditionalBranching) {
    auto checkPositive = [](int x) -> Result<int> {
        if (x < 0) {
            return Result<int>(
                std::in_place_index<0>,
                std::runtime_error("negative number")
            );
        }
        return validate(x);
    };

    auto checkEven = [](int x) -> Result<int> {
        if (x % 2 != 0) {
            return Result<int>(
                std::in_place_index<0>,
                std::runtime_error("odd number")
            );
        }
        return validate(x);
    };

    auto checkSmall = [](int x) -> Result<int> {
        if (x > 100) {
            return Result<int>(
                std::in_place_index<0>,
                std::runtime_error("number too large")
            );
        }
        return validate(x);
    };

    // All checks pass
    auto result1 = validate(42) | checkPositive | checkEven | checkSmall;
    EXPECT_TRUE(isRight(result1));
    EXPECT_EQ(42, value(result1));

    // Fails at negative check
    auto result2 = validate(-5) | checkPositive | checkEven | checkSmall;
    EXPECT_TRUE(isLeft(result2));
    EXPECT_STREQ("negative number", error(result2).what());

    // Fails at even check
    auto result3 = validate(43) | checkPositive | checkEven | checkSmall;
    EXPECT_TRUE(isLeft(result3));
    EXPECT_STREQ("odd number", error(result3).what());

    // Fails at size check
    auto result4 = validate(200) | checkPositive | checkEven | checkSmall;
    EXPECT_TRUE(isLeft(result4));
    EXPECT_STREQ("number too large", error(result4).what());
}

TEST(ComplexPipelineTest, AccumulatingState) {
    struct State {
        int value;
        std::vector<std::string> log;
    };

    auto step1 = [](State s) -> Result<State> {
        s.value *= 2;
        s.log.push_back("doubled");
        return validate(std::move(s));
    };

    auto step2 = [](State s) -> Result<State> {
        s.value += 10;
        s.log.push_back("added 10");
        return validate(std::move(s));
    };

    auto step3 = [](State s) -> Result<State> {
        s.value /= 2;
        s.log.push_back("halved");
        return validate(std::move(s));
    };

    State initial{5, {}};
    auto result = validate(std::move(initial))
        | step1
        | step2
        | step3;

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(10, value(result).value);  // (5*2 + 10) / 2 = 10

    std::vector<std::string> expectedLog = {"doubled", "added 10", "halved"};
    EXPECT_EQ(expectedLog, value(result).log);
}

// ============================================================================
// Copy vs Move Verification Tests
// ============================================================================

TEST_F(MonadicTypesTest, CopySemanticInMbindLvalue) {
    LogRecord expected = {
        String{"MONADIC_TEST: DEBUG X->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG X->Copy constructor call"},
        // When mbind is called on lvalue, the value inside is copied
        String{"MONADIC_TEST: DEBUG X->Copy constructor call"},
        String{"MONADIC_TEST: DEBUG Y->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG Y->Move constructor call"},
        String{"MONADIC_TEST: DEBUG None->Destructor call"},
        String{"MONADIC_TEST: DEBUG X->Destructor call"},
    };

    DummyClass::DummyClass obj{"X"};
    Result<DummyClass::DummyClass> e = validate(obj);

    auto result = mbind(e, [](DummyClass::DummyClass d) {
        (void) d;  // Prevent compiler complaining about unused parameter
        // Taking by value causes copy
        return validate(DummyClass::DummyClass{"Y"});
    });

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(expected, GetRecord(logger_).value());
    ResetRecord(logger_);
}

TEST_F(MonadicTypesTest, MoveSemanticInMbindRvalue) {
    LogRecord expected = {
        String{"MONADIC_TEST: DEBUG Z->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG Z->Move constructor call"},
        String{"MONADIC_TEST: DEBUG Z->Copy constructor call"},
        String{"MONADIC_TEST: DEBUG W->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG W->Move constructor call"},
        String{"MONADIC_TEST: DEBUG None->Destructor call"},
        String{"MONADIC_TEST: DEBUG Z->Destructor call"},
        String{"MONADIC_TEST: DEBUG Z->Destructor call"},
        String{"MONADIC_TEST: DEBUG None->Destructor call"},
    };

    auto result = mbind(
        validate(DummyClass::DummyClass{"Z"}),
        [](DummyClass::DummyClass d) {
            (void) d;  // Prevent compiler complaining about unused parameter
            return validate(DummyClass::DummyClass{"W"});
        }
    );

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(expected, GetRecord(logger_).value());
    ResetRecord(logger_);
}

TEST_F(MonadicTypesTest, ConstRefDoesNotCopyInLambda) {
    LogRecord expected = {
        String{"MONADIC_TEST: DEBUG P->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG P->Copy constructor call"},
        // Lambda takes const ref, so no additional copy
        String{"MONADIC_TEST: DEBUG Q->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG Q->Move constructor call"},
        String{"MONADIC_TEST: DEBUG None->Destructor call"},
    };

    DummyClass::DummyClass obj{"P"};
    Result<DummyClass::DummyClass> e = validate(obj);

    auto result = mbind(e, [](const DummyClass::DummyClass&) {
        return validate(DummyClass::DummyClass{"Q"});
    });

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(expected, GetRecord(logger_).value());
    ResetRecord(logger_);
}

TEST_F(MonadicTypesTest, ChainedPipePreservesMoveSemantic) {
    LogRecord expected = {
        String{"MONADIC_TEST: DEBUG A1->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG A1->Move constructor call"},
        String{"MONADIC_TEST: DEBUG A2->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG A2->Move constructor call"},
        String{"MONADIC_TEST: DEBUG None->Destructor call"},
        String{"MONADIC_TEST: DEBUG A3->Parametric constructor call"},
        String{"MONADIC_TEST: DEBUG A3->Move constructor call"},
        String{"MONADIC_TEST: DEBUG None->Destructor call"},
        String{"MONADIC_TEST: DEBUG A2->Destructor call"},
        String{"MONADIC_TEST: DEBUG A1->Destructor call"},
        String{"MONADIC_TEST: DEBUG None->Destructor call"},
    };

    auto result = validate(DummyClass::DummyClass{"A1"})
        | [](const DummyClass::DummyClass&) {
            return validate(DummyClass::DummyClass{"A2"});
        }
        | [](const DummyClass::DummyClass&) {
            return validate(DummyClass::DummyClass{"A3"});
        };

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(expected, GetRecord(logger_).value());
    ResetRecord(logger_);
}

// ============================================================================
// Result<T> Specific Edge Cases
// ============================================================================

TEST(ResultEdgeCaseTest, ResultWithEmptyString) {
    Result<std::string> r = validate(std::string(""));

    EXPECT_TRUE(isRight(r));
    EXPECT_EQ("", value(r));
}

TEST(ResultEdgeCaseTest, ResultWithNullptr) {
    int* ptr = nullptr;
    Result<int*> r = validate(ptr);

    EXPECT_TRUE(isRight(r));
    EXPECT_EQ(nullptr, value(r));
}

TEST(ResultEdgeCaseTest, ResultWithZeroValue) {
    Result<int> r = validate(0);

    EXPECT_TRUE(isRight(r));
    EXPECT_EQ(0, value(r));
}

TEST(ResultEdgeCaseTest, ResultErrorMessagePreserved) {
    std::string longError =
        "This is a very long error message that should be fully preserved "
        "when propagated through the monadic chain without any truncation";

    Result<int> r(std::in_place_index<0>, std::runtime_error(longError));

    EXPECT_TRUE(isLeft(r));
    EXPECT_STREQ(longError.c_str(), error(r).what());
}

TEST(ResultEdgeCaseTest, ResultWithOptional) {
    Result<std::optional<int>> r1 = validate(std::optional<int>(42));
    Result<std::optional<int>> r2 = validate(std::optional<int>{});

    EXPECT_TRUE(isRight(r1));
    EXPECT_TRUE(value(r1).has_value());
    EXPECT_EQ(42, value(r1).value());

    EXPECT_TRUE(isRight(r2));
    EXPECT_FALSE(value(r2).has_value());
}

TEST(ResultEdgeCaseTest, ResultWithPair) {
    auto pair = std::make_pair(1, std::string("one"));
    Result<std::pair<int, std::string>> r = validate(pair);

    EXPECT_TRUE(isRight(r));
    EXPECT_EQ(1, value(r).first);
    EXPECT_EQ("one", value(r).second);
}

TEST(ResultEdgeCaseTest, ResultWithTuple) {
    auto tuple = std::make_tuple(1, 2.5, std::string("three"));
    Result<std::tuple<int, double, std::string>> r = validate(tuple);

    EXPECT_TRUE(isRight(r));
    EXPECT_EQ(1, std::get<0>(value(r)));
    EXPECT_DOUBLE_EQ(2.5, std::get<1>(value(r)));
    EXPECT_EQ("three", std::get<2>(value(r)));
}

TEST(ResultEdgeCaseTest, ChainedErrorsFirstWins) {
    auto fail1 = [](int) -> Result<int> {
        return Result<int>(
            std::in_place_index<0>,
            std::runtime_error("error 1")
        );
    };

    auto fail2 = [](int) -> Result<int> {
        return Result<int>(
            std::in_place_index<0>,
            std::runtime_error("error 2")
        );
    };

    auto result = validate(42) | fail1 | fail2;

    EXPECT_TRUE(isLeft(result));
    EXPECT_STREQ("error 1", error(result).what());
}

// ============================================================================
// Identity and Law Tests
// ============================================================================

TEST(MonadLawsTest, LeftIdentity) {
    // Left identity: validate(x) | f  ==  f(x)
    auto f = [](int x) { return validate(x * 2); };

    int x = 21;
    auto result1 = validate(x) | f;
    auto result2 = f(x);

    EXPECT_EQ(value(result1), value(result2));
}

TEST(MonadLawsTest, RightIdentity) {
    // Right identity: m | validate  ==  m
    auto m = validate(42);

    auto result = m | [](int x) { return validate(x); };

    EXPECT_EQ(value(m), value(result));
}

TEST(MonadLawsTest, Associativity) {
    // Associativity: (m | f) | g  ==  m | (x -> f(x) | g)
    auto f = [](int x) { return validate(x * 2); };
    auto g = [](int x) { return validate(x + 10); };

    auto m = validate(5);

    auto result1 = (m | f) | g;
    auto result2 = m | [&f, &g](int x) { return f(x) | g; };

    EXPECT_EQ(value(result1), value(result2));
}

// ============================================================================
// Stress Tests
// ============================================================================

TEST(StressTest, VeryLongChain) {
    auto result = validate(0);

    for (int i = 0; i < 1000; ++i) {
        result = result | [](int x) { return validate(x + 1); };
    }

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(1000, value(result));
}

TEST(StressTest, LargeDataInEither) {
    std::vector<int> largeVec(10000);
    std::iota(largeVec.begin(), largeVec.end(), 0);

    auto result = validate(std::move(largeVec))
        | [](std::vector<int> v) {
            v.push_back(10000);
            return validate(std::move(v));
        };

    EXPECT_TRUE(isRight(result));
    EXPECT_EQ(10001, value(result).size());
    EXPECT_EQ(10000, value(result).back());
}

TEST_F(MonadicTypesTest, ManyDummyClassOperations) {
    ResetRecord(logger_);

    auto result = validate(DummyClass::DummyClass{"Start"});

    for (int i = 0; i < 10; ++i) {
        result = result | [i](const DummyClass::DummyClass&) {
            return validate(DummyClass::DummyClass{
                "Step" + std::to_string(i)
            });
        };
    }

    EXPECT_TRUE(isRight(result));

    // Verify the final DummyClass has the expected identifier
    // EXPECT_EQ("Step9", value(result).getIdentifier());
    EXPECT_EQ(DummyClass::DummyClass{"Step9"}, value(result));
}


// End of `MonadicTypesTest.cxx'