set(HPP Common.hpp
		NeuralConnection.hpp
		NeuronInput.hpp
		SpikingNeuron.hpp)

set(CPP main.cpp
		NeuralConnection.cpp
		NeuronInput.cpp
		SpikingNeuron.cpp)

set(NAME "snn")

add_executable(${NAME} ${HPP} ${CPP})
target_link_libraries(${NAME} nmemory)