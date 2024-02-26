# Text Editor
This project is for practicing and enhancing software skills in modern C++, TDD, OOP, and design patterns.
- Build Tool: CMake
- Development Environment: Docker Container
- Language: C++
- Unit Testing Framework: GoogleTest

## Possible Process for MVP (AI generated)
### 1. Core Components:
  - Text Buffer: This is where the text content is stored. It should support operations like insert, delete, and update text.
  - Cursor Management: Manages the position of the cursor in the text buffer. It should allow moving the cursor up, down, left, and right.
  - Command Processing: Interprets user input as commands. Commands could include opening a file, saving a file, moving the cursor, inserting text, etc.
  - Screen Rendering: Updates the terminal display to reflect the current state of the text buffer and cursor position.
### 2. Basic Features:
  - Opening and Saving Files: Allow users to open existing files and save their work.
  - Cursor Movement: Implement navigation keys for moving the cursor within the text.
  - Editing Text: Support for inserting and deleting text at the cursor's position.
  - Command Mode: A mode for entering commands, separate from the text editing mode.
### 3. Development Steps:
  - Design and Plan: Outline the architecture and functionality of your text editor. Decide on the design patterns and data structures to use.
  - Implement Core Components: Start by implementing the core components like the text buffer, cursor management, and command processing.
  - Develop Basic Features: Implement the basic features like file handling, cursor movement, and text editing.
  - Testing: Write unit tests for each component and feature to ensure they work as expected.
  - Iterate and Refine: Based on testing feedback, iterate and refine your implementation. Add new features and improve existing ones.
### 4. Tools and Libraries:
  - CMake: For managing the build process and dependencies.
  - GoogleTest: For writing and running unit tests.
  - Docker: For creating a consistent development environment.
  - NCURSES: A library for creating text-based user interfaces in a terminal. It's crucial for rendering the text editor in a terminal.
### 5. Design Patterns:
  - Command Pattern: Use the Command pattern for implementing undo/redo functionality and handling user commands.
  - Observer Pattern: Use the Observer pattern to notify the screen rendering component of changes in the text buffer or cursor position.
### 6. Modern C++ Practices:
  - Utilize modern C++ features like smart pointers, range-based for loops, and STL containers.
  - Follow Object-Oriented Programming (OOP) principles to structure your code.
### 7. Final Steps:
  - User Interface: Enhance the text editor with a more user-friendly interface, including status bars, menus, or command line prompts.
  - Advanced Features: Consider adding more advanced features like syntax highlighting, auto-completion, and custom commands.
  - Documentation: Write documentation for your text editor, including usage instructions and API documentation.
