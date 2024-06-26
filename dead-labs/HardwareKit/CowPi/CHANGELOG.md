# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to
[Semantic Versioning](https://semver.org/spec/v2.0.0.html).

<!--

## [major.minor.patch] - yyyy-mm-dd

-->

## [Unreleased]

- LCD1602 default dialect for SPI
- Bit-banged I2C implementation
- Microcontroller-dependent code other than that for ATMega328P

<!--
- `Added` for new features.
- `Changed` for changes in existing functionality.
- `Deprecated` for soon-to-be removed features.
- `Removed` for now removed features.
- `Fixed` for any bug fixes.
- `Security` in case of vulnerabilities.
-->

## [0.3.0] - 2022-08-01

### Added

- Replaced single header file with library
  - Default implementations for reading inputs and writing outputs
    - Most are microcontroller-independent; I2C is still ATMega328P-only
  - Microcontroller-dependent code (*e.g.* memory-mapped I/O structures)
    isolated from microcontroller-independent code
  - Framework to allow polling I/O code and memory-mapped I/O code to be graded
    distinctly
- 7-segment and dot-matrix fonts
- Framework to control LCD1602 display module; students only need to write code
  to use SPI or I2C hardware
- Setup code to enable `printf`/`scanf` for AVR microcontrollers
- Example code
  - Replace test code in construction instructions with examples
  - Additional examples demonstrating library features

## [0.2.1] - 22-04-26

### Added

- Default implementations to scan keypad and to send data to display module

### Fixed

- Explicitly configures NAND input pins

## [0.2.0] - 22-04-01

### Added

- Setup code to configure I/O pins
- Setup code to configure MAX7219
- Macros to enable and disable SPI hardware, to leave external LED an output pin

### Changed

## [0.1.0] - 2021-11-02

### Added

- `cowpi.h`

  - Structures for accessing ATMega328P memory-mapped I/O registers
