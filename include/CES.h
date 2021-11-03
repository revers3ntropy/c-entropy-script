#pragma once
#include <string>

#include "RTResult.h"
#include "Error.h"

std::tuple<es::RunTimeResult*, es::Error*> run(const std::string& es_code, std::string filename);
