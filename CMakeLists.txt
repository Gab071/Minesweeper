cmake_minimum_required (VERSION 3.1)

# Set name of the project
project(Minesweeper)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall -Wextra -pedantic -Werror=return-type -Werror=parentheses -Werror=vla -Werror=array-bounds -Wcast-qual -Wmaybe-uninitialized )

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(
        -Wall 
        -Wextra 
        -Wpedantic 
        -Werror=return-type 
        -Werror=parentheses 
        -Werror=vla 
        -Werror=array-bounds 
        -Wcast-qual 
        -Wmaybe-uninitialized
    )
endif()

# Windows specific config
# You can change it if you install SFML in different directory (or have different version of it)
IF (WIN32)
    # Include local sfml cmake config
    set(SFML_DIR "C:/lib/SFML-2.6.1/lib/cmake/SFML")
    # Link sfml statically (Optional)
    set(SFML_STATIC_LIBRARIES TRUE)
ELSEIF (UNIX AND NOT APPLE)
    # Linux-specific config:
    # Linux system-installed SFML (e.g., via apt) installs CMake files into standard 
    # paths (/usr/lib/x86_64-linux-gnu/cmake/SFML or /usr/lib/cmake/SFML).
    # CMake finds it automatically—no SFML_DIR variable needed!
ENDIF()

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)


add_executable(Minesweeper main.cpp Array2D.h
        MinesweeperBoard.cpp
        MinesweeperBoard.h
        MSBoardTextView.h
        MsBoardTextView.cpp
        MSTextController.cpp
        MSTextController.h
        MSSFMLView.cpp
        MSSFMLView.h
        MSSFMLController.cpp
        MSSFMLController.h
        Menu.cpp
        Menu.h)
target_link_libraries(Minesweeper sfml-graphics)

file(COPY ${CMAKE_SOURCE_DIR}/pngs/smile.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/pngs/field0.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/pngs/field1.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/pngs/field2.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/pngs/field3.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/pngs/field4.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/pngs/field5.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/pngs/field6.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/pngs/field7.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/pngs/field8.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/pngs/angry.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/pngs/flag.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Press_Start_2P/PressStart2P-Regular.ttf DESTINATION ${CMAKE_BINARY_DIR})
