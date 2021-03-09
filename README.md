# perfect-numbers

A program that lists the perfect numbers in the ranges 2^8, 2^16, 2^32, or 2^64.

## How it works

All of the known perfect numbers are even. An even perfect number is the product `2^(p - 1) * (2^p - 1)` where
`(2^p - 1)` is a Mersenne prime. There are very few values of `p` such that the resulting number is less than 2^64.
In fact the only values worth checking are 2, 3, 5, 7, 13, 17, 19, and 31.

A `struct perfect_generator` will act as an iterator through these values and generate the corresponding perfect
number. Each function `perfect_nextN` (where `N` is the number of bits) will allow iteration to continue until the
next perfect number would be outside of the range of `uintN_t`.

## Building

```sh
$ make
```
