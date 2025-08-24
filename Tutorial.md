# Tutorial (as of v.1.2.0)
### 1. Initializing an Entity
This is the most basic part of all. When you initialize entities, you must specify the data type it will hold inside the template brackets (`<>`).
```cpp
int main() {
    Entity<int> Object = 10; // Integer wrapped with entity
}
```
And, there is other ways to initialize an entity:
```cpp
int main() {
    Entity<int> a = 1; // initialized integer
    Entity<int> b; // Uninitialized integer
    Entity<int> k(10); // initialized integer with () constructor
    Entity<std::vector<int>> c;
    c.EntitySet(std::vector<int>(10, 0)); // initializing an entity with custom parameter
    Entity<int> j(a); // Copying another entity
}
```

### 2. Core & Draft values
There is two types of values in the `Entity` : an draft value and an core value.
Draft values are used to edit the variable before updating the whole variable and modifying the variable does not affect the core variable itself. And functions like `EntityGet()` will only work with core values, not the draft one.
```cpp
int main() {
    Entity<int> a = 10;
    a.EntityValue = 15; // EntityValue is the draft variable.
    std::cout << a.EntityGet(); // Getting the copy version of the current entity core value. You can see the value is still 10
    a.UpdateEntity(); // Updating the core value itself with the draft varaible
    std::cout << a.EntityGet(); // Now the value is 15
    // Or, to set the core value directly
    a.EntitySet(30);
    // a = 30; // << Or by using this shortcut
    std::cout << a.EntityGet(); // The value is now 30
}
```

### 3. Entity operators
`Entity` almost supports (or all) operators to perform operations directly without using `EntityGet()`, but if you want to work with the draft values, its an different process. You have to use `EntityValue` if you want to perform operations in the draft variable.
While `Entity` supports all operators, these operators only work with core values. The `=` operator you seen in the article 2, is an operator used directly in setting the core values directly to the core variable.
```cpp
int main() {
    Entity<int> a = 10;
    std::cout << a + 35; // prints core value of a plus 35
    std:: cout << a; // note the core value still remains unchanged
}
```

### 4. Validators
Validator is an value managing system to whether check if the value follows the validator's rules or not. Validator is similar to a gate where values have to do a full check to pass the gate. If it follows the rule, the value passes, if not, the gate disallows the value to pass the gate. To get started, the default validator when creating an `Entity` always return `true`.
```cpp
int main() {
    Entity<int> a = 11;
    a.SetValidator([](auto b) // Validator to check whether the value is divisible by two or not.
                    {
                        return b%2 == 0;
                    });
    //! Remember that validators upon initialization will check the value immediately. If the value violates the validator, the core value will be set to default state (wihtout performing a check with the validator).
    // Because a is set as 11, and it violates the validator, the core value is set to uninitialized.
    std::cout << a.EntityGet();
    // Note that operator that changes the core variable also follows the validator, and the value gets rejected once it is not accepted by the validator.
    // If you want to get the current validator to use the validator standalone, you can use GetValidator()
    auto val = a.GetValidator();
    std::cout << val(15);
}

```

### 5. States
States is similar to backups, which saves the current core value into a list of state. This is an expensive operation since if the type of the Entity is big, the state list consumes more memory for each state you save. If some states are not used anymore, you can use `ClearStates()` to clear all states saved.
```cpp
int main() {
    Entity<int> a = 11;
    ll SaveStateID = a.SaveState(); // The variable's value is saved to the list of states, then the function returns the ID (integer) for which can be loaded later.
    a.EntitySet(100);
    std::cout << a.EntityGet() << '\n'; // prints 100
    a.LoadState(SaveStateID); // Loads the save state. Note that if the index does not exist, it throws std::out_of_range, in an weird way.
    std::cout << a.EntityGet() << '\n';
    // IF you want to get an standalone version of the state, you can use GetState().
    a.EntitySet(69);
    ll OtherSaveState = a.SaveState();
    std::cout << a.GetState(OtherSaveState);
}
```

### 6. Type-casting
The `Entity` struct itself allows type-casting, for which it auto-casts by values from constructors, setting values.
And, `Entity` also supports with operators that in many cases you don't have to do anything because the compiler automatically converts the `Entity` as seen in past articles.
```cpp
int main() {
    Entity<double> a(10.345);
    float floatex  = static_cast<float>(playerStamina);

    // this also works for integer truncation
    int intex = static_cast<int>(playerStamina);

    std::cout << "float : " << staminaAsFloat.EntityGet() << std::endl; // 10.345
    std::cout << "integer : " << staminaAsInt.EntityGet() << std::endl;     // 10
}
```
The compiler also auto converts the value in constructors:
```cpp
int main() {
    Entity<int> b(10.345); // b becomes 10 as 10.345 (double, float...) is auto type-casted into integer.
    std::cout << b.EntityGet(); // prints 10
}
```

### 7. Erasing entities
`EraseEntity()` erases both `Entity`'s draft and core value. Remember that it is not affected by validators.
```cpp
int main()
{
	Entity<int> j(100);
    std::cout << j << '\n'; // 100
    j.EraseEntity();
    std::cout << j; // uninitialized integer's value
}
```

### 8. Accessing type's elements directly
You can interact with its members directly using the pointer-like -> (arrow) and * (dereference) operators.
The `->` operator gives you pointer-like access to the members of the wrapped object. This is the most common way to call member functions.
```cpp
int main() {
    Entity<std::vector<int>> a({1,3,6,4,78,3,6});
    a->push_back(10); // calls push_back in a
    for (auto i : a.EntityGet())
    {
        std::cout << i << ' ';
    }
}
// or
int main() {
    Entity<std::vector<int>> a({1,3,6,4,78,3,6});
    (*a).push_back(10); // calls push_back in a
    for (auto i : (*a))
    {
        std::cout << i << ' ';
    }
}
```

### 9. Major informations
- Remember that `Entity` acts like an wrapper for the object meanwhile you can still do everything the type does. Such as sorting an vector while vector is wrapped with Entity, and it works.
```cpp
int main() {
    Entity<std::vector<int>> a({1,3,6,4,78,3,6});
    std::sort(a->begin(), a->end());
    for (auto i : a.EntityGet())
    {
        std::cout << i << ' ';
    }
}
// or
int main() {
    Entity<std::vector<int>> a({1,3,6,4,78,3,6});
    std::sort((*a).begin(), (*a).end());
    for (auto i : (*a))
    {
        std::cout << i << ' ';
    }
}
```
