# === COMPILER SETTINGS ===
CXX = g++
CXXFLAGS = -std=c++11 -Wall -pthread
INCLUDE = -Iinclude

# === DAY 1 ===
day1:
	$(CXX) $(CXXFLAGS) $(INCLUDE) src/main_day1.cpp src/Authenticator.cpp -o mindmancer_day1
	./mindmancer_day1

test_day1:
	$(CXX) $(CXXFLAGS) $(INCLUDE) test/test_auth_simulated.cpp src/Authenticator.cpp -o test_day1
	./test_day1

# === DAY 2 ===
day2:
	$(CXX) $(CXXFLAGS) $(INCLUDE) \
	src/main_day2.cpp \
	src/SessionManager.cpp \
	src/WorkSessionManager.cpp \
	src/TimerCount.cpp \
	src/TaskLogger.cpp -o mindmancer_day2
	./mindmancer_day2

test_day2:
	$(CXX) $(CXXFLAGS) $(INCLUDE) \
	test/TestWorkSessionManager.cpp \
	src/SessionManager.cpp \
	src/WorkSessionManager.cpp \
	src/TimerCount.cpp -o test_day2
	./test_day2

# === DAY 3 ===
day3:
	$(CXX) $(CXXFLAGS) $(INCLUDE) \
	src/main_day3.cpp \
	src/SessionManager.cpp \
	src/WorkSessionManager.cpp \
	src/BreakSessionManager.cpp \
	src/TimerCount.cpp \
	src/TaskLogger.cpp \
	src/MotivationalQuoteManager.cpp \
	src/SessionSummary.cpp \
	src/SessionConfigManager.cpp -o mindmancer_day3
	./mindmancer_day3

test_day3: test_break test_quote test_summary

test_break:
	$(CXX) $(CXXFLAGS) $(INCLUDE) \
	test/TestBreakSessionManager.cpp \
	src/BreakSessionManager.cpp \
	src/SessionManager.cpp \
	src/TimerCount.cpp \
	src/TaskLogger.cpp -o test_break
	./test_break

test_quote:
	$(CXX) $(CXXFLAGS) $(INCLUDE) \
	test/TestMotivationalQuoteManager.cpp \
	src/MotivationalQuoteManager.cpp -o test_quote
	./test_quote

test_summary:
	$(CXX) $(CXXFLAGS) $(INCLUDE) \
	test/TestSessionSummary.cpp \
	src/SessionSummary.cpp -o test_summary
	./test_summary

# === DAY 4 ===
day4:
	$(CXX) $(CXXFLAGS) $(INCLUDE) \
	src/main_day4.cpp \
	src/SessionManager.cpp \
	src/WorkSessionManager.cpp \
	src/BreakSessionManager.cpp \
	src/TimerCount.cpp \
	src/TaskLogger.cpp \
	src/MotivationalQuoteManager.cpp \
	src/SessionSummary.cpp \
	src/SessionConfigManager.cpp -o mindmancer_day4
	./mindmancer_day4

test_day4:
	$(CXX) $(CXXFLAGS) $(INCLUDE) \
	test/TestSessionConfigManager.cpp \
	src/SessionConfigManager.cpp -o test_config
	./test_config

# === CLEAN ===
clean:
	rm -f mindmancer_day1 mindmancer_day2 mindmancer_day3 mindmancer_day4 \
	      test_day1 test_day2 test_break test_quote test_summary test_config \
	      *.log
