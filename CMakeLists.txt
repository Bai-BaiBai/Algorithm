cmake_minimum_required(VERSION 3.14)
project(Algorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(Algorithm main.cpp main.cpp SortTestHelper.h SelectionSort.h InsertionSort.h BubbleSort.h ShellSort.h MergeSort.h QuickSort.h)