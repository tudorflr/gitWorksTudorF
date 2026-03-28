# AI-Assisted Code Compiler

A system that combines AI-generated code with automated execution and testing, then iteratively improves the solution based on feedback from failed test cases.

## Overview

The project explores using AI inside a real execution loop rather than as a one-time code generator.

Given a problem and test cases, the system:
- generates code
- runs it
- checks correctness
- feeds back errors
- retries with an improved solution

## How it works

- Task definition
  - input, expected output, test cases

- Code generation
  - initial solution produced by AI ( python, java, C++, for now )

- Execution
  - runs code and captures output, errors, runtime

- Validation
  - compares actual output with expected output

- Feedback loop
  - failed tests are summarized and sent back
  - a new solution is generated

- Iteration
  - repeats until success or max attempts reached

## Features

- iterative correction loop based on test results
- automated execution and validation
- structured execution results (status, output, errors)
- attempt history tracking
- timeout handling for execution safety

## Structure

- RunManager handles the full pipeline
- CodeRunner executes code
- Judge compares outputs
- TaskSpec defines problems and tests
- ExecutionResult stores run results

## Example

Input: 13
Expected output: 39

The system may require multiple attempts to reach the correct result, fixing issues such as formatting or logic errors.

## Future work

- web API for submitting and viewing runs
- database for storing history
- simple web interface similar to coding platforms
- improved feedback strategies

## Tech

- Python
- subprocess execution
- JSON-based task definitions

## Status

In progress. Core loop is implemented and working.
