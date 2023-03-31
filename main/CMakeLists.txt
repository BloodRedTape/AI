cmake_minimum_required(VERSION 3.10)

add_executable(AIMain
	"sources/main.cpp"
)

target_include_directories(AIMain PUBLIC "sources")
target_link_libraries(AIMain PUBLIC AICore)
