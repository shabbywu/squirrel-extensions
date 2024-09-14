set(CMAKE_CXX_STANDARD 20)

add_executable(sq_repl main.cpp plugins.cpp)
target_include_directories(sq_repl PRIVATE ${EXTERNAL_INCLUDE_DIR})
target_link_libraries(sq_repl PRIVATE sqbind17::sqbind17 libpeconv_mt)
target_link_directories(sq_repl PRIVATE ${EXTERNAL_LIBS_DIR})
target_compile_options(sq_repl PRIVATE /MT)
