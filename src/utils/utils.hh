#pragma once

#include "../sdl/common.hh"
#include <string>

std::string get_path(const char *relative_path);
std::string get_path(std::string relative_path);