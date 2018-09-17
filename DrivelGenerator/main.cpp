#include <iostream>
#include <fstream>
#include <assert.h>
#include "SharedText.h"

char* read_file(const char* filename, size_t* size) {
    std::ifstream file;
    file.open (filename, std::ios::in | std::ios::binary | std::ios::ate);
    assert(file.is_open());
    assert(file.tellg() >= 0);
    *size = (size_t)file.tellg();

    file.seekg(0);
    char* buffer = (char*) malloc(*size);
    file.read(buffer, *size);

    assert(file);
    file.close();

    return buffer;
}

int main() {
    size_t size;
    char* buffer = read_file(".input", &size);
    auto text_arc = SharedText::BuildSharedText(buffer, size, false);

    free(buffer);

    return 0;
}