![GitHub](https://img.shields.io/github/license/mikeanth-dev/midicmd?style=for-the-badge)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/mikeanth-dev/midicmd?style=for-the-badge)
![GitHub top language](https://img.shields.io/github/languages/top/mikeanth-dev/midicmd?style=for-the-badge)
![Supported platforms](https://img.shields.io/badge/Platform-Linux-red?style=for-the-badge)

# MidiCMD

A linux command-line application that turns any MiDi device into a macro keyboard.

---

## Getting Started

### The easy solution: Getting the precompiled binaries

The recommended way to install is to download one of the precompiled binaries available in the releases page.  

### The hack3rman solution: Building from source

If, however, you're feeling adventurous or I don't provide the right arch for your system, building from source is a BREEZE.  
All you have to do is to ensure you have `make` installed on your system, then clone this repo and run `make install`.

### The first run

The first time you'll run this program, you should run `midicmd init` to finish setting up your instance and then feel free to check the `help` options or the wiki for more details.

### Enabling the service

Say you want this code to run every time you log in, but typing `midicmd start` manually is such a chore. What can you do?  
Fear not, you can simply enable `midicmd` as a service for the current user by running `midicmd enable` (assuming you ran `midicmd init` before, in order to finish the setup).

## Feedback, suggestions and help

For feedback, suggestions, bug reports etc., feel free to e-mail me at 'mike.anth99@gmail.com'.

---

_a project by Mircea-Pavel Anton (Mike Anthony)_
