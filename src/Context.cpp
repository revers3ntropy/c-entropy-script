#include <iostream>
#include <utility>

#include "../include/Context.h"

es::Context::~Context() {
    delete &symbol_table;
}

es::Error* es::Context::set_own(std::string id, es::Primitive* value) {
    if (!symbol_table.contains(id)) {
        symbol_table.insert({
            std::move(id),
            new Symbol(value, id)
        });
    }
    return nullptr;
}

void es::Context::log() {
    std::cout << "---- CONTEXT ----" << std::endl;
    for (auto const& [key, symbol] : symbol_table) {
        std::string out = key;
        if (symbol->is_const){
            out += " (CONST)";
        }

        out += ": " + symbol->value->str();
    }
    std::cout << "-----------------" << std::endl;
}

bool es::Context::has(const std::string& id) {
    auto [value, error] = this->get(id);
    if (error) return false;
    return value != nullptr;
}

bool es::Context::hasOwn(const std::string& id) {
    return symbol_table.contains(id);
}

std::tuple<es::Primitive*, es::Error*> es::Context::get(const std::string& id) {
    auto [symbol, error] = getSymbol(id);
    if (error) return {nullptr, error};
    return {symbol->value, nullptr};
}

std::tuple<es::Symbol*, es::Error*> es::Context::getSymbol(const std::string& id) {
    if (symbol_table.contains(id)) {
        Symbol* symbol = symbol_table.at(id);
        return {symbol, nullptr};
    }

    if (parent) {
        return parent->getSymbol(id);
    }

    return {nullptr, nullptr};
}

es::Error* es::Context::set(es::Primitive* val, const std::string& id, es::SymbolOptions* options) {
    Context* context = this;

    if (options->global) {
        context = root();
    } else {
        // searches upwards to find the identifier, and if none can be found then it assigns it to the current context
        while (!context->hasOwn(id) && context->parent != nullptr)
            context = context->parent;

        if (!context->hasOwn(id))
            context = this;

        return context->setOwn(val, id, options);
    }

    return nullptr;
}

es::Error* es::Context::setOwn(es::Primitive* val, const std::string& id, es::SymbolOptions* options) {
    if (symbol_table.contains(id)) {
        if (symbol_table.at(id)->is_const){
            return new Error(nullptr, nullptr, "TypeError","Symbol '" + id + "' is constant.");
        }
        symbol_table.erase(id);
    }

    symbol_table[id] = new Symbol(val, id);
    return nullptr;
}

void es::Context::remove(const std::string& id) {
    if (symbol_table.contains(id))
        symbol_table.erase(id);
}

es::Context* es::Context::root() {
    return parent != nullptr ? parent->root() : this;
}

void es::Context::clear() {
    for (auto const& [key, symbol] : symbol_table) {
        symbol_table.erase(key);
        delete symbol;
    }
}

void es::Context::reset_as_global() {
    if (!initialised_as_global) return;

    auto [print, print_err] = root()->get("print");
    auto [input, input_err] = root()->get("input");

    clear();

    initialise_as_global(print, input);
}

void es::Context::initialise_as_global(es::Primitive* print, es::Primitive* input) {

}
