# UUUU, aka Four U, aka For You

An [esolang] based on The Dark Knight Rises; [Plane Scene] quotes.
UUUU only allows string asignments, including concatenation, and conditional assignments.
But really just cross-compiles to a small subset of c++.

It's developed on and for Debian/Windows Subsystem for Linux (Debian).
And probably only works there, since it uses shell commands.
It might work on MacOS, but definitely won't work on windows.
To run, the compiler must have access to the g++ c++ compiler on the commandline.

### HelloWorld example:
Simple.uuuu
```
BANE
It would be extremely painful.

BANE
for you
```
```
$ banecoding Simple.uuuu
$ ./Simple
$ It would be extremely painful.
```


### More complicated HelloWorld that uses all current language features:
Complicated.uuuu
```
CIA
no friends

BANE
Big guy, for you

EXTREMELY
Big guy, for 

OURGUY
it would be EXTREMELY HOODEDMAN1

PAVEL refused HOODEDMAN1 offer in favour of CIA
BANE
OURGUY

PAVEL
for you
```

```
$ banecoding Complicated.uuuu
$ ./Complicated
$ Big guy, for you
$ ./Complicated Cia
$ Big guy, for Cia
```

Gets cross-compiled to:
```
#include <iostream>
int main (int argc, char* argv[]) {

    std::string CIA = "no friends";
    std::string BANE = "Big guy, for you";
    std::string EXTREMELY = "Big guy, for ";
    std::string OURGUY = EXTREMELY + std::string( (argc >= 2) ? std::string(argv[1]) : "no friends" );
    std::string PAVEL = ( std::string( (argc >= 2) ? std::string(argv[1]) : "no friends" ).compare(CIA) == 0 ) ? BANE : OURGUY;
    std::cout << PAVEL << "\n";

    return 0;
}
```

[esolang]: https://esolangs.org/wiki/Esoteric_programming_language
[Plane Scene]: https://www.youtube.com/watch?v=arty9MuqEg0
