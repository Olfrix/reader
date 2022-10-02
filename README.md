```
______               _           
| ___ \             | |          
| |_/ /___  __ _  __| | ___ _ __ 
|    // _ \/ _` |/ _` |/ _ \ '__|
| |\ \  __/ (_| | (_| |  __/ |   
\_| \_\___|\__,_|\__,_|\___|_|   
                                 
```
### Requirements
`cmake >=3.21, c++20 (gcc >=8 or clang >=10), ninja, clang-format, python3`
### Build
The script performs clean build of 2 build types: debug (`./debug_build`) and release (`./release_build/`)  
`cd scripts/ && ./build.sh`
### Generate input
The script will generate a file with 100'000 unique words of a size at least the specified value (in MB)   
`python3 ./scripts/generate.py <size_in_MB>`
### Run
Debug version (-Og):  
`./debug_build/reader <path_to_input_file>`  
Release version (-O3):  
`./release_build/reader <path_to_input_file>`  
### Format code
`find . -regex '.*\.\(cpp\|h\)' -exec clang-format -style=file -i {} \;`  
### Run tests
`./<build_type>_build/ctest --output-on-failure`  
### Measure performance
`/usr/bin/time --verbose ./release_build/reader <path_to_input_file>`  