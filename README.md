My playspace of c++ exercises to learn the language.

To run an exercise: `g++ learn.cpp -o learn.out -std=c++17`
Can also compile multiple source files together so they get linked by the
compiler: `g++ learn.cpp learn2.cpp -o learn.out -std=c++17`

I've added the alias `cpplay learn` to compile `learn.cpp` and run the object
file. I've defined it as a function in my `.zshrc`:
```
cpplay() {
  g++ "$1.cpp" -o "$1.out" -std=c++17;
  "./$1.out"
}
```