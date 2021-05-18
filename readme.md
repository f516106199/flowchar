# flowchar

flowchar - a tiny tool for conversion from pseudo-code to flowchart in character format

## usage

 "Usage:"  
flowchar -c \<codePath> -o \<chartPath>  
"Options:" << std::endl;  

- -c \<path>  specify path of code to be parsed, required.

- -o \<path> specify path of chart to be emitted, optional.

mention:: the codePath's file must be ended with new line .  

## language

use fake code .  

sync:

``` c++
what ;    // ';' is necessary. 
...;

if(cond){
    ...    
}
else{   //optional 
    ...     
}
whlle(cond){
    ...     
}
```

## install  

windows  

``` bash
cd path/to/flowchar
mkdir build
cd bulid
cmake -G "Unix Makefiles" ..
cmake -DCMAKE_BUILD_TYPE=Release .. 
cmake --build .

```

unix /linux /macos

``` bash
cd path/to/flowchar
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE_release ..
cmake --build .
```

## qucikly use

certainly you can try changing diretion to bin and execute the flowchar binary file.  

but it may only work on unix/linux/macos;  
