set(FRAMEWORK_SOURCES
	Framework/Framework.cpp
	Framework/Framework.hpp
	Framework/Sprite.cpp
	Framework/Sprite.hpp
	Framework/DebugDrawOpenGL.cpp
	Framework/DebugDrawOpenGL.hpp
)

set(PLOTS_SOURCES
	Plots/PlotRenderer.cpp
	Plots/PlotRenderer.hpp
	Plots/ImpulsePlot.cpp
	Plots/ImpulsePlot.hpp
	Plots/ImpulsePlotBundle.cpp
	Plots/ImpulsePlotBundle.hpp
)

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
	Simulation/Probes/CarVelocity.cpp
	Simulation/Probes/CarVelocity.hpp
	Simulation/Probes/IImpulseHandler.hpp
	Simulation/Probes/LeftDistance.cpp
	Simulation/Probes/LeftDistance.hpp
	Simulation/Probes/TrackAngle.cpp
	Simulation/Probes/TrackAngle.hpp
	Simulation/Probes/TrackDistance.cpp
	Simulation/Probes/TrackDistance.hpp
	Simulation/Probes/TrackSide.cpp
	Simulation/Probes/TrackSide.hpp
)

set(SNN_SOURCES
	SNN/Common.hpp
	SNN/NeuralConnection.hpp
	SNN/NeuralConnection.cpp
	SNN/NeuronInput.hpp
	SNN/NeuronInput.cpp
	SNN/SpikingNeuron.cpp
	SNN/SpikingNeuron.hpp
)

set(SIMULATION_SOURCES
	Simulation/PassageEvaluator.cpp
	Simulation/PassageEvaluator.hpp
	Simulation/Track.cpp
	Simulation/Track.hpp
	Simulation/World.cpp
	Simulation/World.hpp
)

set(SOURCES
	Exceptions.hpp
	main.cpp
	PlotImpulseHandle.cpp
	PlotImpulseHandle.hpp
	TestEnvironment.hpp
)

set(ALL_SOURCES
	${FRAMEWORK_SOURCES}
	${PLOTS_SOURCES}
	${SIMULATION_PHYSICS_SOURCES}
	${SIMULATION_PROBES_SOURCES}
	${SIMULATION_SOURCES}
	${SNN_SOURCES}
	${SOURCES}
)

set(NAME "snn")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${NAME} ${ALL_SOURCES})
target_link_libraries(${NAME} nmemory)
target_link_libraries(${NAME} Box2D)

# For Visual Studio
source_group(src FILES ${SOURCES})
source_group(src\\Framework FILES ${FRAMEWORK_SOURCES})
source_group(src\\Plots FILES ${PLOTS_SOURCES})
source_group(src\\Simulation FILES ${SIMULATION_SOURCES})
source_group(src\\Simulation\\Physics FILES ${SIMULATION_PHYSICS_SOURCES})
source_group(src\\Simulation\\Probes FILES ${SIMULATION_PROBES_SOURCES})
source_group(src\\SNN FILES ${SNN_SOURCES})