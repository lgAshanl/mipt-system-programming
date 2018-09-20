#include "FileTools.h"

char *read_file(const char *filename, size_t *size) {
    assert(size != nullptr);

    std::ifstream file;
    file.open(filename, std::ios::in | std::ios::binary | std::ios::ate);
    assert(file.is_open());
    assert(file.tellg() >= 0);
    *size = (size_t) file.tellg();

    file.seekg(0, std::ios::beg);
    char *buffer = (char *) malloc(*size);
    file.read(buffer, *size);

    assert(file);
    file.close();

    return buffer;
}

void write_file(const char *filename, SharedTextARC &text_arc) {
    assert(&text_arc);

    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);
    assert(file.is_open());

    char *buffer = (char *) calloc(text_arc.GetTextSize(), sizeof(char));
    char *local_buf = buffer;
    for (auto i = text_arc.strings.begin(); i != text_arc.strings.end(); ++i) {
        memcpy(local_buf, i.base()->date, i.base()->size);
        local_buf += i.base()->size;
        *local_buf = '\n';
        ++local_buf;
    }
    buffer[text_arc.GetTextSize() - 1] = 0;

    file.write(buffer, text_arc.GetTextSize() - 1);
    assert(file);

    free(buffer);
    file.close();
}