include(../yi-cmake-utils/IO.cmake)

#[=[
bracket comment
bracket comment
bracket comment
#]=]

#run in configure time
set(FOO "BAR" CACHE STRING "")
message("FOO: $CACHE{FOO}")
message("PATH: $ENV{PATH}")

#scope of var
#NOTE cmake has 2 of scope: function scope & directory scope
add_subdirectory(a-sub-proj)
message("Outside-Var" : ${Outside-Var})
unset(Outside-Var)
if (NOT DEFINED Outside-Var)
    message("Outside-Var is not set")
endif ()

#func
function(myFunc arg1 arg2)
    set(myFuncVar "yyyy")
    message("funcVar: ${myFuncVar}")

    message("myFunc: ${arg1}, ${arg2}")
    set(funcVarParentScope "yyyy" PARENT_SCOPE)

    printVars(CMAKE_CURRENT_FUNCTION
            CMAKE_CURRENT_FUNCTION_LIST_DIR
            CMAKE_CURRENT_FUNCTION_LIST_FILE
            CMAKE_CURRENT_FUNCTION_LIST_LINE)
endfunction()

myFunc("hello" "world")
message("funcVar Outside func: ${funcVar}")
message("funcVarParentScope Outside func: ${funcVarParentScope}")

#macro
#NOTE macro has no scope
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

#list
set(myList a list "of;five;elements")
list(LENGTH myList myListLen)
#see more: GET JOIN FIND POP_BACK POP_FRONT...
message("the list is: ${myList}, len: ${myListLen}")

#message
#message(FATAL_ERROR "this will end the process!")
message(WARNING "WARNING")
message(AUTHOR_WARNING "AUTHOR_WARNING")
message(NOTICE "NOTICE")
message(STATUS "STATUS")
message(VERBOSE "VERBOSE")
message(DEBUG "DEBUG")
message(TRACE "TRACE")

