include_guard(GLOBAL)

macro(printVars)
    foreach (var ${ARGV})
        message("${var} ::\t\t ${${var}}")
    endforeach ()
endmacro()

macro(printEnvs)
    foreach (var ${ARGV})
        message("${var} ::\t\t $ENV{${var}} \t (env)")
    endforeach ()
endmacro()

function(printProps target)
    foreach (var ${ARGV})
        get_target_property(OUTPUT ${target} ${var})
        message("${var} ::\t\t ${OUTPUT} \t (prop of ${target})")
    endforeach ()
endfunction()

