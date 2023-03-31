cmake_minimum_required(VERSION 3.10)

add_library(AICore 
	"sources/layered_neural_network.cpp"
 "sources/neuron.cpp" "sources/layer.cpp")

target_include_directories(AICore PUBLIC "sources")
target_link_libraries(AICore PUBLIC StraitXBase)
