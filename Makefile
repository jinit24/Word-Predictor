Main: compile_files
	
compile_files : word.cpp assets/Insert.cpp assets/Prednew.cpp assets/Misc.cpp 
	g++ -c word.cpp assets/Insert.cpp assets/Prednew.cpp assets/Misc.cpp
