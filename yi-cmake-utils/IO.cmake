include_guard(GLOBAL)

macro(printVars)
    foreach (var ${ARGV})
        message("${var} \t=\t ${${var}}")
    endforeach ()
endmacro()

macro(printEnvs)
    foreach (var ${ARGV})
        message("${var} \t=\t $ENV{${var}} \t (env)")
    endforeach ()
endmacro()

macro(printCaches)
    foreach (var ${ARGV})
        message("${var} \t=\t $Cache{${var}} \t (env)")
    endforeach ()
endmacro()

function(printProps SCOPE SVAR)
    foreach (var ${ARGN})
        get_property(_OUTPUT ${SCOPE} ${SVAR} PROPERTY ${var})
        message("${var} \t=\t ${_OUTPUT} \t (prop of ${SCOPE}::${SVAR})")
    endforeach ()
endfunction()

function(printTargetProps TARGET)
    set(_TARGET ${TARGET})
    printProps(TARGET ${_TARGET} ${ARGN})
endfunction()

function(printDirProps DIR)
    set(_DIR ${DIR})
    printProps(DIRECTORY ${_DIR} ${ARGN})
endfunction()


