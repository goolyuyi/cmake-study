include_guard(GLOBAL)

macro(printVars)
    foreach (var ${ARGV})
        message("${var} ::\t\t ${${var}}")
    endforeach ()
endmacro()

