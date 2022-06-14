# my-ppmptd
Compile-time parsing of `__TIME__` and `__DATE__` macros into numerical tokens.

## Why my-ppmptd
Why did I create my preprocessor metaprogramming `__TIME__` and `__DATE__` library? To parse `__TIME__` and `__DATE__` to obtain the temporal information they contain at compile-time.

For what purpose? Preprocessor metaprogramming using time and date.

Isn't this really impractical? Yes. But imagine the confusion on the face of someone reading `#include __DATE__` somewhere in your code.

Why release this library? Because I've been sitting on it since 2017 and no one seems to have come up with something similar since then.

## How to use the my-ppmptd
Compressed variants of the library are available. This should help users use the library between now and when Linux becomes supported by the generator. Otherwise, the code generator is currently supported on Windows (see OS compatibility list). 

It is recommended that mechanical storage devices (HDD) users use the `assert` variant/mode as it offloads the processing to the preprocessor. Solid state drive (SSD) users can use the `3_6M_files` variant, as it offloads processessing to the file system, though at the cost of storage space.

### For compressed library download
1. Uncompress the library
2. Uncompress `date.h` and `time.h` in a search directory
3. If using the `3_6M_files` variant, have `my_ppmptd/date/` **as** an extra search directory

### For code generator use
Generate the code (see call syntax) directly in a search directory

**Note:** 
- HDD performance have not been tested
- On `3_6M_files` mode with an SSD, code generation can take from one hour to quite a bit more than one hour. HDD users ought to take the day off

Call syntax:
  ```
  my_ppmp.exe <lib-path> <mode>
  
  <lib-path> :: <path>
    
  <mode> :: assert | 3_6M_files
  ```
  Where
    `<lib-path>` is the path to the directory you wish to generate the files into.
    `<mode>` is the parser for `__DATE__`. Due to techincal limitations, there is currently no parser choice of `__TIME__`. 
  
Assertion parsers use gcc's `#assert` directive to produce predicates to match on string literals. This is the slowest of the two parser as the preprocessor can be slow at interpretting those.

File name parsers (ab)use the file system with the deceptively simple `#include __DATE__` as only requirement to call. This parser is as fast as the slowest part of the files system/storage hardware. Qualitative tests have been run on an SSD, and it is quite fast. Compilation of trivial programs calling upon the file name `__DATE__` parser complete under a second. 

**Important notes:**
- If the `__DATE__` file name parser is used, an include path must be added to its directory. Using the `-idirafter` option is recommended.
- In `3_6M_files` mode, the generator will produces a `__DATE__` parser of 3.6 million files in a single directory. This is done to reduce the number of search directories. The creation of such files can be interrupted with `Ctrl`+`C`.

### Macros defined by the parsers
- `MY_PPMPTD_TIME_SECONDS`
- `MY_PPMPTD_TIME_MINUTES`
- `MY_PPMPTD_TIME_HOURS`
- `MY_PPMPTD_DATE_DAY`
- `MY_PPMPTD_DATE_MONTH`
- `MY_PPMPTD_DATE_YEAR`

OS compatibility list:
- Windows 10 (other versions TBD)

Compiler compatibility list:
- gcc 8.1 (other versions TBD)
