function(add_demo NAME)
    include_directories("../src")
    add_executable(${NAME} ${NAME}.cpp)
    target_link_libraries(${NAME} PRIVATE DDF)
    set_target_properties(${NAME} PROPERTIES FOLDER Samples)
endfunction()

add_demo(hello)
