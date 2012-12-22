set(SIMULATION_PHYSICS_SOURCES
	simulation/physics/Car.cpp
	simulation/physics/Car.hpp
	simulation/physics/Contacts.cpp
	simulation/physics/Contacts.hpp
	simulation/physics/FixtureUserData.hpp
	simulation/physics/Tire.cpp
	simulation/physics/Tire.hpp
)

set(SIMULATION_PROBES_SOURCES
	simulation/probes/IImpulseHandler.hpp
	simulation/probes/TrackDistance.cpp
	simulation/probes/TrackDistance.hpp
)

set(SIMULATION_SOURCES
	simulation/Track.cpp
	simulation/Track.hpp
	simulation/World.cpp
	simulation/World.hpp
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
source_group(src\\simulation FILES ${SIMULATION_SOURCES})
source_group(src\\simulation\\physics FILES ${SIMULATION_PHYSICS_SOURCES})
source_group(src\\simulation\\probes FILES ${SIMULATION_PROBES_SOURCES})