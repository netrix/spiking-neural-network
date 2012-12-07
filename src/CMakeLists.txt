set(HPP DebugDrawOpenGL.hpp
		PhysicsCar.hpp
		PhysicsContacts.hpp
		PhysicsTire.hpp
		PhysicsFixtureUserData.hpp
		Exceptions.hpp
		Common.hpp
		Sprite.hpp
		Framework.hpp
		NeuralConnection.hpp
		NeuronInput.hpp
		PlotOpenGL.hpp
		SpikingNeuron.hpp
		TestEnvironment.hpp
		Track.hpp)

set(CPP main.cpp
		DebugDrawOpenGL.cpp
		PhysicsCar.cpp
		PhysicsContacts.cpp
		PhysicsTire.cpp
		Sprite.cpp
		Framework.cpp
		NeuralConnection.cpp
		NeuronInput.cpp
		PlotOpenGL.cpp
		SpikingNeuron.cpp
		Track.cpp)

set(NAME "snn")

add_executable(${NAME} ${HPP} ${CPP})
target_link_libraries(${NAME} nmemory)
target_link_libraries(${NAME} Box2D)