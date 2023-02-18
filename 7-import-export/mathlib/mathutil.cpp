//
// Created by 于一 on 2023/2/17.
//
#include <string>
#include "math_symbol.h"

#ifdef OPENEXR_FOUND
#include "openexr.h"
#endif

#include <iostream>

namespace mathlib {
    std::string getInvert(const std::string &func) {
        if (func == "sqrt") {
            return "pow";
        } else if (func == "pow") {
            return "sqrt";
        } else {
            return "unknown";
        }
    }

    std::string getSymbol(const std::string &name) {
        if (name == "delta")
            return std::move(std::string(Delta_Symbol));
        return std::move(std::string("unknown"));
    }

    void useOpenEXR() {
#ifdef OPENEXR_FOUND
        int maj, min, patch;
        const char *extra;
        exr_get_library_version(&maj, &min, &patch, &extra);
        std::cout << "the OpenExr Version: " << maj << "." << min << "." << patch << "." << extra << std::endl;
#else
        std::cout << "no OpenExr" << std::endl;
#endif
    }
}