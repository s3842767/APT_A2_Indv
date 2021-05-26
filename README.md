# APT_A2
Repository for Advanced Programming Techniques Assignment 2
## Testing


```bash
./qwirkle < <testname>.input > <testname>.gameout
diff -w <testname>.output <testname>.gameout
if [-e <testname>.expsave] diff -w -y <testname>.expsave <actual_gamesave>
```