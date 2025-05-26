# ===== Compiler and Flags =====
CXX = g++
CXXFLAGS = -std=c++11 -Wall -pthread
INCLUDE = -Iinclude

# ===== Day 1 (Login System) =====
DAY1_SRC = src/main_day1.cpp src/Authenticator.cpp

day1:
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(DAY1_SRC) -o mindmancer_day1
	./mindmancer_day1

# ===== Day 2 (Work Timer System) =====
DAY2_SRC = src/main_day2.cpp \
           src/SessionManager.cpp \
           src/WorkSessionManager.cpp \
           src/TimerCount.cpp \
           src/TaskLogger.cpp

day2:
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(DAY2_SRC) -o mindmancer_day2
	./mindmancer_day2

# ===== Unit Test: WorkSessionManager =====
test_work:
	$(CXX) $(CXXFLAGS) $(INCLUDE) test/TestWorkSessionManager.cpp \
	src/SessionManager.cpp src/WorkSessionManager.cpp src/TimerCount.cpp -o test_work
	./test_work

# ===== Cleanup =====
clean:
	rm -f mindmancer_day1 mindmancer_day2 test_work
