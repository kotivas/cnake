
# Define the project name
project(cnake)

# Set the cmake minimum version to 3.21
cmake_minimum_required(VERSION 3.21)

# find all used librariesw
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# copy assets to the build folder
file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(cnake WIN32 src/main.cpp src/game.cpp src/snake.cpp src/renderwindow.cpp )

target_link_libraries(cnake SDL2::SDL2 SDL2::SDL2main
							SDL2_image::SDL2_image
							SDL2_mixer::SDL2_mixer
							SDL2_ttf::SDL2_ttf
)