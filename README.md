
Utilities
=========

As the name says, this library is a collection of utilities that may help from time to time. Nothing to fancy,
just things that could or should be in the standard-libary.

Current features
----------------

* `algorithm.hpp`: Several small algorithms for checking whether a value is in a container,
  to remove values from containers, ˙
* `carthesian_product.hpp`: Functionality to create a range that represents the carthesian product
  of an arbitrary number of other ranges.
* `core.hpp`: Tiniest utilities both for the library itself as for users. Currently only an alias for pointers.
* `enforce.hpp`: Functions that throw an exception if their argument is not what it should be.
* `integer_literals.hpp`: User-defined literals to create fixed-sized-integers, size\_t or ptrdiff\_t.
* `irange.hpp`: Basically pythons `range()` with a little bit more functinality.
* `random.hpp`: Facilities to ease the use of C++'s random-number-library in the 99% of trivial cases.
* `reference.hpp`: A reference that can be reassigned. Bassicaly an `observer_ptr` that cannot be null.
* `string.hpp`: Simple utilites for working with strings.
* `timer.hpp`: A nanosecond-precission-timer to ease the creation of benchmarks.

Current Tasks
-------------

* There are basically never as many unit-tests as one would like.
* More algorithms are always better.
* The same goes for more ranges.

License
-------

LGPLv3 or, at your option, any later version of the GPL.

As usual: If this doesn't fit your needs, contact me, and we might find a solution.

