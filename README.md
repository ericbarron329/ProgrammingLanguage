Command to run to create the .wasm from .cpp
emcc main.cpp -o wasmModule.js \                         
    -s EXPORTED_FUNCTIONS='["_processInput","_malloc","_free"]' \
    -s EXPORTED_RUNTIME_METHODS='["lengthBytesUTF8","stringToUTF8"]' \
    -s MODULARIZE=1 \
    -s 'EXPORT_NAME="createModule"'

Command to open a new local python server to vizualize page
python -m http.server 8080
