#pragma once
#include <string>
#include <map>

#include "Symbol.h"
#include "Error.h"
#include "Primitive.h"

namespace es {
    class Context {
        std::map<std::string, Symbol*> symbol_table;
        bool deleted;
        bool initialised_as_global;
        Context* parent;

    public:
        Context():
            symbol_table({}),
            deleted(false),
            initialised_as_global(false),
            parent(nullptr)
        {}
        ~Context();
        Error* set_own(std::string id, Primitive* value);
        bool has(const std::string& id);
        bool hasOwn(const std::string& id);
        std::tuple<es::Primitive*, es::Error*> get(const std::string& id);
        std::tuple<es::Symbol*, es::Error*> getSymbol(const std::string& id);
        Error* set(Primitive* val, const std::string& id, SymbolOptions* options);
        Error* setOwn (Primitive* val, const std::string& id, SymbolOptions* options);
        void remove (const std::string& id);
        Context* root();
        void log();
        void clear();
        void reset_as_global();


        void initialise_as_global (es::Primitive* print, es::Primitive* input);
    };
}