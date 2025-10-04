cmake_minimum_required(VERSION 4.0)

project(LearnGL)

file(GLOB HGL_SRC_FILES "HGL/*.cpp")
file(GLOB HGL_HEADER_FILES "HGL/include/*.hpp")

add_executable(LearnGL 
    vendor/glad/src/gl.c vendor/glad/include/glad/gl.h
    ${HGL_HEADER_FILES}
    ${HGL_SRC_FILES}

    main.cpp
)



add_subdirectory(vendor/glfw)
target_link_libraries(LearnGL glfw)

add_subdirectory(vendor/glad)
target_link_libraries(LearnGL glad)

target_include_directories(LearnGL PRIVATE vendor/glm)
target_include_directories(LearnGL PRIVATE vendor/glad/include)
target_include_directories(LearnGL PRIVATE vendor/stb)

set_property(TARGET LearnGL PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/")



if(MSVC)
    string(REGEX REPLACE "/W[1-3]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    string(REGEX REPLACE "/W[1-3]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    target_compile_options(LearnGL  PRIVATE /WX /permissive-)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /std:c11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")

    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

    if(ASN)
        target_compile_options(LearnGL  PRIVATE /fsanitize=address)
        target_link_options(LearnGL PRIVATE /INCREMENTAL:NO /INFERASANLIBS) 
    endif()


else()

    target_compile_options(LearnGL  PRIVATE -Wall -Wextra -pedantic -Werror -Wno-language-extension-token)


    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")
    if(ASN)
        target_compile_options(LearnGL  PRIVATE -fsanitize=address)
        target_link_options(LearnGL  PRIVATE -fsanitize=address)
    endif()
endif()
