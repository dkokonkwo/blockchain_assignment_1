Question One:

Task 1: Implement SHA-256 Hashing
1.    Objective: Implement the SHA-256 hashing algorithm in C to understand how data integrity is maintained in blockchain.
Submission Requirements:
•    Write a C program that takes a string as input and outputs its SHA-256 hash.
•    Include comments to explain how the SHA-256 algorithm processes the input to produce the hash.
•    Test the program by hashing the input "Blockchain Cryptography".


Task 2: Simple Blockchain Simulation
1.    Objective: Create a basic simulation of a blockchain in C that utilizes hashing for validating integrity.
Submission Requirements:
•    Define a Block structure in C that includes index, timestamp, data, previous hash, and the hash of the current block.
•    Implement a function to calculate the hash of a block and another to validate the chain.
•    Simulate a small blockchain where each new block is added after validating the entire chain.

Question Two:

Objective:

To develop and understand the core data structures that underpin blockchain technology, using the C programming language to create a simplified version of a blockchain.

Requirements:

Access to a C development environment (such as GCC Compiler, Visual Studio Code with C extension, or any C IDE).
Basic to intermediate knowledge of C programming, particularly pointers, dynamic memory allocation, structures, and file handling.
Assignment Tasks:

Task 1: Defining the Block Structure

Objective: Implement a Block structure that will act as the basic unit in the blockchain.
Instructions:
Define a Block structure in C that includes attributes such as index, timestamp, data (or transactions), previous hash, and the hash of the current block.
Implement a function to display block information.
Test by creating and displaying a single block.
Task 2: Creating a Blockchain

Objective: Implement a linked list to manage blocks in a blockchain.
Instructions:
Develop functions to add a block to the blockchain, ensuring that each new block correctly stores the hash of the previous block.
Implement the SHA-256 hashing function to generate hashes for each block (use a library or implement your own).
Write a function to validate the integrity of the blockchain by ensuring the chain of hashes is consistent throughout the blockchain.
Task 3: Simulating Transactions

Objective: Simulate transaction data within blocks.
Instructions:
Modify the Block structure to include a list of transactions (could be simple strings or a more complex structure).
Implement a function to add transactions to a block.
Ensure that changes in transaction data reflect accurately in the block’s hash.
Task 4: Blockchain Persistence

Objective: Save the blockchain to a file and load it back into the application.
Instructions:
Write functions to save the entire blockchain to a file and to load it from the file.
Ensure the integrity of the blockchain upon loading (re-validate hashes).
Deliverables:

Complete C source code for each task presenting the GitHub link.
A report documenting:
The structure and design of the implemented blockchain.
Challenges encountered during implementation and how they were resolved.
Output screenshots for each task.
Analysis of how the implemented data structures and functions simulate the basic operations of a real blockchain.
