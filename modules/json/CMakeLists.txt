add_library(jsonlib SHARED main.cpp)
target_include_directories(jsonlib PRIVATE ${EXTERNAL_INCLUDE_DIR})
target_link_libraries(jsonlib PRIVATE sqbind17::sqbind17)
target_compile_options(jsonlib PRIVATE /MT)
