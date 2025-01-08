# shell.nix
{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  # Include essential build tools and C development packages
  buildInputs = with pkgs; [
    # Core development tools
    gcc       # GNU C Compiler
    gdb       # GNU Debugger
    gnumake   # Make build automation tool
    cmake     # Build system generator
    
    # Development utilities
    valgrind  # Memory leak detector
    clang-tools # Includes clang-format, clang-tidy
    bear      # Tool for generating compilation database
    
    # Code analysis and formatting
    cppcheck  # Static analysis tool
    uncrustify # Code beautifier
    
    # Documentation
    man
    man-pages
    man-pages-posix
    
    # Additional libraries (uncomment as needed)
    # gsl      # GNU Scientific Library
    # openblas # Basic Linear Algebra Subprograms
  ];

  # Set environment variables
  shellHook = ''
    echo "C Development Environment"
    echo "Available tools:"
    echo " - gcc: $(gcc --version | head -n1)"
    echo " - make: $(make --version | head -n1)"
    echo " - cmake: $(cmake --version | head -n1)"
    echo " - gdb: $(gdb --version | head -n1)"
    echo ""
    echo "Run 'man <command>' for documentation"
  '';
}
