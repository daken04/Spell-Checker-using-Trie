# Spell Checker

## Problem Statement

Design an efficient spell checker using the trie data structure, supporting the following functionalities:

### Required Features:

1. **Spell Check:** Checking if the input string is present in the dictionary.
2. **Autocomplete:** Finding all the words in the dictionary that begin with the given input.
3. **Autocorrect:** Finding all the words in the dictionary that are at an edit distance (Levenshtein distance) of at most 3 from the given input.

### Input Format:

- The first line contains two space-separated integers `n` and `q`, representing the number of words in the dictionary and the number of queries to be processed, respectively.
- The next `n` lines contain a single string `s` representing a word in the dictionary.
- The next `q` lines contain two space-separated values. The first one is an integer `ai`, and the second will be a string `ti`.
  - `ai = 1` means Spell Check operation needs to be done on `ti`.
  - `ai = 2` means Autocomplete operation needs to be done on `ti`.
  - `ai = 3` means Autocorrect operation needs to be done on `ti`.
- Both strings `s` and `t` consist of lowercase English letters.

### Output Format:

- Spell check: Printing ‘1’ if the string is present in the dictionary, otherwise ‘0’.
- Autocomplete & Autocorrect: Printing the number of words in the first line. The following lines will be the set of words in lexicographical order.
