function(Format target directory)
    find_program(CLANG-FORMAT_PATH clang-format REQUIRED)
    set(EXPRESSION h hpp hh c cc cxx cpp)
    list(TRANSFORM EXPRESSION PREPEND "${directory}/*.")
    file(GLOB_RECURSE SOURCE_FILES FOLLOW_SYMLINKS
            LIST_DIRECTORIES false ${EXPRESSION}
            )
    add_custom_command(TARGET ${target} PRE_BUILD COMMAND
            ${CLANG-FORMAT_PATH} -i --style=file ${SOURCE_FILES})
endfunction()

# check these tools:
# <LANG>_CLANG_TIDY
# <LANG>_CPPCHECK
# <LANG>_CPPLINT
# <LANG>_INCLUDE_WHAT_YOU_USE
# LINK_WHAT_YOU_USE

add_executable(6-code-tool-sanitizer bad_index.cpp)
#target_compile_options(x-sanitizer PRIVATE -analyze -RTC1)
#target_compile_options(6-code-tool-sanitizer PRIVATE  -fsanitize=address)
#target_compile_options(x-sanitizer PRIVATE -O2 -Rpass=inline)
