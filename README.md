# NewsClustering
Práctica 2 del Curso de Experto en Arquitectura y Desarrollo de Software, sobre TDD y refactoring

## Requisitos
- CMake 3.5.1
- compilador C++11

El resto de dependencias del proyecto son gestionadas automaticamente a traves de cmake.

## Compilar
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

## Ejecutar los tests
    $ bin/NewsClusteringTest

## Procesar los items almacenados en el directorio "data"
    $ bin/NewsClustering ../data
