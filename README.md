# cppcourse-brunel

Method :

1) Put the following files in the same folder (main_folder) :

main.cpp
network.cpp
network.h
neuron.cpp
neuron.h
neuron_unittest.cpp
Doxyfile.in
CMakeLists.txt
googletest
(googletest is a folder / make sure it is named googletest AND NOT gtest)

2) With the terminal, place yourself in the folder (main_folder) and enter the following commands :

cmake .

(wait until it is finnished)

make

make doc (for doxyfile)

3) Now you can run ./neuron_unittest to test the googletests, or 
./Neurons to run the simulation with 12'500 neurons.
