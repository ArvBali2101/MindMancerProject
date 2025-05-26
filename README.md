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
