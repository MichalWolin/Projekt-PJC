cmake_minimum_required(VERSION 3.24)
project(Projekt)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG a0b8a92e3d1532361c2f7feb63babc5c18d00ef2
)

FetchContent_MakeAvailable(fmt)

add_executable(Projekt main.cpp findPassword.cpp sortPasswords.cpp addPassword.cpp editPassword.cpp removePassword.cpp addCategory.cpp removeCategory.cpp addCategory.h addPassword.h editPassword.h findPassword.h removeCategory.h removePassword.h sortPasswords.h Password.cpp Password.h)
target_link_libraries(Projekt fmt)
