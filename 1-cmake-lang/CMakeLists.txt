include(../yi-cmake-utils/IO.cmake)

#============================================
#[=[
bracket comment
bracket comment
bracket comment
#]=]

#============================================
#CONCEPT:
#cmake has four type of vars:
#1. var: 临时变量
#2. cache vars: stored in CMakeCache.txt,形成build tree后，可以各种调整，可以在cmake-gui中修改
#3. env vars: 系统变量
#4. properties: scoped vars

#============================================
message("\n\n------vars------")

set(FOO "cached BAR" CACHE STRING "")
set(FOO "BAR")

message("FOO: $CACHE{FOO}")
#shortcut for set a bool cache var
option(MY_OPT_1 "help text")

message("FOO: ${FOO}")
message("PATH: $ENV{PATH}")

#we can list all the variables and caches
printDirProps(
        CACHE_VARIABLES
        VARIABLES
)
#https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html


#============================================
message("\n\n------scope of var------")
#CONCEPT: cmake has 2 of scope: function scope & directory scope

add_subdirectory(a-sub-proj)
message("Outside-Var" : ${Outside-Var})
unset(Outside-Var)
if (NOT DEFINED Outside-Var)
    message("Outside-Var is not set")
endif ()

#============================================
message("\n\n------func------")

function(myFunc arg1 arg2)
    set(myFuncVar "yyyy")
    message("funcVar: ${myFuncVar}")

    message("myFunc: ${arg1}, ${arg2}")
    message("ARGC=${ARGC},ARGV=${ARGV}")

    set(funcVarParentScope "yyyy" PARENT_SCOPE)# PARENT_SCOPE: set var in parent scope

    printVars(
            CMAKE_CURRENT_FUNCTION #func name
            CMAKE_CURRENT_FUNCTION_LIST_DIR
            CMAKE_CURRENT_FUNCTION_LIST_FILE
            CMAKE_CURRENT_FUNCTION_LIST_LINE
    )
endfunction()

myFunc("hello" "world" a;b;cl;"aaa")
message("funcVar Outside func: ${funcVar}")
message("funcVarParentScope Outside func: ${funcVarParentScope}")

#============================================
message("\n\n------macro------")

#macro has no scope
set(myList 1 2 3)
macro(printList list)
    #loop
    foreach (item IN LISTS ${list})
        message("item: ${item}")
    endforeach ()
endmacro()
printList(myList)

set(myList 1,2,3)
printList(myList)

#============================================
message("\n\n------list------")

set(myList a list "of;five;elements")
list(LENGTH myList myListLen)
#see more: GET JOIN FIND POP_BACK POP_FRONT...
message("the list is: ${myList}, len: ${myListLen}")

#============================================
message("\n\n------message------")
#message(FATAL_ERROR "this will end the process!")
message(WARNING "WARNING")
message(AUTHOR_WARNING "AUTHOR_WARNING")
message(NOTICE "NOTICE")
message(STATUS "STATUS")
message(VERBOSE "VERBOSE")
message(DEBUG "DEBUG")
message(TRACE "TRACE")