#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "SharedText.h"
#include "stdio.h"

#define size_t std::size_t


SharedText::SharedText(const char *text, size_t length, bool move) {
    this->size = sizeof(char) * length + 1;
    if (!move) {
        this->data = (char *) malloc(size * sizeof(char));
        memcpy(this->data, text, this->size - 1);
    } else {
        this->data = (char *) text;
    }
    this->data[size - 1] = 0;
}

SharedText::~SharedText() {
    free(data);
}

SharedTextARC SharedText::BuildSharedText(const char *text, size_t length, bool move) {
    auto shared_text = new SharedText(text, length, move);
    return SharedTextARC(shared_text);
}

void SharedText::TextToStrings() {
    for (size_t i = 0; i < this->size; ++i) {
        if (data[i] == '\n') {
            data[i] = 0;
        }
    }

}

void SharedText::StringsToText() {
    for (size_t i = 0; i < this->size; ++i) {
        if (data[i] == 0) {
            data[i] = '\n';
        }
    }
}

size_t SharedText::GetSize() {
    return this->size;
};

SharedTextARC::SharedTextARC(SharedText *text) {
    this->text = text;
    this->counter = new std::atomic<size_t>(1);

    size_t strings_counter = 0;
    for (size_t i = 0; i < text->size; ++i) {
        if (text->data[i] == '\n') {
            ++strings_counter;
        }
    }
    this->strings_num = ++strings_counter;

    this->strings.reserve(this->strings_num);
    this->strings.push_back(text->data);
    for (size_t data_i = 0; data_i < text->size; ++data_i) {
        if (text->data[data_i] == '\n') {
            this->strings.push_back(&text->data[data_i + 1]);
        }
    }
    text->TextToStrings();
}

SharedTextARC::SharedTextARC(const SharedTextARC &obj) : strings(obj.strings) {
    this->counter = obj.counter;
    ++(*this->counter);
    this->text = obj.text;
    this->strings_num = obj.strings_num;
    this->strings = obj.strings;
}

SharedTextARC::~SharedTextARC() {
    if (--(*this->counter) == 0) {
        delete this->counter;
        delete this->text;
    };
}


const char *SharedTextARC::GetText() {
    return this->text->data;
}

size_t SharedTextARC::GetTextSize() {
    return this->text->size;
};

void SharedTextARC::TextToStrings() {
    this->text->TextToStrings();
}

void SharedTextARC::StringsToText() {
    this->text->StringsToText();
}