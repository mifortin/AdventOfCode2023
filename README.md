#  My Solutions to Advent of Code 2023

This year's theme is pointers / minimizing the use of standard libraries.  How far will I manage to go with this hair-brained scheme?!

Each day adds new goodies to my "unofficial advent of code standard library".  Or whatever it is.

## Main Header
Well....  if you want to use this poorly thought out API, include "Day01.hpp" and compile each DayXX.cpp.  Good luck!

## Strings
Strings are represented as two pointers.  One for the start, one for the end.  This actually saved my bacon on day 1 as it became trivial to do string compare forward and backward.

## Parsing
All strings for the moment are views inside of the original data; which is a string literal in the code.  I'm lazy.  Not sorry.

This means when I parse, I copy a string (which is just a view), and then the parse functions increment the appropriate pointers.  Useful addition of day 2.  I also started using structs.  A good idea.  Classes with members - that's too much abstraction for the challenge!

## Bitsets
The functions take in a char array.  This allows the array to exist on the stack and be default inited to 0.  Either set or test.  Brought to you by Day 4's puzzle

## Arrays
Caved, now am using templates.  Arrays have a maximum fixed size.  O(n) everything!  Invoke ACArray.

Most important result of day 5 is the range operations + range array.  These allow adding a range while maintaining sorting order - and merges ranges as need be.  This allows day 5 to run spectacularly fast.  See ACRange and ACRangeArray.

If the type in the array has a "Consume" to parse the value, then you can consume the array and it will read it in easily.

There's Quicksort - be sure that less then and greater than are both implemented.
