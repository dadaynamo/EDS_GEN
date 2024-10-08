# EDS_GEN
This C++ application generates a random EDS (Elastic Degenerate String) file based on user-defined parameters like max file length, elastic word structure, repetitiveness, and percentage of degenerate symbols. It provides flexibility for creating customizable EDS files for analysis and testing.

## Installation
Use make command to compile the cpp program

## Usage: 
### With Makefile
```
make eds
```
```
make raw
```
```
make help
```
```
make version
```
### Classic Execution
```
./EDS-GEN [option] [argument] | ...
```

Options:
  --help                        Show this help message and exit.
  
  --type <type>                 Specify the type of sequences (Raw, Eds, Eds-intensive, Test)
                                 Example: --type [R, E, I, T]

  --output <outputfile>          Specify the name of the output file without the extension.
                                 Example: --output result
  
  --totSize <TOTsize>               Set the maximum size of the generated output.
                                 Example: --size 1000

  --maxPerDeg <maxPerDeg>         Set the max number  of degenerate symbols in the generated sequence.
                                 Example: --maxPerDeg 25
                              

--numDeg <numDeg>         Set the max number  of degenerate symbols in the generated sequence.
                                 Example: --numDeg 5
                              
  --repeatability <level>        Set the repeatability level for the EDS (Elastic Degenerate Sequence). (NOT IN USE)
                                 Accepted values: 1 to 10.
                                 Example: --repeatability 5

  --degenerate <percentage>      Set the percentage of degenerate symbols in the generated sequence. (NOT IN USE)
                                 Accepted values: 0 to 100.
                                 Example: --degenerate 25

  --seed <seedvalue>             Specify a seed for random number generation to ensure repeatable results. (NOT IN USE)
                                 Example: --seed 12345

  --custom-alphabet <string>     If --alphabet is set to "custom", define the custom alphabet. (NOT IN USE)
                                 Example: --custom-alphabet "abcdxyz"

  --version                      Display the version of the program and exit.

### Examples:
```
  ./mainEDS-GEN --type E --outputName intensive --totSize 1000 --maxPerDeg 2 --numDeg 100 
```
```
  ./mainEDS-GEN --type R --outputName intensive --totSize 1000  
```