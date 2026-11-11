// reflection.h
#pragma once
#include <any>
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class FunctionRegistry
{
public:
    using AnyArgs = std::vector<std::any>;
    using Invoker = std::function<std::any(const AnyArgs&)>;

    FunctionRegistry(const FunctionRegistry&)            = delete;
    FunctionRegistry& operator=(const FunctionRegistry&) = delete;
    FunctionRegistry(FunctionRegistry&&)                 = delete;
    FunctionRegistry& operator=(FunctionRegistry&&)      = delete;

    static FunctionRegistry& instance()
    {
        static FunctionRegistry reg;
        return reg;
    }

    void registerFunc(const std::string& name, Invoker invoker) { table_[name] = std::move(invoker); }

    std::any invoke(const std::string& name, const AnyArgs& args = {})
    {
        auto it = table_.find(name);
        if (it == table_.end())
            throw std::runtime_error("function not found: " + name);
        return it->second(args);
    }

    bool has(const std::string& name) const { return table_.count(name) > 0; }
    std::vector<std::string> list() const
    {
        std::vector<std::string> names;
        for (const auto& [name, _] : table_)
            names.push_back(name);
        return names;
    }

private:
    FunctionRegistry() = default;

    std::unordered_map<std::string, Invoker> table_;
};

// 把任意函数包装成 Invoker
template<typename Ret, typename... Args, size_t... I>
std::any invokeImpl(Ret (*fn)(Args...), const std::vector<std::any>& args, std::index_sequence<I...>)
{
    if (args.size() != sizeof...(Args))
        throw std::runtime_error("argument count mismatch");
    if constexpr (std::is_void_v<Ret>)
    {
        fn(std::any_cast<Args>(args[I])...);
        return {};
    }
    else
    {
        return fn(std::any_cast<Args>(args[I])...);
    }
}

template<typename Ret, typename... Args>
FunctionRegistry::Invoker makeInvoker(Ret (*fn)(Args...))
{
    return [fn](const std::vector<std::any>& args) -> std::any {
        return invokeImpl(fn, args, std::index_sequence_for<Args...> {});
    };
}

// 注册宏
#define REGISTER_FUNC(name, fn) \
    static bool _reg_##fn##__LINE__ = (FunctionRegistry::instance().registerFunc(name, makeInvoker(fn)), true)
