# Bloom Filter Implementation in C
A simple bloom filter implementation written in C. Bloom filters are space-efficient probabilistic data-structures that is used to test whether an element is a member of a set. False positive results are possible, but false negatives are not. This implementation uses a murmurhash3 hashing algorithm, a fast non-cryptographic hash function suitable for general hash-based lookups. Bloom filters are most commonly used in databases such as PostgreSQL to speed up query execution time by potentially reducing the need to perform costly disk I/O.

![image](https://user-images.githubusercontent.com/39445369/148291118-0ee7093b-6f08-4b51-9ed6-a010dfe254b6.png)


## How to Run
The `main.c` program takes in a file, ideally one that has a list of words (separated by new lines) that a user wants to add to the data structure. Before running, go to `main.c` and tweak the `FALSE_POSITIVE_RATE` parameter to your target false positive rate.
1. Run `make` or `make debug` -- this should generate a `main` file executable that could then be ran
2. Run `./main <INSERT_FILE_NAME>` with INSERT_FILE_NAME containing the file which you want to read words from
3. The terminal should then generate a report containing the best parameters for the bloom filterm, the false positive rate information, and space utilization in bytes compared to a less space-efficient data structure like an array/hashset.

![image](https://user-images.githubusercontent.com/39445369/148290742-aa7c5094-5abe-42a3-967e-b125697d976f.png)

### Makefile options
1. `make clean`: removes all object files and the main object file
2. `make debug`: enables the -DDEBUG flag which when enabled, currently prints out potential duplicate words
3. `make test`: runs the main executable on a specified text file in the Makefile
4. `make valgrind`: runs `make test` but with valgrind to check for memory leaks

### Testing
This repository has included three files to perform tests on the bloom filter.
1. `1-1000.txt`: this text file contains the 1000 most common words in the english language
2. `1000-md5.txt`: this text file contains 1000 randomly generated md5 hash values
3. `10000-md5.txt`: this text file contains 10000 randomly generated md5 hash values


## Todo/Features

- [ ] Write output to file
- [ ] More hash functions 
- [ ] Writing Bloomfilters out to file for persistent storage
