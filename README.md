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

make

make doc (for doxyfile)

3) Now you can run ./neuron_unittest to test the googletests, or 
./Neurons to run the simulation with 12'500 neurons (expected time : 48s). 
I advise you to put '1' as starting step, '10000' as stopping step and '0' as external current.

4) The Spikes-plots 1 & 2 correspond to brunels plots. The Spike-plot2 is the same as the first but with more neurons taken into account. This allows a better reading of the plots.
