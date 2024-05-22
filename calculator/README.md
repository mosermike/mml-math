# calculator

This c++ programme does simple calculations and matrix calculations such as computing the determinant or the inverse.

## Install

The programm can be installed by simply executing
'''
make 
'''

Note that the two libraries mml and mml-math are needed and can be installed her
- libmml : [github](https://github.com/mosermike/mml), [gitlab](https://gitlab.moser.mywire.org/moser/mml)
- libmml-math : [github](https://github.com/mosermike/mml-math), [gitlab](https://gitlab.moser.mywire.org/moser/mml-math)
If you want to install the executing script somewhere, execute
'''
make install DST=[path to installation directory]
'''

## Usage

The code itself can be executed as
'''
./calc.x -c 1+1
'''
and it prints the result. Note, that when you are using brackets, write the equation as "(1+1)" with the quote signs.

## Constants
TODO

## Uninstall

To uninstall any created files, simply execute
'''
make uninstall DST=[path to installation directory].
'''


## Matrix Calculations
TODO

## Project status
Ongoing (beta version)
