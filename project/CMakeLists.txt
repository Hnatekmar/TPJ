cmake_minimum_required(VERSION 3.6)
project(mirage)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
    include/AST.h
    include/CompilerException.h
    include/FilePos.h
    include/IFunction.h
    include/Lexer.h
    include/Parser.h
    include/Token.h
    include/Type.h
    src/IFunction.cpp
    src/AST.cpp
    src/CompilerException.cpp
    src/Lexer.cpp
    src/Parser.cpp
    src/Token.cpp
    src/Type.cpp
    src/Vector.cpp
    main.cpp)

add_executable(interpreter ${SOURCE_FILES})
