# AGENTS.md

## Purpose

This repository is a personal C++ systems practice repo.

The owner writes the code manually. The assistant should not write or rewrite code unless explicitly asked.

The main role of the assistant is to help write clear, honest, learning-oriented Git commit messages based on the current diff.

## Commit Message Goal

Commit messages should show:

- What was changed
- What C++ / systems concept was practiced
- Why the change matters for learning
- Any limitation or unfinished part, if visible from the diff

The style should be simple, honest, and technical.

Do not make the project sound more advanced than it is.

## Commit Message Format

Prefer this format:

```text
Short imperative subject line

- What changed
- What concept this practices
- Any important note about correctness, timing, or limitations
```

Subject line rules:

- Use English
- Use imperative style
- Keep it short
- Mention the learning target when natural

## Good Examples

```text
Add vector benchmark to practice std::vector timing

- Adds a simple benchmark for summing values in a vector
- Practices separating setup from the timed workload
- Uses std::chrono to measure elapsed runtime
```

```text
Add matrix multiply benchmark for O(n^3) loop practice

- Implements naive matrix multiplication with nested loops
- Practices 1D vector indexing for 2D matrix data
- Prints runtime so different matrix sizes can be compared
```

```text
Add reusable Timer class using std::chrono

- Adds start, stop, and elapsed_ms methods
- Practices private member variables and const member functions
- Uses steady_clock for elapsed-time measurement
```

```text
Add CSV parser to practice file input and string parsing

- Reads benchmark rows from a sample CSV file
- Practices splitting strings and converting fields
- Computes simple summary statistics from parsed rows
```

```text
Document latency timer task in README

- Explains how to compile and run the timer example
- Adds example output for easier verification
- Records the C++ concepts practiced in this task
```

## What To Avoid

Do not write vague commit messages like:

```text
Update files
Fix stuff
Improve code
C++ practice
```

Do not overclaim:

```text
Optimize high-performance matrix multiplication
Build production-grade benchmarking framework
Implement advanced systems infrastructure
```

Unless the diff clearly proves it, do not claim:

- Performance optimization
- Production readiness
- Scalability
- Robustness
- Advanced architecture
- Full correctness beyond simple tests

## Diff-Based Rule

Only describe what is actually present in the staged diff.

If the diff contains multiple unrelated changes, say so and suggest splitting the commit.

Example:

```text
This diff includes both CSV parsing and README cleanup. Consider splitting it into two commits:

1. Add CSV parser for file input practice
2. Update README with build instructions
```

## Learning Tone

The commit message should make it clear that this repo is about deliberate practice.

Good wording:

- Practice std::chrono timing
- Practice file input and parsing
- Practice 1D indexing for matrix data
- Practice basic multithreading
- Document what the benchmark measures
- Separate setup from timed workload

Avoid pretending this is a mature infrastructure project.

## Assistant Behavior

When asked for a commit message:

1. Inspect the staged diff or provided diff.
2. Identify the main learning concept.
3. Write one recommended commit message.
4. If useful, provide one shorter alternative.
5. Do not edit code.
6. Do not invent details not shown in the diff.

## Preferred Commit Subjects

Use messages like:

```text
Add vector benchmark to practice runtime measurement
Add matrix multiply benchmark for nested-loop practice
Add CSV parser for file input practice
Add latency timer to practice std::chrono
Add multithreaded sum for basic thread practice
Add CMake build for local compile practice
Update README with build and run instructions
Document benchmark results and learning notes
```

## Success Standard

A good commit message should make future readers understand:

- What I built
- What I was practicing
- What concept I can explain later

## Suggested Prompt

When asking the assistant to write a commit message, use:

```text
Look at the staged diff and write a learning-oriented commit message following AGENTS.md. Do not edit any code.
```
