cmake_minimum_required(VERSION 3.6)
project(mirage)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(warnings "-pedantic -Wall -Wextra -Werror -Weffc++")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-pedantic -Wall -Wextra -Werror -Weffc++ -fsanitize=undefined")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()


set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${warnings}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings}")



set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package( Boost )
include_directories( ${Boost_INCLUDE_DIRS} )

link_libraries(${Boost_LIBRARIES})
include_directories(${CMAKE_SOURCE_DIR})

set(SOURCE_FILES
    include/AST.h
    include/CompilerException.h
    include/FilePos.h
    include/IFunction.h
    include/Lexer.h
    include/Parser.h
    include/Token.h
    include/Type.h
    include/StdLib/Define.h
    include/StdLib/Not.h
    include/ASTFunction.h
    include/StdLib/CreateFunction.h
    include/Graphics.h
    include/StdLib/And.h
    include/StdLib/Import.h
    include/StdLib/Error.h
    include/StdLib/Debug.h
    src/StdLib/Debug.cpp
    src/StdLib/Error.cpp
    src/StdLib/Import.cpp
    src/StdLib/And.cpp
    src/Graphics.cpp
    src/StdLib/CreateFunction.cpp
    src/ASTFunction.cpp
    src/StdLib/Not.cpp
    src/StdLib/Define.cpp
    src/IFunction.cpp
    src/AST.cpp
    src/CompilerException.cpp
    src/Lexer.cpp
    src/Parser.cpp
    src/Token.cpp
    src/Type.cpp
    include/StdLib/CreateGraphicsElement.h
    src/StdLib/CreateGraphicsElement.cpp
    src/Vector.cpp
    include/GraphicsObject.h
    src/GraphicsObject.cpp
    include/StdLib/Macro.h
    src/StdLib/Macro.cpp
    include/StdLib/Or.h
    src/StdLib/Or.cpp
    include/StdLib/Error.h
    src/StdLib/Error.cpp
    include/StdLib/List.h
    src/StdLib/List.cpp
    include/StdLib/First.h
    src/StdLib/First.cpp
    include/StdLib/Rest.h
    src/StdLib/Rest.cpp
    include/StdLib/AddBack.h
    src/StdLib/AddBack.cpp
    include/StdLib/AddFront.h
    src/StdLib/AddFront.cpp
    include/StdLib/Size.h
    src/StdLib/Size.cpp
    include/StdLib/Times.h
    src/StdLib/Times.cpp
    include/StdLib/Divide.h
    src/StdLib/Divide.cpp
    include/StdLib/BiggerThan.h
    src/StdLib/BiggerThan.cpp
    include/StdLib/LessThan.h
    src/StdLib/LessThan.cpp
    include/StdLib/BiggerOrEqual.h
    src/StdLib/BiggerOrEqual.cpp
    include/StdLib/LessOrEqual.h
    src/StdLib/LessOrEqual.cpp
    include/StdLib/Plus.h
    src/StdLib/Plus.cpp
    include/StdLib/Minus.h
    src/StdLib/Minus.cpp
    include/StdLib/If.h
    src/StdLib/If.cpp
    include/StdLib/Equals.h
    src/StdLib/Equals.cpp
    include/StdLib/Quote.h
    src/StdLib/Quote.cpp
    include/StdLib/Eval.h
    src/StdLib/Eval.cpp
    main.cpp)
add_executable(interpreter ${SOURCE_FILES})
