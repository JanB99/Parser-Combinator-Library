# Parser-Combinator-Library

A small Parser Combinator library written in c++ that includes the basic building blocks of parsing string input text.
The library includes primitives like:
- Digit/letter parsing
- Custom character parsing
- Multiple digits/letters parsing (0 or more)
- Multiple custom character parsing (0 or more)
- Sequential parsing of a list of parsers 
- Parsing based on choice between parsers

In addition, the project includes a small arithmetic parsing library.
This is based on a simple grammar for addition and multiplication shown below:

Nr. | Grammar
----|-------------------------------
1   | expr = term + expr \| term
2   | term = factor * term \| factor
3   | factor = ( expr ) \| integer
