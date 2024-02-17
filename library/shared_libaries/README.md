# Creating shared libraries on linux

## Compilie source files to object file
```bash
g++ -fpic -c foo.cpp -o foo.o
g++ -fpic -c bar.cpp -o bar.o
```
### Flags
- `-fpic` Tells compilier to create position independent code. Use `-fPIC` instead if not compiling 
- `-c` Tells compilier to skip linking stage. i.e. Compilie to object file we will link later

## Link object files to shared object
```bash
g++ -fpic -shared foo.o bar.o -Wl,-soname,libexample.so.0 -o libexample.so.0.0.0
```

### Flags
- `-fpic` Same as above
- `-shared` Tells compilier to compilie to a shared object
- `-Wl,-soname,` Tells compilier to append a soname to the shared object, which defines the major version of the shared library.

## Create symbolic link to shared object
```bash
ln -s libexample.so.0.0.0 libexample.so.0
ln -s libexample.so.0 libexample.so
```

NOTE: The first created link should be the soname

## Compilie program to use library
```bash
g++ -I path/to/headers -L path/to/lib app.cpp -o app.bin -l example
```

## Change env var
```bash
export LD_LIBRARY_PATH="/absolute/path/to/soname:$LD_LIBRARY_PATH"
```

Now you can execute `app.bin`

NOTE: Because of the symbolic links, you can recompilie(update) the shared library without users of the library 
needing to recompilie their program.

