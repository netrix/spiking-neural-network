set(HPP DebugDrawOpenGL.hpp
		PhysicsCar.hpp
		PhysicsTire.hpp
		PhysicsFixtureUserData.hpp
		Common.hpp
		Sprite.hpp
		Framework.hpp
		NeuralConnection.hpp
		NeuronInput.hpp
		SpikingNeuron.hpp
		TestEnvironment.hpp)

set(CPP main.cpp
		DebugDrawOpenGL.cpp
		PhysicsCar.cpp
		PhysicsTire.cpp
		Sprite.cpp
		Framework.cpp
		NeuralConnection.cpp
		NeuronInput.cpp
		SpikingNeuron.cpp)

set(NAME "snn")

add_executable(${NAME} ${HPP} ${CPP})
target_link_libraries(${NAME} nmemory)
target_link_libraries(${NAME} Box2D)