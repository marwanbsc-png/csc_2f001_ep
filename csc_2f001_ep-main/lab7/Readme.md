# The Lanister bank, part II

**Objective:** The objective of this exercise is to understand references, operator overloading and the basic C++ containers.

## A better interface

In this exercise, you will make the interface of the tree map of the Lanister bank easier to use. For that, we will use references and we will overload some operators.

### Question 1

We will start by improving the `at` and `set_at` methods. For that, replace the signature of these methods:

* from `void set_at(const K key, const V value)` to `void set_at(const K& key, const V& value)`,
* and from `V at(const K& key)` to `V& at(const K& key)`.

Why using references is more efficient?

> **Tip:**
> If `K` and `V` are objects, we avoid copying the keys and values. For example, let us consider the following code:
>
> ```cpp
> std::string str = "Tyrion";
> map.set_at(str, 2);
> std::cout << map.at(str) << std::endl;
> ```
>
> With the old signature, `str` is copied when we call `set_at` and `at`. This copy leads to a copy of the whole array of characters "Tyrion", which is costly. Here, the string is small, and the C++ library avoids allocating and freeing memory. However, for a longer string, the cost can become prohibitive since each copy would also lead to allocated and freed memory for the parameters.

### Question 2

Add now a `V& operator [] (const K& key)` method in `treemap_t`. This method creates a node associated to the key `key`, and returns a reference to the value inside the node. For that, think that you can reuse the `lookup` method.

If your code is correct, you can now initialize the bank with the following code:

```cpp
map["Tyrion"] = 2;
map["Jaime"] = 15;
map["Cersei"] = 63;
map["Tywin"] = 75;
map["Kevan"] = 48;
map["Lancel"] = 70;
map["Alton"] = 54;
map["Martyn"] = 32;
map["Willem"] = 6;
```

Why this code actually modifies the balance field of the account inside the `node_t` objects?

> **Tip:**
> Since the operator `[]` returns a reference to the value inside a node, the `=` operator copies the balance directly in the node.

### Question 3

The C++ language offers a construct to transparently enumerate the elements of a container, i.e., of a data structure used to store a set of objects. For that, the developer can use a range-based loop:

```cpp
for(auto& var: map) { ... }
```

The compiler rewrites this code in:

```cpp
for(auto it=map.begin(); it!=map.end(); ++it) {
  auto& var = *it;
  ...
}
```

In this code, `it` is an iterator. An iterator is a structure that has to overload:

* the operator `!=` to know if we reached the end of the container,
* the operator `++` to move the iterator to the next element,
* and the operator `*` to convert the iterator into an element of the container.

For our tree map, you implemented the `iterator_t` structure, which is able to enumerate the elements of the map. This structure is a good starting point to build a C++ iterator. For the moment, you use the `iterator_t` class like this:

```cpp
for(auto it = map.begin(); it.cur != nullptr; it.next()) {
  std::cout << it.cur->key << " => " << it.cur->value << std::endl;
}
```

As a first step to transform `iterator_t` into a fully fledge C++ iterator, start by implementing an `iterator_t& operator ++()` operator in `iterator_t`. You should now be able to enumerate the elements with this loop:

```cpp
for(auto it = map.begin(); it.cur != nullptr; ++it) { ... }
```

### Question 4

Implement a `bool operator != (const iterator_t& it) const` operator in `iterator_t`, which returns true if `this->cur` and `it.cur` are different. Add also a `iterator_t end()` method in `treemap_t`. This method returns an instance of `iterator_t` in which `cur` is initialized to `nullptr`. You should now be able to enumerate the elements with this loop:

```cpp
for(auto it = map.begin(); it != map.end(); ++it) { ... }
```

> **Note:**
> First, be careful: your current `iterator_t` constructor does probably not yet handle the case where the root of the tree is null. Also, a comparison with `!=` between the iterators means a comparison of the pointers, not of the objects pointed by the pointers. In other words, your function is supposed to simply execute this test `this->cur != it.cur`.

### Question 5

Implement a `pair_t& operator *()` in `iterator_t`. This method simply returns `*cur` since `cur` is an instance of `node_t`, which inherits from `pair_t`. You should now be able to enumerate the elements with this loop:

```cpp
for(auto it=map.begin(); it!=map.end(); ++it) {
  auto& pair = *it;
  std::cout << pair.key << " => " << pair.value << std::endl;
}
```

### Question 6

Replace your loop by:

```cpp
for(auto& pair: map) {
  std::cout << pair.key << " => " << pair.value << std::endl;
}
```

### Question 7

The `auto` keyword can also be used to transparently unpack a structure. In our loop, for example, `pair` is a structure with a key (first field) and a value (second field). We can thus unpack it with a construct that looks like the python `a, b = f()` construct. To see how it works, replace your loop by:

```cpp
for(auto& [key, value]: map) {
  std::cout << key << " => " << value << std::endl;
}
```

## Complex keys and values

Now that our `treemap_t` has a nice interface, we can use it to store more complex keys and values.

### Question 1

Currently, the map associates an account name (a `std::string`) to a balance (a `double`). Instead, we will associate an account name to an `account_t` structure that we will implement step by step. At this question, create an `account_t` structure with:

* Two fields:
  * `double balance` gives the balance of the account,
  * `std::string note` is a note set by the banker.
* Two constructors:
  * An empty constructor that sets the balance to 0 and the note to an empty string,
  * A constructor that takes as parameter a balance used to initialize the field, and that also initializes the note to an empty string.

In the main function, without removing the code that you already have to test the map, creates an account like that:

```cpp
account_t a = 42;
```

Why this code compiles?

> **Tip:**
> Because the C++ compiler promotes the integer 42 into a double, and then into an `account_t` by using the second constructor.

### Question 2

We will now enrich the interface of `std::cout` to be able to print an account. For that, you have to implement this function:

```cpp
std::ostream& operator << (std::ostream& os, const account_t& account)
```

Technically, `std::cout` is an instance of `std::ostream`. When you call `std::cout << a;`, where `a` is an account, g++ generates a call to `operator << (cout, a)`. The operator `<<` has to print the balance followed by €, and if note is not null, it has to add the note in parenthesis. If your code is correct, the following code should output `42€ (best client ever)`:

```cpp
account_t a = 42;
a.note = "best client ever";
std::cout << a << std::endl;
```

### Question 3

In `main`, replace the declaration `treemap_t<std::string, double>` by `treemap_t<std::string, account_t>`. Why the code compiles and executes correctly?

> **Tip:**
> Because (i) when the compiler compiles `map["Tyrion"] = 2`, it promotes `2` into an `account_t` by using the second constructor of `account_t`, and (ii) when the compiler compiles `std::cout << pair.key << " => " << pair.value << std::endl`, it uses the overloaded operator `<<` to print `pair.value` (it's also the case in your `display` method).

### Question 4

Similarly, for the key, we now want to use a `lanister_t` object. Add a `lanister_t` structure with:

* A single field `std::string` that gives the name of the owner of the account,
* Two constructors, one empty, and one that initializes the name,
* A `bool operator < (const lanister_t& lanister) const` and a `bool operator == (const lanister_t& lanister) const` methods that compare `this->name` and `lanister.name`,

Now, add a `std::ostream& operator << (std::ostream& os, const lanister_t& lanister)` that prints the name of the account owner followed by " Lanister".

At this step, you should be able to replace the declaration `treemap_t<std::string, account_t>` by `treemap_t<lanister_t, account_t>`. Why the code is correct?

> **Tip:**
> Because `treemap_t` uses the overloaded operators `<` and `==` of `lanister_t`.

## The std::map container

Our binary search tree is what we call a **container** in C++. A container is a data structure that contains elements. The algorithm of our binary search tree is especially simple and inefficient because the tree may be unbalanced. This happens for example if we add the numbers `0, 1, 2, ...` in this order. In this case, the number will accumulate to the right, and we will end up with a tree that looks like a linked-list. To solve this problem, we can implement a red-black tree ([https://en.wikipedia.org/wiki/Red–black_tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree)).

### Question 1

Implementing the red-black tree algorithm is complex and out of the scope of this lab. Instead, we will simply reuse the red-black tree provided by the standard c++ library (`std::map`). Fortunately, our `treemap_t` has exactly the same interface. To use `std::map`, first, include `<map>`. Then, replace the declaration `treemap_t<lanister_t, account_t>` by `std::map<lanister_t, account_t>`.

🎉 **Congratulations! You are able to use the `std::map` container!**

> **Note:** You can find the whole interface of `std::map` [here](https://en.cppreference.com/w/cpp/container/map) if you want to use more advanced methods.

## The very comeback of the monsters (the std::vector container)

Apart from `std::map`, another container is especially useful: the `std::vector` container (see the documentation [here](https://en.cppreference.com/w/cpp/container/vector)). A vector is an extensible array, exactly as you implemented in lab 3 for the monsters.

### Question 1

In a file named `monster.cpp`:

* Create a `struct monster_t` with a name (a `std::string`) and a number of health points (a `int`),
* A `std::ostream& operator << (std::ostream& os, const monster_t& m)` able to print the monster,
* A main function that creates a monster with the name `Pikachu` and prints it.

### Question 2

Add a `std::vector<monster_t> army` variable in `main` (you have to include `<vector>`). By using the `push_back` method of `army`, which appends an element at the end of the vector, add 10 monsters named `Pikachu-i`. To build the string `Pikachu-i`, you can use `"Pikachu-" + std::to_string(i)`, where `i` is an integer.

Try to use a range-based loop to print your army (e.g., `for(auto& var: container) { ... }`).

---

🎉 **Congratulations! You are now able to use the vector container!**