#pragma once
#include <string>

#include "RTResult.h"
#include "Error.h"
#include "Context.h"

es::RunTimeResult* run(const std::string& es_code, std::string filename, es::Context* context = new es::Context());
