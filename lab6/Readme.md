# The Lanister bank, part I

**Goal:** The objective of this exercise is to familiarize you with templates.

In this exercise, you will design a small bank, focusing on the problem of quickly searching for a customer by their name. This quick search problem is quite general: any web application, like Facebook, must be able to retrieve an account based on a login ID.

At a high level, the problem of storing a bank’s customers is quite similar to the problem of storing monsters in a monster army. Since the number of a bank’s customers is unknown and unbounded, you have seen so far that customers can be stored in a dynamic array or in a linked list. Neither of these two structures is suitable:

* A dynamic array is unsuitable because a bank has a large (unbounded) number of customers. If you used a dynamic array to store our customers, you would risk having to resize (and thus copy) an enormous array when adding a new customer, which would severely impact performance.
* A linked list is also unsuitable because this structure is particularly inefficient for searching. Indeed, with a linked list, the only way to reach the n<sup>th</sup> element in the list is to exhaustively traverse the previous n-1 nodes. If the linked list has N nodes, and if searches are evenly distributed across all customers, you would therefore need to traverse, on average, N/2 nodes to find a customer. If N is very large, this complexity seriously degrades performance.

Since none of the data structures studied so far are suitable, we introduce binary search trees in this lab. This data structure has the advantage of handling an unbounded number of elements while being efficient for adding or searching for elements. The algorithm you will study in this exercise is (relatively) simple to implement but can lead to inefficiency issues that we present at the end of the exercise. To address these inefficiencies, there are red-black trees or 2-3-4 trees, and we encourage curious students and algorithm enthusiasts to explore them.

In order to design a generic code, you will implement the binary search tree as a map. A map is a data structure that associates keys to values. For the bank, the key is a string that gives the name of a customer, and the value is the balance of the account. You will also implement the binary search tree in a generic way, which means that the data structure itself will not be tailored for the bank use case, but designed to associate any type of keys to any type of values. For that, you will rely on templates.

## Basic structures

In this exercise, we simply start by defining two central structures:

* `treemap_t` represents a binary search tree. It associates keys to values.
* `pair_t` represents an association between a key and a value.

### Question 1

In a file `treemap.h`, define a `treemap_t` structure. A treemap is defined as a template structure with two parameters: `K` gives the type of a key, and `V` gives the type of a value. For the moment, the `treemap_t` structure is empty (no fields, no constructors, not methods). Note that any element defined inside `treemap_t` is parameterized by `K` and `V`.

### Question 2

We will now define the `pair_t` structure. A pair associates a key with the template type `K` to a value with the template type `V`. We will define the `pair_t` structure as an **nested class** inside `treemap_t`. Thanks to that, `pair_t` is also parameterized by `K` and `V` without having to repeat `template <class K, class V>`. Your code will thus look like that:

```cpp
template <class K, class V>
struct treemap_t {
  struct pair_t {
    ...
  };
};
```

`pair_t` has two fields: `key` with the type `K` and `value` with the type `V`.

In a file `main.cpp`, add a `main` function. Inside the `main` function, defines a variable `pair` that associates a `std::string` to a `double`, and initialize it to `Tyrion` for the key and `2.0` for the value. If your code is correct, the following code should output `Tyrion: 2€`:

```cpp
std::cout << pair.key << ": " << pair.value << "€" << std::endl;
```

## The tree

Now that the basic structure of the code is correct, we can implement the binary search tree. A binary tree consists of nodes, and each node has two children: a left child and a right child.

For a binary search tree, each node is labeled with a value defined on a totally ordered set. In our case, this is the name of the owner of the bank account, and the order used is the lexicographical order based on the account names. The principle of a binary search tree is that the labels under the left child (included) of a node are all strictly smaller than the node’s label, and those under the right child (included) are all stictly larger.

The figure below illustrates the principle. If we take, for example, the node labeled with Jaime’s account, we can see that the nodes to the left are smaller and those to the right are larger.

```text
        [Tyrion]
       /    \
 [Jaime]    [Tywin]
  /   \           \
[Cersei] [Kevan]    [Willem]
 /             \
[Alton]          [Lancel]
               \
              [Martyn]
```

### Question 1

To represent a node in the tree, we need a `node_t` data structure. This structure inherits from `pair_t`, and adds three other fields:

* `node_t* parent`: `nullptr` for the root of the tree, the parent in the tree otherwise,
* `node_t* left`: left child,
* `node_t* right`: right child.

Implement `node_t` as an nested class inside `treemap_t`. Add a constructor to `node_t`. The constructor takes a parent as parameter and initializes adequately the `parent` field. The constructor also initializes the children to `nullptr`.

In `treemap_t`, add a `node_t* root` field initialized to `nullptr` with a constructor of `treemap_t`. `root` gives the root of the binary search tree.

### Question 2

You will now implement the central method of `treemap_t`:

```cpp
node_t* lookup(node_t** pcur, node_t* parent, const K* key, bool create)
```

The `lookup` method is used to add a new pair (when `create` is true) or to retrieve an existing pair (when `create` is false or true).

The `lookup` method explores the tree recursively. For that, it takes three other parameters:

* `pcur` is a pointer to a `node_t*`. `*pcur` is the current node explored by `lookup` (see below),
* `parent` gives the parent of `*pcur` (`nullptr` when we explore the root node),
* `key` is the key that we are looking for in the tree.

The argument `pcur` is subtle: it is a pointer to a memory location that contains itself a pointer to the node currently explored by `lookup`. Initially, `pcur` is a pointer to the `root` field of a `treemap_t`, which means that `*pcur` points to the root node. If the root node does not yet exist, we can create it in `lookup` with `*pcur = new node_t { parent }`. Then, while we are traversing the tree, `pcur` points to the left or right field of the parent of the current node. For example, if we want to insert "Darth Vader", we will end up with `pcur` that points to the right field inside the node "Cersei" (see the tree above). To create the node "Darth Vader", we have to execute `*pcur = new node_t { parent }`, which will allocate the memory for "Darth Vader", and set the right field of "Cersei" to this node. As a result, you can observe that we execute the exact same operation to allocate a root node or an intermediate node: we have to execute `*pcur = new node_t { parent }` in both cases. In the lookup code, you should thus not distinguish the case where we allocate the root node or an intermediate node. If you click on need help, you will see a graphical representation of the two cases.

> **Tip:**
> ```text
> # Initial state
>      Type          Memory content    Memory address
>                     ------------     
> treemap_t::root     | nullptr  |        0x10000
>                     ------------
> 
> # Lookup to create Tyrion
> - pcur: 0x1000 (pointer to the root field in the treemap_t)
> - parent: nullptr
> 
> => to create Tyrion: *pcur = new node_t { parent }
> 
> # State after
>      Type          Memory content    Memory address
>                     ------------     
> treemap_t::root     |  0x1100  |        0x1000
>                     ------------
> 
>                     ------------
> node_t::parent      |  0x1000  |        0x1100
> node_t::left        | nullptr  |        0x1108
> node_t::right       | nullptr  |        0x1110
> node_t::key         | "Tyrion" |        0x1118
>                     ------------
> 
> # Lookup to create Jaime
> - pcur: 0x1000 (pointer to the root field in the treemap_t)
> - parent: nullptr
> 
> => Since *pcur not null and Jaime < Tyrion, execute pcur = &(*pcur)->left, which means that:
> 
> - pcur:   0x1108  (pointer to the left field in the node_t Tyrion)
> - parent: 0x1000  (pointer to node of Tyrion)
> 
> => to create Jaime: *pcur = new node_t { parent }
> 
> # State after
>      Type          Memory content    Memory address
>                     ------------     
> treemap_t::root     |  0x1100  |        0x1000
>                     ------------
> 
>                     ------------
> node_t::parent      |  0x1000  |        0x1100
> node_t::left        |  0x1200  |        0x1108
> node_t::right       | nullptr  |        0x1110
> node_t::key         | "Tyrion" |        0x1118
>                     ------------
> 
>                     ------------
> node_t::parent      |  0x1100  |        0x1200
> node_t::left        | nullptr  |        0x1208
> node_t::right       | nullptr  |        0x1210
> node_t::key         | "Jaime"  |        0x1218
>                     ------------
> ```

Implement the `lookup` method. You can test it with the following code:

```cpp
treemap_t<std::string, double> map;
std::string name;

name = "Tyrion";
map.lookup(&map.root, nullptr, &name, true);
name = "Jaime";
map.lookup(&map.root, nullptr, &name, true);
name = "Cersei";
map.lookup(&map.root, nullptr, &name, true);
```

> **Tip:**
> To illustrate how `lookup` works, we suppose that we are trying to create an account for a user "Darth Vader" in the tree given above. Initially, we call thus `lookup` with the following parameters:
> * `pcur` is a pointer to `root` inside `treemap_t`,
> * `parent` is equal to `nullptr` since we are starting from the root of the tree,
> * `key` is a pointer to the `std::string` "Darth Vader",
> * `create` is true since we want to create the account if it does not yet exist.
> 
> At this step, `*pcur` is not null: it points to root. We can create a local variable `node_t* cur = *pcur`. `cur` is pointer to `Tyrion`: the node that we are exploring in `lookup`. `*key` and `cur->key` are different since "Darth Vader" and "Tyrion" are different, so we have to explore a child. Note that if we had called `lookup` with "Tyrion", we would have returned `cur` at this step since we would have found the node that represents "Tyrion".
> 
> To know which child we have to explore, we have to compare `*key` to `cur->key` with `*key < cur->key`. "Darth Vader" is lower than "Tyrion" (D is before T in the alphabet). We have thus to explore the left node of "Tyrion". For that, we simply have to call `lookup(&cur->left, cur, key, create)`. In this call, `pcur` is a pointer to the left node of "Tyrion", which means that `*pcur` is a pointer to "Jaime". `parent` is a pointer to the node "Tyrion".
> 
> Similarly, `lookup` will traverse the tree step by step:
> * When `lookup` explores "Jaime" (i.e., `*pcur` points to "Jaime"), `lookup` goes to the left by calling `lookup(&cur->left, cur, key, create)`,
> * When `lookup` explores "Cersei" (i.e., `*pcur` points to "Cersei"), `lookup` goes to the right by calling `lookup(&cur->right, cur, key, create)`.
> 
> At this stage, `pcur` is a pointer the right field inside "Cersei". `*pcur` is thus null: "Cersei" does not have yet a right child. Here, we have two possibilities:
> * If `create` is false, the function returns `nullptr` since the key does not exist.
> * Otherwise, we have to create a new node. For that, calling `*pcur = new node_t { parent }` does the job: this expression will set the right node of "Cersei" to the new node. We can then set the key of the node to "Darth Vader" with `(*pcur)->key = *key`. After, the code continues normally: it stores `*pcur` in `cur`, which means that `cur` is a pointer to the newly allocated "Darth Vader". Since now `*key == cur->key`, the code returns `cur`.

🎉 **Implementing this lookup method is quite complex and you made it, congratulations!**

### Question 3

The `lookup` method can create or retrieve a node, but using it is not yet very intuitive. We will hide this complexity behind two new methods of `treemap_t`:

* `void set_at(const K key, const V value)`: this method creates the key `key` in the map if it does not yet exist, and updates its value of it already exists.
* `V at(const K key)`: this method retrieves the value associated to `key`. If `key` does not exist, the method prints a message and quit the process with `exit`.

If your code is correct, the following code should output `48`:

```cpp
map.set_at("Tyrion", 2);
map.set_at("Jaime", 15);
map.set_at("Cersei", 63);
map.set_at("Tywin", 75);
map.set_at("Kevan", 48);
map.set_at("Lancel", 70);
map.set_at("Alton", 54);
map.set_at("Martyn", 32);
map.set_at("Willem", 6);

std::cout << map.at("Kevan") << std::endl;
```

### Question 4

Add now a method `display()` in `treemap_t` to print a complete tree. The `display()` method should output the tree by indenting the nodes like that:

```text
      (Alton, 54)
    (Cersei, 63)
  (Jaime, 15)
    (Kevan, 48)
      (Lancel, 70)
        (Martyn, 32)
(Tyrion, 2)
  (Tywin, 75)
    (Willem, 6)
```

> **Tip:**
> You can implement `display()` recursively by using an intermediate method `void display(node_t* cur, std::string prefix)`. `cur` enumerates all the nodes, and prefix is the prefix that you want to print before the node (a string with spaces).
> 
> *To display `cur`, you have to display recursively `cur->left`, then to print `cur`, and then to display recursively `cur->right`.*

## Iterator

### Question 1

We will now enrich our bank with a new feature, which will allow the user to enumerate the nodes in the order of the tree (i.e., by starting by the lowest node to the left, i.e., "Alton" in our case). For that, we will implement what we call an **iterator**. An iterator is data structure that points to a current node, and that mainly offers a `void next()` method able to move to the next node. With our tree, the iterator initially points to "Alton", and after a call the `next()`, it points to "Cersei". When the iterator points to the last node (i.e., "Willem" in our case), a call to `next()` makes the iterator points to `nullptr`, which terminates the iteration.

We will implement the iterator with a data structure called `iterator_t` defined as a nested class in `treemap_t`. `iterator_t` has a single field: `node_t* cur`, which gives the current node of the iterator. Its constructor takes as argument a root node. The constructor initializes `cur` to the first node ("Alton" in our case). It also has a `void next()` method that moves `cur` to the next node.

With this interface, we can enumerate the nodes of the tree with this code:

```cpp
for(treemap_t<std::string, double>::iterator_t it = treemap_t<std::string, double>::iterator_t { map.root };
    it.cur != nullptr;
    it.next()) {
  std::cout << it.cur->key << " => " << it.cur->value << std::endl;
}
```

In this code, the first line of the `for` creates and initializes the iterator. The second line means that the loop ends when `it.cur` is null. The third line means that, at each step of the loop, we call `it.next()` to move to the next node. In the body of the loop, we simply print the node. The code should thus output:

```text
Alton => 54
Cersei => 63
Jaime => 15
Kevan => 48
Lancel => 70
Martyn => 32
Tyrion => 2
Tywin => 75
Willem => 6
```

Implement the `iterator_t` structure.

> **Tip:**
> The constructor has to find the lowest node to the left of the tree. The `next` method is more complex. To find the next node, we have two possibilities:
> * If `cur` has a right node (for example, when `cur` points to "Jaime"), We have to find the lowest node to the left, by starting from `cur->right`. For example, if we start from `Jaime`, `cur->right` points to "Kevan". The lowest node to the left of "Kevan" is "Kevan" itself since "Kevan" does not have a left child.
> * If `cur` does not have a right node, we have to go up. For example, if `cur` points to "Martyn", the next node is "Tyrion". For that, we have to go up step by step in a loop. For each `cur`, if `cur` has a parent, and if `cur` is the right child of its parent (i.e., if `cur == cur->parent->right`), we have to continue to go up by setting `cur` to `cur->parent`. For example, if `cur` points to "Martyn", since "Martyn" is the right child of "Lancel", we go up and thus restart with `cur` that points to "Lancel". "Lancel" is itself the right child of "Kevan", so, we continue to go up, up to "Jaime", since "Jaime" is not the right child of "Tyrion". After this loop, we simply have to set `cur` to the parent of `cur` ("Tyrion" in our case).

### Question 2

In order to ease the use of our data structure, add a `iterator_t begin()` to `treemap_t`. This method returns an iterator to the map. Thanks to this method, we can simplify the loop that iterates over the pairs into:

```cpp
for(treemap_t<std::string, double>::iterator_t it = map.begin();
    it.cur != nullptr;
    it.next()) {
  std::cout << it.cur->key << " => " << it.cur->value << std::endl;
}
```

### Question 3

A template type can quickly become cumbersome. For example, for the user, writing the type `treemap_t<std::string, double>::iterator_t` is not very convenient. For this reason, the C++ language offers a generic type called `auto`. The type of an `auto` variable is deduced from the expression that initializes the variable. Thanks to the `auto` keyword, we can thus simplify the loop that enumerates the elements of our bank with:

```cpp
for(auto it = map.begin(); it.cur != nullptr; it.next()) {
  std::cout << it.cur->key << " => " << it.cur->value << std::endl;
}