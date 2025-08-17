# Entity (`Entity.hpp`)

A C++ 17 header-only library for creating states/managing variables more easier/expanded. This wrapper allows you to treat complex, state-managed objects with the same syntactic ease as a primitive type like `int` or `float`.

## About The Project

In standard C++, primitive variables offer no protection. Such as setting an integer and set it as `k` and then change it.

This `Entity` wrapper solves that problem. By wrapping a variable in an `Entity<T>` object, you gain a powerful safety net.

*instead of this (unsafe):*
```cpp
int health = 100;
health -= 500; // Oops, health is now -400!
```                  
**You do this (safe and controllable):**
```cpp
#include "Entity.hpp"

Entity<int> health(100);
// Set a rule ONCE: health must be between 0 and 100.
health._SetValidator([](int val){ return val >= 0 && val <= 100; }); // using lambda expressions

health -= 500; // Operation is automatically rejected by the validator.
// The value of health remains safely at 0.
```

The library is designed with the principles of modern **Entity-Component-System (ECS)** architecture in mind, making it a perfect building block for creating great components in game engines, simulations, or any complex application state.

## Key Features (simplified)

-   **Transparent Syntax**: Thanks to extensive operator overloading, `Entity<int>` behaves almost exactly like a regular int.
-   **Built-in Validation**: Assign rules (validators) to an `Entity` to ensure it can never be put into an invalid state.
-   **Global Debug Mode**: A simple global flag (`__ENTITY_DEBUG_ENABLED`) can be turned on to print detailed logs for every operation, helping you trace data flows.
-   **State Management**: A built-in "draft" vs. "committed" state model (`_EntityValue` vs. the internal value) allows for patterns like UI put validation before committing to the core state.
-   **Header-Only**: No complex build steps. Just include `Entity.hpp` and you're ready to go.
-   **Generic & Flexible**: Works with any data type (`int`, `std:string`, custom `struct`s, and even pointers).

## Getting Started

This is a header-only library, making installation simple.

1.  Download the `Entity.hpp` file from this repository.
2.  Place it in your project's `include` directory (or wherever you keep your headers).
3.  Include it in your C++ files:
    ```cpp
    #include "include/Entity.hpp"
    ```
4. You're done with setting up Entity library.

## Usage and Tutorial
<img width="733" height="419" alt="image" src="https://github.com/user-attachments/assets/38c74c0e-7b93-4931-a67f-49cbd787ba29" />
<img width="783" height="628" alt="image" src="https://github.com/user-attachments/assets/5c4c8e53-c44b-4db3-b182-6511111b4fa9" />
<img width="1193" height="203" alt="image" src="https://github.com/user-attachments/assets/5e8bd00c-f5ce-4d46-aef4-f968217b74f4" />
