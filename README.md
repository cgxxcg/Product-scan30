### Parsing customer transaction data from an input CSV file
This is a system that can store customer transaction data and query it using transaction identifiers (i.e., the id field from the CSV file). This is achieved by implementing a hash table-based database that uses single linked chains for collision resolution. Each record in input CSV will contain the following fields: id, purchased_item, and cost.

To call executable with arguments: 
```./lookup [-s threshold] [-t table_size] <filename>```


```-s threshold```(optional flag with required argument):
Prints descriptive metadata about the hash table and its linked list chains after all queries are processed (as shown in the “Input/Output Examples” section).

```-t table_size```(optional flag with required argument):
Table_size is an integer specifying the size that we should create the hash table with. If -t is not specified, the default size of the hash table should be the constant DEFAULT_TABLE_SIZE, as defined in the lookup.c. If table_size is smaller than the constant MIN_TABLE_SIZE, then the program must make the hash table size to MIN_TABLE_SIZE. Table size won’t be greater than INT_MAX.

```filename```(required)
The path to the input CSV. Each record in this CSV must have three columns, in this order: id,purchased_item, cost

All CSV files that existed are properly-formatted (no empty columns).


