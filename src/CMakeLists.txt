set(HPP Common.hpp
		Game.hpp
		NeuralConnection.hpp
		NeuronInput.hpp
		SpikingNeuron.hpp
		TestEnvironment.hpp
		CarTest.hpp)

set(CPP main.cpp
		Game.cpp
		NeuralConnection.cpp
		NeuronInput.cpp
		SpikingNeuron.cpp)

set(NAME "snn")

add_executable(${NAME} ${HPP} ${CPP})
target_link_libraries(${NAME} nmemory)
target_link_libraries(${NAME} Box2D)