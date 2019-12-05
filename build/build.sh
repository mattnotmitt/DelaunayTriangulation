mkdir -p data
g++ -o DT -I ../external/ ../src/*.cpp ../tests/*.cpp -O3 -fopenmp -march=native
