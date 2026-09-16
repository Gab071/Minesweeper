cmake_minimum_required (VERSION 3.1)

# Tu wstawcie nazwę swojego projektu
project(saper)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall -Wextra -pedantic -Werror=return-type -Werror=parentheses -Werror=vla -Werror=array-bounds -Wcast-qual -Wmaybe-uninitialized )

# Windows specific config
# To możecie zmienić jeśli zainstalujecie SFML-a w innym miejscu
IF (WIN32)
    # Include local sfml cmake config
    set(SFML_DIR "C:/lib/SFML-2.5.1/lib/cmake/SFML")
    # Link sfml statically (Optional)
    set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)


add_executable(saper main.cpp Array2D.h
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
target_link_libraries(saper sfml-graphics)

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
