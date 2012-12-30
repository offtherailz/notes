# Chapter 16 - Structures, Unions, and Enumerations

Three new types:

+ Structures are collections of values (members), possibly of different
  types
+ Unions are similar to structures, except that its members share the same
  storage. So, a union can store one member at a time, but not all members
  simultaneously.
+ Enumerations are integer types whose values are named by the programmer.

## Structure variables

To begin, let's compare structures with arrays. All elements in an array
are of the same type. To select an array element, we specify its position
(as an integer subscript). But the elements (or members) of a structure
aren't required to be of the same type. Also, members of a structure have
names; to select a member, we give its name, not its position.

Structures are like records, and members similar to fields (in some other
languages).

### Declaring structure variables

You can declare one or more structs as follows.

    struct {
            int number;
            char name[NAME_LEN+1];
            int on_hand;
    } part1, part2;

**NB**: Each member has a semi-colon, and the declaration as a whole has
a semi-colon. Within a struct, the member names are scoped. So other
structs or other parts of the program could use `number` as the name for
something else without fear of conflict. (C says that each structure has
a separate 'name space' for its members.)

### Initializing structure variables

    struct {
            int number;
            char name[NAME_LEN+1];
            int on_hand;
    } part1 = {528, "Disk drive", 10}, part2 = {914, "Printer cable", 5};

The values in the initializer must appear in the same order as in the
declaration. Expressions used in the initializer must be constant, though
C99 allows for some non-constant expressions. You can omit values; anything
not initialized is set to 0 automatically.

### C99 Designated initializers

Just as with arrays, in C99 you can specify which elements you want to
initialize out of a larger array (`{[1] = 14, [8] = 9}`), you can designate
specific items you want to initialize in a struct. This makes
initializations easier to read, easier to check for correctness and you can
specify member values in any order:

    {.on_hand = 2, .number = 1, .name = "Disk drive"}

You can also mix initializations (in both arrays and structs), giving some
items designators and leaving some without them. This seems like a very bad
idea to me. In any case, for a struct, if you leave a designator off, the
compiler assumes it appears after the previous designator in the struct.

### Operations on structure

To select one of the structures members, you use the name and dot-notation:

    part1.number

The members of a struct are lvalues, so they can appear in assignments as
well:

    part1.on_hand++;
    part2.number = 258;

In addition to accessing individual member values, you can assign an entire
structure to another:

    part2 = part1

Unlike arrays, this works. All the member values of `part1` are copied into
`part2` -- even if they are arrays.

Note, however, that the two structures must be of compatible types. You
can't assign a structure of one shape to another that is completely
different.

## Structure types

So far we've seen how to declare structure _variables_, but what we will
want more often is the ability to create structure _types_. That is, we
don't want to be forced to declare all structure variables together and up
front, nor do we want to space out declarations of the same structure type
over and over full spelled out. It would repeat tons of information, add
the likelihood of errors, make it harder to change the program and, worst
of all, if you declare `part1` and `part2` separately, then _they are no
longer considered to be of compatible types_, even if the struct
declarations look identical.

To avoid this, we want to define a name that represents a structure _type_.
There are two ways to do this: declare a structure tag or use `typedef` to
define a type name.

### Declaring a structure tag

    struct part {
            int number;
            char name[NAME_LEN+1];
            int on_hand;
    };
    ...
    struct part part1, part2;
    ...
    struct part part3 = {528, "Disk drive", 14};
    struct part part4;
    part4 = part3;

### Defining a structure type

    typedef struct {
            int number;
            char name[NAME_LEN+1];
            int on_hand;
    } Part;
    ...
    Part part1, part2;

You can usually use either method to create a structure type, but the
structure tag method is required for linked lists. K will mostly use that
style rather than `typedef`.

### Structures as arguments and return values

Structures can be used as arguments or return values for functions.

    void print_part(struct part p)
    {
            printf("Part number: %d\n", p.number);
            printf("Part name: %s\n", p.name);
            printf("Quantity on hand: %d\n", p.on_hand);
    }
    ...
    print_part(part1);

    struct part build_part(int number, const char*name, int on_hand)
    {
            struct part p;

            p.number = number;
            strcopy(p.name, name);
            p.on_hand = on_hand;

            return p;
    }

    part1 = build_part(528, "Disk drive", 10);

Passing a structure to a function or returning one from a function both
make a copy of the whole structure. This requires work and memory space. So
it can be better to use a pointer, rather than passing the whole structure
back or forth. In addition, sometimes the struct you want to work with must
be unique (e.g. FILE structures from `<stdio.h>` used for reading and
writing with files).

### Compount literals

Just as arrays in C99 can use compound literals to create unnamed arrays,
usually to pass the item to a function, structures can do the same thing in
C99.

    print_part((struct part) {528, "Disk drive", 14});

A compound literal usually consists of a type within parentheses and then
a set of values in braces. The typename can be `struct` followed by
a structure tag or a `typedef` name. You can also use designators with
a compound literal, if you like.

    print_part((struct part) {.number = 528,
                              .name = "Disk drive",
                              .on_hand = 14});

Finally, a compound literal may leave some members unspecified. In that
case, they are initialized to 0 automatically.

## Nested arrays and structures

You can combine arrays and structures without restriction. Arrays can have
structs as elements, and structs can have arrays as members. In addition,
structs can have other structs as members.

### Nested structures

    struct person_name {
            char first[FIRST_NAME_LEN+1];
            char middle_initial;
            char last[LAST_NAME_LEN+1];
    };

    struct student {
            struct person_name name;
            int id, age;
            char sex;
    } student1, student2;


Getting at member values from nested structs requires multiple applications
of the dot operator:

    strcpy(student1.name.first, "Fred");

Advantages of nesting structs in this way:

+ The inner struct is a unit of data. We can pass it as a parameter, rather
  than passing each member value separately.

        display_name(student1.name);

+ Copying the data takes one assignment instead of three.

        struct person_name new_name;
        ...
        student1.name = new_name;

### Arrays of structures

A very common combination of arrays and structures is an array whose
elements are structures. Such an array can work like a simple database.

    struct part inventory[100]; /* An array to store 100 part structs */

You use subscripting to get at individual structs, e.g. `inventory[i]`. To
get at a member inside a specific part, we subscript and then use dot
notation: `inventory[i].number`.

### Initializing an array of structures

Initializing an array of structs is similar to initializing
a multi-dimensional array. Each structure has its own initializer,
surrounded by braces. The outermost array initializer wraps all of these
with its own braces.

    struct dialing_code {
            char *country;
            int code;
    }

    const struct dialing_code country_codes[] =
        {{"Argentina", 54}, {"Brazil", 55}, {"China", 86}, {"Congo", 243},
         {"Ethiopia", 251}, ...}

The inner braces around each struct are optional. Put them there.

C99 designated initializers can have multiple designators at once, in order
to initialize a nested variable fully.

    struct part_inventory[100] =
        {[0].number = 528, [0].on_hand = 10, [0].name[0] = '\0'};

## Unions

Unions are similar to structures. They contain one or more members,
possibly of different types. But the compiler stores unions differently
from structures. The compiler allocates only enough space for the largest
of the members, which overlay each other in this space. Assigning a new
value to one member changes the values of other members at the same times.

    union {
            int i;
            double d;
    } u;

For a structure, the members are stored at different addresses in memory.
For a union, the members are stored at the same address -- and the total
allocation makes sure that the largest member will fit.

You can then assign to `u.i` or `u.d`, as with a structure. However,
a union can hold _only one value at a time_ from among its members. So if
you set `u.i`, then whatever value was in `u.d` becomes meaningless. Again,
a union allows you to store _only one_ of its potential members at a time.

In other ways, unions are very like structures. You can declare union tags
or union types with `typedef`. You can copy unions with `=`. You can pass
them to functions or return unions from functions.

Unions can be initialized in a manner similar to structures, but only the
first member can be given an initial value (prior to C99 designators).

    union {
            int i;
            double d;
    } u = {0}; /* sets u.i to 0 */

The braces are required and the expression in the braces must be
a constant. (C99 changes this.)

You can use a designated initializer in C99 to set values other than the
first member:

    union {
            int i;
            double d;
    } u {.d = 10.0}; /* sets u.d to 10.0 */

No matter how you give a union an initial value, of course, only one value
can be initialized.

### Using unions to save space

Unions can be useful if you want to save space that structures would atake
up. King offers a somewhat complex, but helpful example. Imagine you have
a catalog for a store that carries books, mugs and shirts. Each type of
item has a stock number and a price. But then the types diverge:

+ Books have title, author and number of pages
+ Shirts have design, colors available and sizes available
+ Mugs have design

If you build a structure to store one of these varied items at a time, it
will waste space (since a mug, for example, needs only design, not title,
author, number of pages, colors available or sizes available).

Instead of doing that, you could create a union made up of three structs.
Only one struct will be used at a time, and the total memory space will be
less.

    struct catalog_item {
            int stock_number;
            double price;
            int item_type;
            union {
                    struct {
                            char title[TITLE_LEN+1];
                            char author[AUTHOR_LEN+1];
                            int num_pages;
                    } book;
                    struct {
                            char design[DESIGN_LEN+1];
                    } mug;
                    struct {
                            char design[DESIGN_LEN+1];
                            int colors;
                            int sizes;
                    } shirt;
            } item;
    };

This will create a fair amount of nesting for individual `catalog_item`
structs. For example, assume `c` is a book:

    printf("%s", c.item.book.title)

### Using unions to build mixed data structures

Unions are also useful to create data structures that contain a mixture of
different types of data. For example, an array where the elements are ints
or doubles. An array as a whole can only store one type of data, but
a union fixes that problem. You store only items of that union type, but
each one of those may store an int or a double.

    typedef union {
            int i;
            double d;
    } Number;

    Number number_array[100];

    number_array[0].i = 5;
    number_array[0].d = 8.395;

### Adding a "tag field" to a union

This, however, shows a big problem with unions. There is no way to tell
which member of the union was last changed and therefore contains a useful
value. How do you know if you want to access the `i` or the `d` member of
an item in the `number_array`?

One answer is to embed the union in a struct and add a "tag field" or
"discriminant" member for the outer struct. The purpose of the tag field is
to tell functions which member to access.

    #define INT_KIND = 0
    #define DOUBLE_KIND = 1

    typedef struct {
            int kind;
            union {
                    int i;
                    double d;
            } u;
    } Number;

    n.kind = INT_KIND;
    n.u.i = 82;

    void print_number(Number n)
    {
            if (n.kind == INT_KIND)
                    printf("%d", n.u.i);
            else
                    printf("%g", n.u.d);
    }

Of course, this means that everytime the program assigns anything to
a member of the union, the tag field must be changed too.

## Enumerations

We often need variables that only have a small set of meaningful values. As
an example, a boolean can only have two possible values: "true" and
"false". A variable that stores a card's suit can only have four values:
"clubs", "diamonds", "hearts" and "spades".

One thought is to just assign values using small integers:

    int hearts;
    ...
    hearts = 3;

But this isn't very clear: you have no way to know how many values there
are, nor what 3 has to do with anything.

Alternatively, you could use macros:

    #define SUIT int
    #define CLUBS 0
    #define DIAMONDS 1
    #define HEARTS 2
    #define SPADES 3
    ...
    SUIT s;
    s = HEARTS;

This is better, but still has problems. It's not obvious that the macros
represent values of a single type. If there are more than a few macros, it
becomes a lot of work to set them up this way. Finally, the preprocessor
removes the macros, so they aren't visible during debugging.

C provides a specific type for this kind of situation -- enumerated types.

    enum { CLUBS, DIAMONDS, HEARTS, SPADES } s1, s2;

### Enumeration tags and tag names

It's also possible to give enumerations names, and thi sis useful in the
same way s it is for structures and unions. You can declare a tag or use
`typedef` to create a genuine tag name.

    # Tag name
    enum suit { CLUBS, DIAMONDS, HEARTS, SPADES };
    enum suit s1, s2;
    # Typedef
    typedef enum { CLUBS, DIAMONDS, HEARTS, SPADES } Suit;
    Suit s1, s2;

This is an excellent way to create a boolean type for C89:

    typedef enum { FALSE, TRUE } Bool;

### Enumerations as integers

Underneath the syntax, C treats enumeration variables and constants as
integers. By default, the compiler assigns the integers 0, 1, 2,... to the
constants in a particular enumeration. In the case of the booleans, for
example, FALSE is 0 and TRUE is 1.

It is possible  specify different values for enumeration constants.

    enum suit { CLUBS = 1, DIAMONDS = 2, HEARTS = 3, DIAMONDS = 4 };

The values can be arbitrary integers, in any order

    enum dept { RESEARCH = 20, PRODUCTION = 10, SALES = 25 };

It's also legal for two or more enumeration constants to have the same
value.

When an enumeration constant is not given a specific value, it is
automatically given the value one greater than the previous constant.

    enum Colors { BLACK, LT_GRAY = 7, DK_GRAY, WHITE = 15 };
    /* BLACK = 0, LT_GRAY = 7, DK_GRAY = 8, WHITE = 15 */

The values for enumerations are just integers, so C allows you to mix them
with ordinary ints.

    int i;
    enum suit { CLUBS = 1, DIAMONDS = 2, HEARTS = 3, DIAMONDS = 4 } s;
    i = CLUBS;      /* i = 1 */
    s = 1;          /* s = 1 (CLUBS) */
    s++;            /* s = 2 (DIAMONDS) */
    i = s + 2;      /* i = 4 */

### Using enumerations to declare "tag fields"

Enumerations are good for solving the problem of determining which member
of a union was the last to be assigned a value.

    typedef struct {
            enum { INT_KIND, DOUBLE_KIND } kind;
            union {
                    int i;
                    double d;
            } u;
    } Number;

