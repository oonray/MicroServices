cmake_minimum_required(VERSION "3.18")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_testing()
include(CPack)

include(FetchContent)

project(jwt_auth)

include_directories(c_src)
include_directories(c_inc)

link_libraries(argparse)
link_libraries(tritree)
link_libraries(fileio)
link_libraries(ringbuffer)
link_libraries(vector)

FILE(GLOB c_src "c_src/*.c")
list(FILTER c_src EXCLUDE REGEX "main")

#janson
find_package(jansson)
include_directories(${JANSSON_INCLUDE_DIR})
link_libraries(${JANSSON_LIBRARIES})
#libjwt
find_package(libjwt)
include_directories(${lIBJWT_INCLUDE_DIR})
link_libraries(${LIBJWT_LIBRARIES})
#executable
add_executable(server c_inc/mongoose/mongoose.c c_src/main.c ${c_src} c_inc/bstring/bstrlib.c)


#tests
add_executable(server_tests c_inc/munit/munit.c c_inc/mongoose/mongoose.c c_tests/main.c ${c_src} c_inc/bstring/bstrlib.c)
add_test(server_test server_tests)
