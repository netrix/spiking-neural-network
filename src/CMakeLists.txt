set(SIMULATION_PHYSICS_SOURCES
	Simulation/Physics/Car.cpp
	Simulation/Physics/Car.hpp
	Simulation/Physics/Contacts.cpp
	Simulation/Physics/Contacts.hpp
	Simulation/Physics/FixtureUserData.hpp
	Simulation/Physics/Tire.cpp
	Simulation/Physics/Tire.hpp
)

set(SIMULATION_PROBES_SOURCES
	Simulation/Probes/IImpulseHandler.hpp
	Simulation/Probes/TrackDistance.cpp
	Simulation/Probes/TrackDistance.hpp
)

set(SIMULATION_SOURCES
	Simulation/Track.cpp
	Simulation/Track.hpp
	Simulation/World.cpp
	Simulation/World.hpp
)

set(SOURCES
	Common.hpp
	DebugDrawOpenGL.cpp
	DebugDrawOpenGL.hpp
	Exceptions.hpp
	Framework.cpp
	Framework.hpp
	ImpulsePlot.cpp
	ImpulsePlot.hpp
	main.cpp
	NeuralConnection.hpp
	NeuralConnection.cpp
	NeuronInput.hpp
	NeuronInput.cpp
	PlotOpenGL.hpp
	PlotOpenGL.cpp
	SpikingNeuron.cpp
	SpikingNeuron.hpp
	Sprite.cpp
	Sprite.hpp
	TestEnvironment.hpp
)

set(ALL_SOURCES
	${SIMULATION_PHYSICS_SOURCES}
	${SIMULATION_PROBES_SOURCES}
	${SIMULATION_SOURCES}
	${SOURCES}
)

set(NAME "snn")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${NAME} ${ALL_SOURCES})
target_link_libraries(${NAME} nmemory)
target_link_libraries(${NAME} Box2D)

# For Visual Studio
source_group(src FILES ${SOURCES})
source_group(src\\Simulation FILES ${SIMULATION_SOURCES})
source_group(src\\Simulation\\Physics FILES ${SIMULATION_PHYSICS_SOURCES})
source_group(src\\Simulation\\Probes FILES ${SIMULATION_PROBES_SOURCES})