# One-Stop PC Parts – Inventory & Distribution Management System

A modular, terminal-based C++ system simulating a real-world production and distribution management platform for PC components.

## 🧩 Features

- 🧍‍♂️ Multi-role user system (Admin + Normal)
- 🔐 Secure password hashing (DJB2-style)
- 📦 Inventory + real-time demand tracking
- 🧠 Greedy algorithm to fulfill demands optimally
- ⛓️ Blockchain-style delivery logging (block ID, timestamp, hash)
- 📝 Action log (user-modified logs with timestamps)
- 🎨 ASCII CLI splash screen with animation
- ⏱️ Inactivity-based auto exit for session security
- 🌈 Color-coded terminal output

---

## 🛠️ System Components

| Module           | Responsibility                        |
|------------------|----------------------------------------|
| `UserSystem`     | Auth, login, register, admin controls  |
| `InventorySystem`| Stock, demand, allocation              |
| `Blockchain`     | Event chain for delivery records       |
| `Logger`         | Tracks who modified what and when      |
| `Main`           | Core loop, splash, menu navigation     |

---

## 📁 Data Persistence

The system uses `nlohmann/json` to store persistent data across runs:

- `users.json` – user credentials + roles
- `inventory.json` – inventory stock
- `demand.json` – region-based demand
- `blockchain.json` – event logs (supply fulfillment)
- `action_log.json` – user actions log

---

## 🔐 Security

- Passwords are hashed using DJB2-style one-way hash
- Banned users are time-locked with `banned_until`
- Admin controls can remove or ban other users
- All sensitive actions are logged

---

## 🧠 Algorithms

- **Greedy Search**:
  - Selects nearest location to fulfill demand
  - Prioritizes based on availability and proximity

---

## 📦 Installation & Usage

### 🔧 Requirements

- C++ compiler (MSVC, g++)
- `nlohmann/json.hpp` in `nlohmann/` directory

### ▶️ Compile & Run

```bash
g++ -std=c++20 -o logistics Main.cpp UserSystem.cpp InventorySystem.cpp Blockchain.cpp Logger.cpp -I. -I./nlohmann
./logistics
