set(TARGET DDF_Shader_Compile)

file(GLOB_RECURSE SHADERS CONFIGURE_DEPENDS "./*.vert" "./*.frag")

add_executable(glslang::validator IMPORTED)
find_program(GLSLANG_VALIDATOR "glslangValidator" HINTS $ENV{VULKAN_SDK}/bin REQUIRED)
set_property(TARGET glslang::validator PROPERTY IMPORTED_LOCATION "${GLSLANG_VALIDATOR}")

set(SPVS "")

foreach(SHADER ${SHADERS})
    get_filename_component(SHADER_NAME ${SHADER} NAME)
    set(SPV_FILE "${CMAKE_CURRENT_SOURCE_DIR}/generated/${SHADER_NAME}.spv")
    list(APPEND SPVS ${SPV_FILE})
    add_custom_command(
            OUTPUT ${SPV_FILE}
            COMMAND glslang::validator -o ${SPV_FILE} ${SHADER}
            ARGS --target-env vulkan1.0 ${SHADER_SOURCES} --quiet
            WORKING_DIRECTORY ${working_dir}
            DEPENDS ${SHADER}
            COMMENT "Compiling Shaders"
            VERBATIM
    )
endforeach()

message(STATUS "xxxx ${SPVS}")

add_custom_target(${TARGET} DEPENDS ${SPVS} SOURCES ${SHADERS})
