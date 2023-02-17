//
// Created by 于一 on 2023/2/17.
//
#include <string>
#include "math_symbol.h"

namespace mathlib {
    std::string getInvert(const std::string & func) {
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
}