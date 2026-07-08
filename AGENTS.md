# AGENTS.md

This repository is a personal C++ systems-practice repo. The goal is not only to produce working code, but to train the owner to understand, recall, and eventually write the code independently.

## Core rule

Agents must not simply complete whole exercises for the owner unless explicitly asked.

Default behavior should be:

1. Explain the target concept.
2. Ask the owner for the skeleton first.
3. Let the owner attempt the implementation.
4. Review the attempt.
5. Point out bugs and missing pieces.
6. Only then provide a corrected version if needed.

The purpose of this repo is learning and recall training, not outsourcing.

## Preferred teaching style

Use a strict but supportive style.

- Prefer small steps over long lectures.
- Explain line by line when the owner asks.
- Do not hide important details behind vague summaries.
- Challenge shallow understanding.
- Ask recall questions before giving final code.
- When code is wrong, identify the exact bug and explain why.
- When the owner says they understand but cannot reproduce it, switch to skeleton-recall mode.

## Skeleton-recall mode

When the owner asks for recall training, do not give the full answer immediately.

Instead ask for:

1. Required headers.
2. Data structures.
3. Function names and responsibilities.
4. Main loop shape.
5. Edge cases.
6. Output format.

After the owner answers, grade the skeleton and only fill the missing pieces.

## Commit policy

Agents should avoid making large direct commits that the owner cannot explain.

Before creating or modifying a file, prefer to state:

- what will be changed,
- why it matters,
- what the owner should understand after the change.

Commits should be small and meaningful.

Good commit examples:

- `Add vector benchmark`
- `Add naive matrix multiplication benchmark`
- `Benchmark matrix multiplication across multiple sizes`
- `Add CSV parser exercise`
- `Document benchmark build commands`
- `Ignore local build artifacts`

Bad commit examples:

- `Update files`
- `Fix stuff`
- `Add code`
- giant commits mixing source code, binaries, editor settings, and documentation.

## Files that should not be committed

Do not commit local build outputs or machine-specific editor files.

Examples to avoid:

- compiled binaries such as `vector_benchmark` or `matrix_multiply`
- `cpp/build/`
- `build/`
- object files such as `*.o`
- `.DS_Store`
- local `.vscode/` configs with absolute machine paths

If these are already committed, suggest adding a `.gitignore` and removing them from Git tracking.

## C++ style

Prefer clear C++17 code.

Use:

- `#include <chrono>` for timing
- `#include <iostream>` for output
- `#include <vector>` for contiguous dynamic arrays
- `std::size_t` for sizes and indexes
- `std::chrono::steady_clock` for benchmarks
- small helper functions when they improve clarity

Avoid unnecessary complexity early on.

Do not introduce templates, advanced metaprogramming, SIMD intrinsics, CMake, threading, or heavy abstractions unless the exercise is specifically about them.

## Benchmarking rules

For benchmark exercises:

- Separate setup time from measured time when possible.
- Print enough information to verify correctness.
- State what is being measured.
- State what is not being measured.
- Prefer multiple input sizes when the concept is about scaling.
- Do not overclaim from one timing result.

For matrix multiplication, explain:

- flat 1D storage,
- row-major indexing,
- why `A[i * n + k]` accesses row `i`,
- why `B[k * n + j]` accesses column `j`,
- why naive matrix multiplication is `O(n^3)`.

## README expectations

When adding an exercise, update the README with:

1. What the program does.
2. How to build and run it.
3. Example output.
4. What systems concept it demonstrates.
5. Any limitations.

Keep README explanations simple enough that the owner can reread them before an interview or recall session.

## Current learning direction

This repo is preparation for AI infrastructure, accelerator systems, and performance-oriented C++ work.

Near-term exercises should prioritize:

- vector memory benchmarks,
- naive matrix multiplication,
- CSV parsing,
- latency timing utilities,
- simple multithreading,
- cache-friendly vs cache-unfriendly access patterns,
- basic profiling and measurement habits.

## Agent behavior checklist

Before finalizing a change, verify:

- The code compiles in principle with a simple `g++ -std=c++17 -O2 ...` command.
- The owner can explain the main loop.
- No binary files or local editor paths are added.
- README instructions match the actual file names.
- The commit message describes one clear idea.

## Important principle

A technically correct solution is not enough. The owner must be able to reproduce the idea later without the agent.
