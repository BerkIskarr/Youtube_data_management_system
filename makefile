# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++14

# Target and dependencies
Cpp2nd: Video.o Person.o DataManager.o Creator.o User.o main.o
	$(CXX) $(CXXFLAGS) Video.o Person.o DataManager.o Creator.o User.o main.o -o Cpp2nd

# Compile Video.cpp into Video.o
Video.o: Video.cpp
	$(CXX) $(CXXFLAGS) -c Video.cpp

# Compile Person.cpp into Person.o
Person.o: Person.cpp
	$(CXX) $(CXXFLAGS) -c Person.cpp

# Compile DataManager.cpp into DataManager.o
DataManager.o: DataManager.cpp
	$(CXX) $(CXXFLAGS) -c DataManager.cpp

# Compile Creator.cpp into Creator.o
Creator.o: Creator.cpp
	$(CXX) $(CXXFLAGS) -c Creator.cpp

# Compile User.cpp into User.o
User.o: User.cpp
	$(CXX) $(CXXFLAGS) -c User.cpp

# Compile main.cpp into main.o
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# Clean rule to remove object files and the executable
clean:
	rm -f *.o Cpp2nd
