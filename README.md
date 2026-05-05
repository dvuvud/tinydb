<p align="center">
  <img width="680" alt="tinydb_logo_no_tagline-2" src="https://github.com/user-attachments/assets/87ec195d-bf13-45b3-b3f5-bc00981a55bd"/>
</p>

<p align="center">
  A single-header, embedded key-value store for C++20.<br/>
  Drop one file into your project and you have a persistent database.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-20-blue?style=flat-square" alt="C++20"/>
  <img src="https://img.shields.io/badge/header--only-single%20file-4A7FD6?style=flat-square" alt="header-only"/>
  <img src="https://img.shields.io/badge/license-MIT-green?style=flat-square" alt="MIT"/>
  <img src="https://github.com/dvuvud/tinydb/actions/workflows/ci.yml/badge.svg" alt="CI"/>
</p>

---

```cpp
#include "tinydb.hpp"

tinydb::DB db("myapp.db");
db.put("username", "run");

if (auto name = db.get("username")) {
    std::cout << *name << "\n";   // run
}
```

No CMake. No dependencies. No linking. One `#include`.

---

## Install

Copy [`tinydb.hpp`](tinydb.hpp) into your project:

```bash
curl -O https://raw.githubusercontent.com/dvuvud/tinydb/main/tinydb.hpp
```

**Requirements:** C++20, GCC 12+, Clang 15+, or MSVC 19.34+. Linux, macOS, and Windows.

---

## Quick start

```cpp
#include "tinydb.hpp"

// Open or create a database
tinydb::DB db("app.db");

// Strings
db.put("city", "Stockholm");
auto city = db.get("city");    // std::optional<std::string>

// Numbers and any trivially copyable types
db.put("score", int32_t{100});
db.put("ratio", 0.95f);

auto score = db.get<int32_t>("score");
auto ratio = db.get<float>("ratio");

// Structs
struct Config { int port; bool debug; };
db.put("cfg", Config{8080, false});
auto cfg = db.get<Config>("cfg");

// Check and delete
if (db.has("city")) {
    db.remove("city");
}
```

---

## Docs

Full API reference is available at [dvuvud.github.io/tinydb](https://dvuvud.github.io/tinydb).

---

## Building

```bash
cmake -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

---

## MIT License

See [LICENSE](LICENSE).
