cmake_minimum_required(VERSION 3.19.0)
project(stella-interpreter VERSION 0.1.0)

set (Stella_Syntax
  src/Stella/Absyn.H
  src/Stella/Absyn.C
  src/Stella/Parser.H
  src/Stella/Parser.C
  src/Stella/ParserError.H
  src/Stella/Printer.H
  src/Stella/Printer.C
  src/Stella/Buffer.H
  src/Stella/Buffer.C
  src/Stella/Bison.H
  src/Stella/Lexer.C
)

set (SRCS
  src/Interpret.cpp
  src/Eval.h
  src/Eval.cpp
  src/TypeCheck.h
  src/TypeCheck.cpp
  src/VisitTypeCheck.h
  src/VisitTypeCheck.cpp
)

add_executable(stella-interpreter ${Stella_Syntax} ${SRCS})
set_property(TARGET stella-interpreter PROPERTY CXX_STANDARD 17)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include(CTest)

add_test(NAME applying-non-function-1 COMMAND stella-interpreter typecheck ../tests/ill-typed/applying-non-function-1.stella)
add_test(NAME applying-non-function-2 COMMAND stella-interpreter typecheck ../tests/ill-typed/applying-non-function-2.stella)
add_test(NAME applying-non-function-3 COMMAND stella-interpreter typecheck ../tests/ill-typed/applying-non-function-3.stella)
add_test(NAME argument-type-mismatch-1 COMMAND stella-interpreter typecheck ../tests/ill-typed/argument-type-mismatch-1.stella)
add_test(NAME argument-type-mismatch-2 COMMAND stella-interpreter typecheck ../tests/ill-typed/argument-type-mismatch-2.stella)
add_test(NAME argument-type-mismatch-3 COMMAND stella-interpreter typecheck ../tests/ill-typed/argument-type-mismatch-3.stella)
add_test(NAME bad-if-1 COMMAND stella-interpreter typecheck ../tests/ill-typed/bad-if-1.stella)
add_test(NAME bad-if-2 COMMAND stella-interpreter typecheck ../tests/ill-typed/bad-if-2.stella)
add_test(NAME bad-succ-1 COMMAND stella-interpreter typecheck ../tests/ill-typed/bad-succ-1.stella)
add_test(NAME bad-succ-2 COMMAND stella-interpreter typecheck ../tests/ill-typed/bad-succ-2.stella)
add_test(NAME bad-succ-3 COMMAND stella-interpreter typecheck ../tests/ill-typed/bad-succ-3.stella)
add_test(NAME shadowed-variable-1 COMMAND stella-interpreter typecheck ../tests/ill-typed/shadowed-variable-1.stella)
add_test(NAME undefined-variable-1 COMMAND stella-interpreter typecheck ../tests/ill-typed/undefined-variable-1.stella)
add_test(NAME undefined-variable-2 COMMAND stella-interpreter typecheck ../tests/ill-typed/undefined-variable-2.stella)
add_test(NAME bad-squares-1 COMMAND stella-interpreter typecheck ../tests/ill-typed/bad-squares-1.stella)
add_test(NAME bad-squares-2 COMMAND stella-interpreter typecheck ../tests/ill-typed/bad-squares-2.stella)
set_tests_properties(
  bad-squares-1
  bad-squares-2
  applying-non-function-1
  applying-non-function-2
  applying-non-function-3
  argument-type-mismatch-1
  argument-type-mismatch-2
  argument-type-mismatch-3
  bad-if-1
  bad-if-2
  bad-succ-1
  bad-succ-2
  bad-succ-3
  shadowed-variable-1
  undefined-variable-1
  undefined-variable-2
  PROPERTIES WILL_FAIL TRUE)

add_test(NAME factorial COMMAND stella-interpreter typecheck ../tests/well-typed/factorial.stella)
add_test(NAME increment_twice COMMAND stella-interpreter typecheck ../tests/well-typed/increment_twice.stella)
add_test(NAME higher-order-1 COMMAND stella-interpreter typecheck ../tests/well-typed/higher-order-1.stella)
add_test(NAME logical-operators COMMAND stella-interpreter typecheck ../tests/well-typed/logical-operators.stella)
add_test(NAME squares COMMAND stella-interpreter typecheck ../tests/well-typed/squares.stella)



add_test(NAME 1_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/1.stella)
add_test(NAME 101_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/101.stella)
add_test(NAME 103_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/103.stella)
add_test(NAME 105_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/105.stella)
add_test(NAME 107_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/107.stella)
add_test(NAME 109_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/109.stella)
add_test(NAME 11_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/11.stella)
add_test(NAME 111_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/111.stella)
add_test(NAME 113_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/113.stella)
add_test(NAME 115_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/115.stella)
add_test(NAME 117_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/117.stella)
add_test(NAME 119_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/119.stella)
add_test(NAME 121_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/121.stella)
add_test(NAME 123_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/123.stella)
add_test(NAME 125_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/125.stella)
add_test(NAME 127_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/127.stella)
add_test(NAME 129_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/129.stella)
add_test(NAME 13_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/13.stella)
add_test(NAME 131_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/131.stella)
add_test(NAME 133_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/133.stella)
add_test(NAME 135_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/135.stella)
add_test(NAME 137_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/137.stella)
add_test(NAME 139_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/139.stella)
add_test(NAME 141_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/141.stella)
add_test(NAME 143_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/143.stella)
add_test(NAME 145_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/145.stella)
add_test(NAME 147_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/147.stella)
add_test(NAME 149_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/149.stella)
add_test(NAME 15_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/15.stella)
add_test(NAME 151_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/151.stella)
add_test(NAME 153_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/153.stella)
add_test(NAME 17_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/17.stella)
add_test(NAME 19_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/19.stella)
add_test(NAME 21_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/21.stella)
add_test(NAME 23_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/23.stella)
add_test(NAME 25_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/25.stella)
add_test(NAME 27_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/27.stella)
add_test(NAME 29_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/29.stella)
add_test(NAME 3_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/3.stella)
add_test(NAME 31_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/31.stella)
add_test(NAME 33_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/33.stella)
add_test(NAME 35_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/35.stella)
add_test(NAME 37_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/37.stella)
add_test(NAME 39_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/39.stella)
add_test(NAME 41_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/41.stella)
add_test(NAME 43_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/43.stella)
add_test(NAME 45_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/45.stella)
add_test(NAME 47_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/47.stella)
add_test(NAME 49_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/49.stella)
add_test(NAME 5_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/5.stella)
add_test(NAME 51_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/51.stella)
add_test(NAME 53_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/53.stella)
add_test(NAME 55_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/55.stella)
add_test(NAME 57_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/57.stella)
add_test(NAME 59_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/59.stella)
add_test(NAME 61_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/61.stella)
add_test(NAME 63_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/63.stella)
add_test(NAME 65_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/65.stella)
add_test(NAME 67_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/67.stella)
add_test(NAME 69_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/69.stella)
add_test(NAME 7_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/7.stella)
add_test(NAME 71_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/71.stella)
add_test(NAME 73_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/73.stella)
add_test(NAME 75_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/75.stella)
add_test(NAME 77_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/77.stella)
add_test(NAME 79_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/79.stella)
add_test(NAME 81_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/81.stella)
add_test(NAME 83_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/83.stella)
add_test(NAME 85_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/85.stella)
add_test(NAME 87_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/87.stella)
add_test(NAME 89_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/89.stella)
add_test(NAME 9_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/9.stella)
add_test(NAME 91_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/91.stella)
add_test(NAME 93_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/93.stella)
add_test(NAME 95_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/95.stella)
add_test(NAME 97_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/97.stella)
add_test(NAME 99_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-2/public/99.stella)


set_tests_properties(
    101_stella
    103_stella
    105_stella
    107_stella
    109_stella
    111_stella
    119_stella
    121_stella
    123_stella
    125_stella
    127_stella
    129_stella
    131_stella
    133_stella
    135_stella
    137_stella
    139_stella
    141_stella
    143_stella
    149_stella
    151_stella
    153_stella
    35_stella
    37_stella
    39_stella
    41_stella
    43_stella
    45_stella
    47_stella
    49_stella
    51_stella
    53_stella
    55_stella
    57_stella
    59_stella
    61_stella
    63_stella
    65_stella
    67_stella
    69_stella
    71_stella
    73_stella
    75_stella
    77_stella
    79_stella
    81_stella
    83_stella
    85_stella
    87_stella
    89_stella
    91_stella
    93_stella
    95_stella
    97_stella
    99_stella
  PROPERTIES WILL_FAIL TRUE)

add_test(NAME week-3-1_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/1.stella)
add_test(NAME week-3-11_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/11.stella)
add_test(NAME week-3-13_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/13.stella)
add_test(NAME week-3-15_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/15.stella)
add_test(NAME week-3-17_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/17.stella)
add_test(NAME week-3-19_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/19.stella)
add_test(NAME week-3-21_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/21.stella)
add_test(NAME week-3-23_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/23.stella)
add_test(NAME week-3-25_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/25.stella)
add_test(NAME week-3-27_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/27.stella)
add_test(NAME week-3-29_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/29.stella)
add_test(NAME week-3-3_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/3.stella)
add_test(NAME week-3-31_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/31.stella)
add_test(NAME week-3-33_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/33.stella)
add_test(NAME week-3-35_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/35.stella)
add_test(NAME week-3-37_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/37.stella)
add_test(NAME week-3-39_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/39.stella)
add_test(NAME week-3-41_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/41.stella)
add_test(NAME week-3-43_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/43.stella)
add_test(NAME week-3-45_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/45.stella)
add_test(NAME week-3-47_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/47.stella)
add_test(NAME week-3-49_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/49.stella)
add_test(NAME week-3-5_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/5.stella)
add_test(NAME week-3-51_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/51.stella)
add_test(NAME week-3-53_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/53.stella)
add_test(NAME week-3-55_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/55.stella)
add_test(NAME week-3-57_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/57.stella)
add_test(NAME week-3-59_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/59.stella)
add_test(NAME week-3-61_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/61.stella)
add_test(NAME week-3-63_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/63.stella)
add_test(NAME week-3-65_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/65.stella)
add_test(NAME week-3-67_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/67.stella)
add_test(NAME week-3-69_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/69.stella)
add_test(NAME week-3-7_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/7.stella)
add_test(NAME week-3-71_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/71.stella)
add_test(NAME week-3-73_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/73.stella)
add_test(NAME week-3-9_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-3/public/9.stella)

set_tests_properties(
    week-3-1_stella
    week-3-15_stella
    week-3-17_stella
    week-3-19_stella
    week-3-21_stella
    week-3-23_stella
    week-3-25_stella
    week-3-27_stella
    week-3-29_stella
    week-3-31_stella
    week-3-33_stella
    week-3-35_stella
    week-3-37_stella
    week-3-39_stella
    week-3-43_stella
    week-3-47_stella
    week-3-51_stella
    week-3-53_stella
    week-3-57_stella
    week-3-59_stella
    week-3-63_stella
    week-3-67_stella
    week-3-69_stella
    week-3-7_stella
    week-3-71_stella
    week-3-9_stella
PROPERTIES WILL_FAIL TRUE)


add_test(NAME week-5-1_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/1.stella)
add_test(NAME week-5-101_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/101.stella)
add_test(NAME week-5-103_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/103.stella)
add_test(NAME week-5-105_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/105.stella)
add_test(NAME week-5-107_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/107.stella)
add_test(NAME week-5-109_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/109.stella)
add_test(NAME week-5-11_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/11.stella)
add_test(NAME week-5-111_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/111.stella)
add_test(NAME week-5-113_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/113.stella)
add_test(NAME week-5-115_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/115.stella)
add_test(NAME week-5-117_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/117.stella)
add_test(NAME week-5-119_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/119.stella)
add_test(NAME week-5-121_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/121.stella)
add_test(NAME week-5-123_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/123.stella)
add_test(NAME week-5-125_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/125.stella)
add_test(NAME week-5-127_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/127.stella)
add_test(NAME week-5-129_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/129.stella)
add_test(NAME week-5-13_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/13.stella)
add_test(NAME week-5-131_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/131.stella)
add_test(NAME week-5-133_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/133.stella)
add_test(NAME week-5-15_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/15.stella)
add_test(NAME week-5-17_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/17.stella)
add_test(NAME week-5-19_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/19.stella)
add_test(NAME week-5-21_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/21.stella)
add_test(NAME week-5-23_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/23.stella)
add_test(NAME week-5-25_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/25.stella)
add_test(NAME week-5-27_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/27.stella)
add_test(NAME week-5-29_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/29.stella)
add_test(NAME week-5-3_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/3.stella)
add_test(NAME week-5-31_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/31.stella)
add_test(NAME week-5-33_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/33.stella)
add_test(NAME week-5-35_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/35.stella)
add_test(NAME week-5-37_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/37.stella)
add_test(NAME week-5-39_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/39.stella)
add_test(NAME week-5-41_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/41.stella)
add_test(NAME week-5-43_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/43.stella)
add_test(NAME week-5-45_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/45.stella)
add_test(NAME week-5-47_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/47.stella)
add_test(NAME week-5-49_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/49.stella)
add_test(NAME week-5-5_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/5.stella)
add_test(NAME week-5-51_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/51.stella)
add_test(NAME week-5-53_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/53.stella)
add_test(NAME week-5-55_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/55.stella)
add_test(NAME week-5-57_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/57.stella)
add_test(NAME week-5-59_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/59.stella)
add_test(NAME week-5-61_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/61.stella)
add_test(NAME week-5-63_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/63.stella)
add_test(NAME week-5-65_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/65.stella)
add_test(NAME week-5-67_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/67.stella)
add_test(NAME week-5-69_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/69.stella)
add_test(NAME week-5-7_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/7.stella)
add_test(NAME week-5-71_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/71.stella)
add_test(NAME week-5-73_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/73.stella)
add_test(NAME week-5-75_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/75.stella)
add_test(NAME week-5-77_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/77.stella)
add_test(NAME week-5-79_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/79.stella)
add_test(NAME week-5-81_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/81.stella)
add_test(NAME week-5-83_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/83.stella)
add_test(NAME week-5-85_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/85.stella)
add_test(NAME week-5-87_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/87.stella)
add_test(NAME week-5-89_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/89.stella)
add_test(NAME week-5-9_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/9.stella)
add_test(NAME week-5-91_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/91.stella)
add_test(NAME week-5-93_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/93.stella)
add_test(NAME week-5-95_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/95.stella)
add_test(NAME week-5-97_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/97.stella)
add_test(NAME week-5-99_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-5/public/99.stella)



set_tests_properties(
    week-5-1_stella
    week-5-103_stella
    week-5-105_stella
    week-5-109_stella
    week-5-11_stella
    week-5-119_stella
    week-5-121_stella
    week-5-123_stella
    week-5-125_stella
    week-5-127_stella
    week-5-129_stella
    week-5-13_stella
    week-5-131_stella
    week-5-133_stella
    week-5-15_stella
    week-5-17_stella
    week-5-19_stella
    week-5-21_stella
    week-5-23_stella
    week-5-25_stella
    week-5-27_stella
    week-5-29_stella
    week-5-3_stella
    week-5-31_stella
    week-5-33_stella
    week-5-35_stella
    week-5-41_stella
    week-5-43_stella
    week-5-45_stella
    week-5-5_stella
    week-5-51_stella
    week-5-63_stella
    week-5-65_stella
    week-5-67_stella
    week-5-69_stella
    week-5-7_stella
    week-5-77_stella
    week-5-9_stella
PROPERTIES WILL_FAIL TRUE)


add_test(NAME week-6-1_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/1.stella)
add_test(NAME week-6-101_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/101.stella)
add_test(NAME week-6-103_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/103.stella)
add_test(NAME week-6-105_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/105.stella)
add_test(NAME week-6-107_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/107.stella)
add_test(NAME week-6-109_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/109.stella)
add_test(NAME week-6-11_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/11.stella)
add_test(NAME week-6-111_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/111.stella)
add_test(NAME week-6-113_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/113.stella)
add_test(NAME week-6-115_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/115.stella)
add_test(NAME week-6-117_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/117.stella)
add_test(NAME week-6-119_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/119.stella)
add_test(NAME week-6-121_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/121.stella)
add_test(NAME week-6-123_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/123.stella)
add_test(NAME week-6-125_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/125.stella)
add_test(NAME week-6-127_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/127.stella)
add_test(NAME week-6-129_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/129.stella)
add_test(NAME week-6-13_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/13.stella)
add_test(NAME week-6-135_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/135.stella)
add_test(NAME week-6-139_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/139.stella)
add_test(NAME week-6-141_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/141.stella)
add_test(NAME week-6-143_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/143.stella)
add_test(NAME week-6-145_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/145.stella)
add_test(NAME week-6-15_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/15.stella)
add_test(NAME week-6-161_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/161.stella)
add_test(NAME week-6-163_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/163.stella)
add_test(NAME week-6-165_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/165.stella)
add_test(NAME week-6-167_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/167.stella)
add_test(NAME week-6-169_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/169.stella)
add_test(NAME week-6-17_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/17.stella)
add_test(NAME week-6-171_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/171.stella)
add_test(NAME week-6-173_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/173.stella)
add_test(NAME week-6-21_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/21.stella)
add_test(NAME week-6-23_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/23.stella)
add_test(NAME week-6-25_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/25.stella)
add_test(NAME week-6-27_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/27.stella)
add_test(NAME week-6-3_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/3.stella)
add_test(NAME week-6-31_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/31.stella)
add_test(NAME week-6-33_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/33.stella)
add_test(NAME week-6-35_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/35.stella)
add_test(NAME week-6-37_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/37.stella)
add_test(NAME week-6-39_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/39.stella)
add_test(NAME week-6-41_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/41.stella)
add_test(NAME week-6-43_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/43.stella)
add_test(NAME week-6-45_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/45.stella)
add_test(NAME week-6-47_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/47.stella)
add_test(NAME week-6-49_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/49.stella)
add_test(NAME week-6-5_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/5.stella)
add_test(NAME week-6-53_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/53.stella)
add_test(NAME week-6-55_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/55.stella)
add_test(NAME week-6-57_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/57.stella)
add_test(NAME week-6-59_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/59.stella)
add_test(NAME week-6-61_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/61.stella)
add_test(NAME week-6-65_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/65.stella)
add_test(NAME week-6-67_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/67.stella)
add_test(NAME week-6-7_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/7.stella)
add_test(NAME week-6-71_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/71.stella)
add_test(NAME week-6-73_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/73.stella)
add_test(NAME week-6-75_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/75.stella)
add_test(NAME week-6-77_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/77.stella)
add_test(NAME week-6-81_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/81.stella)
add_test(NAME week-6-9_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/9.stella)
add_test(NAME week-6-93_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/93.stella)
add_test(NAME week-6-95_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/95.stella)
add_test(NAME week-6-97_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/97.stella)
add_test(NAME week-6-99_stella COMMAND stella-interpreter typecheck /Users/daniilzimin4/compliers/ACCPA/cpp/tests/week-6/public/99.stella)


set_tests_properties(
    week-6-1_stella
    week-6-11_stella
    week-6-129_stella
    week-6-13_stella
    week-6-135_stella
    week-6-139_stella
    week-6-141_stella
    week-6-143_stella
    week-6-145_stella
    week-6-15_stella
    week-6-163_stella
    week-6-169_stella
    week-6-17_stella
    week-6-3_stella
    week-6-31_stella
    week-6-33_stella
    week-6-35_stella
    week-6-37_stella
    week-6-39_stella
    week-6-41_stella
    week-6-45_stella
    week-6-47_stella
    week-6-49_stella
    week-6-5_stella
    week-6-53_stella
    week-6-55_stella
    week-6-57_stella
    week-6-59_stella
    week-6-61_stella
    week-6-65_stella
    week-6-67_stella
    week-6-71_stella
    week-6-75_stella
    week-6-77_stella
    week-6-81_stella
    week-6-9_stella
PROPERTIES WILL_FAIL TRUE)
