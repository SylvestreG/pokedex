POKEDEX
===

[![Build Status](https://travis-ci.org/SylvestreG/pokedex.png)](https://travis-ci.org/SylvestreG/pokedex)

## Overview

Pokedex is a cli for getting information about pokemons

### Building

```bash
$ git clone https://github.com/SylvestreG/pokedex.git
$ cd pokedex && mkdir build && cd build
$ cmake .. && make
```

## How to use

launch pikachu with some arguments

### Usage
```
Usage:
  pokedex [-?|-h|--help] [-h|--help] [-n|--name] [-i|--id]

Options, arguments:
  -?, -h, --help

  Display usage information.

  -h, --help

  help

  -n, --name <aaa,bbb,ccc>

  list of pokemon names

  -i, --id <x,y,z>

  list of pokemon ids
```

### Example

Here is an example to get info about pikachu :
```
[syl@pony build]$ ./pokedex -n pikachu
Number: 25
Name:   Pikachu
Types:  Electric
Height: 1'04"
Weight: 13.2 lbs.
```

