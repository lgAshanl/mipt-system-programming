#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "SharedText.h"
#include "stdio.h"

#define usize std::size_t


SharedText::SharedText(const char *text, usize length, bool move) {
    this->size = sizeof(char) * length + 1;
    if (!move) {
        this->data = (char *) malloc(size);
        memcpy(this->data, text, this->size - 1);
    } else {
        this->data = (char*)text;
    }
    this->data[size - 1] = 0;
}

SharedText::~SharedText() {
    free(data);
}

SharedTextARC SharedText::BuildSharedText(const char *text, usize length, bool move) {
    auto shared_text = new SharedText(text, length, move);
    shared_text->TextToStrings();
    return SharedTextARC(shared_text);
}

void SharedText::TextToStrings() {
    for (usize i = 0; i < this->size; ++i) {
        if (data[i] == '\n') {
            data[i] = 0;
        }
    }

}

void SharedText::StringsToText() {
    for (usize i = 0; i < this->size; ++i) {
        if (data[i] == 0) {
            data[i] = '\n';
        }
    }
}

SharedTextARC::SharedTextARC(SharedText *text) {
    this->text = text;
    this->counter = new std::atomic<usize>(1);

    usize strings_counter = 0;
    for (usize i = 0; i < text->size; ++i) {
        if (text->data[i] == '\n') {
            ++strings_counter;
        }
    }
    this->strings_num = ++strings_counter;

    this->strings = (char **) malloc(this->strings_num * sizeof(char *));
    this->strings[0] = text->data;
    for (usize str_i = 0, data_i = 0; data_i < text->size; ++data_i) {
        if (text->data[data_i] == '\n') {
            this->strings[++str_i] = &text->data[data_i + 1];
        }
    }
}

SharedTextARC::SharedTextARC(const SharedTextARC &obj) {
    this->counter = obj.counter;
    ++(*this->counter);
    this->text = obj.text;
    this->strings_num = obj.strings_num;
    memcpy(this->strings, obj.strings, obj.text->size);
}

SharedTextARC::~SharedTextARC() {
    free(this->strings);
    if (--(*this->counter) == 0) {
        delete this->counter;
        delete this->text;
    };
}



















