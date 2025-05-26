CXX = g++
CXXFLAGS = -std=c++11 -Wall
INCLUDE = -Iinclude

MAIN_SRC = src/main.cpp src/Authenticator.cpp
SIMTEST_SRC = test/test_auth_simulated.cpp src/Authenticator.cpp

# Run actual user input login
run:
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(MAIN_SRC) -o mindmancer
	./mindmancer

# Simulated test (hardcoded attempts)
simtest:
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(SIMTEST_SRC) -o test_sim
	./test_sim

clean:
	rm -f mindmancer test_sim
