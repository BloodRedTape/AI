cmake_minimum_required(VERSION 3.10)

add_library(AICore 
	"sources/neural_network.cpp"
)

target_include_directories(AICore PUBLIC "sources")
target_link_libraries(AICore PUBLIC StraitXBase)
