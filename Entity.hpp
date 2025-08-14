#include <iostream>
#include <functional>

inline bool __ENTITY_DEBUG_ENABLED = false;

template <typename T>
struct Entity
{
private:
    T _EntValue;
    std::function<bool(const T&)> _EntityValidator = [](const T& val) {
        return true;
    };

public:
    T _EntityValue;

    Entity() = default;
    Entity(T object) : _EntValue(object), _EntityValue(object) {}


    void _SetValidator(const std::function<bool(const T&)>& b) {
        if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: _SetValidator called)\n"; }
        _EntityValidator = b;
    }

    std::function<bool(const T&)> _GetValidator() const {
        if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: _GetValidator called)\n"; }
        return _EntityValidator;
    }

    bool _EntitySet(const T& object) {
        if (_EntityValidator(object)) {
            if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: _EntitySet succeeded)\n"; }
            _EntValue = object;
            _EntityValue = object;
            return true;
        } else {
            if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG_WARN: The value you are trying to set violates the validator function. This is likely not what you want!)\n"; }
            return false;
        }
    }

    T _EntityGet() const {
        if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: _EntityGet called)\n"; }
        return _EntValue;
    }

    void _UpdateEntity() {
        if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: _UpdateEntity called)\n"; }
        _EntitySet(_EntityValue);
    }


    Entity<T>& operator=(const T& rhs) { _EntitySet(rhs); return *this; }
    Entity<T>& operator+=(const T& rhs) { _EntitySet(_EntValue + rhs); return *this; }
    Entity<T>& operator-=(const T& rhs) { _EntitySet(_EntValue - rhs); return *this; }
    Entity<T>& operator*=(const T& rhs) { _EntitySet(_EntValue * rhs); return *this; }
    Entity<T>& operator/=(const T& rhs) { _EntitySet(_EntValue / rhs); return *this; }
    Entity<T>& operator%=(const T& rhs) { _EntitySet(_EntValue % rhs); return *this; }
    Entity<T>& operator&=(const T& rhs) { _EntitySet(_EntValue & rhs); return *this; }
    Entity<T>& operator|=(const T& rhs) { _EntitySet(_EntValue | rhs); return *this; }
    Entity<T>& operator^=(const T& rhs) { _EntitySet(_EntValue ^ rhs); return *this; }
    Entity<T>& operator<<=(const T& rhs) { _EntitySet(_EntValue << rhs); return *this; }
    Entity<T>& operator>>=(const T& rhs) { _EntitySet(_EntValue >>= rhs); return *this; }

    Entity<T>& operator++() { _EntitySet(_EntValue + 1); return *this; }
    Entity<T> operator++(int) { Entity<T> temp = *this; _EntitySet(_EntValue + 1); return temp; }
    Entity<T>& operator--() { _EntitySet(_EntValue - 1); return *this; }
    Entity<T> operator--(int) { Entity<T> temp = *this; _EntitySet(_EntValue - 1); return temp; }

    operator const T&() const { return _EntValue; }

    Entity<T> operator+(const T& rhs) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: + op)\n"; } return Entity(_EntValue + rhs); }
    Entity<T> operator-(const T& rhs) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: - op)\n"; } return Entity(_EntValue - rhs); }
    Entity<T> operator*(const T& rhs) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: * op)\n"; } return Entity(_EntValue * rhs); }
    Entity<T> operator/(const T& rhs) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: / op)\n"; } return Entity(_EntValue / rhs); }
    Entity<T> operator%(const T& rhs) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: % op)\n"; } return Entity(_EntValue % rhs); }

    Entity<T> operator&(const T& rhs) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: & op)\n"; } return Entity(_EntValue & rhs); }
    Entity<T> operator|(const T& rhs) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: | op)\n"; } return Entity(_EntValue | rhs); }
    Entity<T> operator^(const T& rhs) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: ^ op)\n"; } return Entity(_EntValue ^ rhs); }
    Entity<T> operator<<(const T& rhs) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: << op)\n"; } return Entity(_EntValue << rhs); }
    Entity<T> operator>>(const T& rhs) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: >> op)\n"; } return Entity(_EntValue >> rhs); }
    Entity<T> operator~() const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: ~ op)\n"; } return Entity(~_EntValue); }

    bool operator!() const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: ! op)\n"; } return !_EntValue; }
    bool operator&&(const Entity<T>& other) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: && op)\n"; } return _EntValue && other._EntValue; }
    bool operator||(const Entity<T>& other) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: || op)\n"; } return _EntValue || other._EntValue; }

    bool operator==(const Entity<T>& other) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: == op)\n"; } return _EntValue == other._EntValue; }
    bool operator!=(const Entity<T>& other) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: != op)\n"; } return _EntValue != other._EntValue; }
    bool operator<(const Entity<T>& other) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: < op)\n"; } return _EntValue < other._EntValue; }
    bool operator>(const Entity<T>& other) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: > op)\n"; } return _EntValue > other._EntValue; }
    bool operator<=(const Entity<T>& other) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: <= op)\n"; } return _EntValue <= other._EntValue; }
    bool operator>=(const Entity<T>& other) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: >= op)\n"; } return _EntValue >= other._EntValue; }

    T& operator*() { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: * (deref) op)\n"; } return _EntValue; }
    const T& operator*() const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: const * (deref) op)\n"; } return _EntValue; }
    T* operator->() { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: -> op)\n"; } return &_EntValue; }
    const T* operator->() const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: const -> op)\n"; } return &_EntValue; }

    template<typename Index>
    auto& operator[](Index&& i) { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: [] op)\n"; } return _EntValue[std::forward<Index>(i)]; }
    const T& operator()() const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: () op)\n"; } return _EntValue; }
};