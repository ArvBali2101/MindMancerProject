# MindMancerProject

# MindMancerProject – Day 1

Terminal-based anti-procrastination assistant (C++)

## ✅ Features Implemented (Day 1)

- `Authenticator` class to validate user login
- Tracks remaining login attempts
- Simulated test with hardcoded password entries
- Colored output for status messages (success, failure)
- Organized into `include/`, `src/`, `test/`, `notes/`

## 📁 Folder Structure

MindMancerProject/
├── include/ # Header files
│ └── Authenticator.h
├── src/ # Implementation files
│ └── Authenticator.cpp
├── test/ # Test cases
│ └── test_auth_simulated.cpp
├── notes/ # Developer notes
│ └── Day1_Notes.md
├── Makefile # Build and run targets
└── README.md # Project documentation


## 🛠️ How to Run

```bash
make simtest    # Build and run simulated login
make clean      # Remove compiled files

# ✅ Day 2 – Work Timer with Pause / Resume / Stop

---

## 🎯 Objective

Implement a modular, interactive work session timer using:
- Countdown logic
- Pause (`p`), Resume (`r`), and Stop (`q`)
- Threaded timer logic
- Inheritance-based class design (`SessionManager`)
- Clean folder structure, proper Makefile, README, and Notes

---

## 🔧 Features Implemented

- `SessionManager`: Abstract timer base class with pause/resume/stop
- `WorkSessionManager`: Controls a Pomodoro-style session
- `TimerCount`: Tracks completed work sessions
- `main_day2.cpp`: CLI-driven UI with menu
- Input instructions shown during runtime
- Compatible with Windows/Linux (`conio.h` use guarded)

---

## 🧪 Testing

### ✔️ Manual:
- Run `make day2` and interact with:
  - `1` Start session
  - `2` Show session count
  - `3` Exit
  - Use `p`, `r`, `q` during session

### ✔️ Unit Test:
- File: `test/TestWorkSessionManager.cpp`
- Covers:
  - Setting session duration
  - Timer count increment
  - Pause/resume state check

Run:
```bash
make test_work

✅ Day 3 – Breaks, Quotes, and Summary

### 🎯 Features Added

- **BreakSessionManager**: After every work session, triggers a short break. After every 4th session, a long break.
- **MotivationalQuoteManager**: Periodically shows motivational quotes during work to keep morale high.
- **SessionSummary**: Parses the task log and displays:
  - Total number of sessions
  - Active duration per session
  - Total active time spent

### 🧪 Tests Written
- `TestBreakSessionManager.cpp`
- `TestMotivationalQuoteManager.cpp`
- `TestSessionSummary.cpp`

### 🧩 Dependencies
- Works alongside:
  - `SessionManager` (abstract base)
  - `TaskLogger` (for logging)
  - `TimerCount` (for tracking session count)

---

## 🛠 Running Day 3

```bash
make day3           # Full feature run
make test_day3      # Runs all 3 Day 3 tests