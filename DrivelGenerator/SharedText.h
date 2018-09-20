#include "atomic"
#include "vector"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "assert.h"

#ifndef DRIVELGENERATOR_SHAREDTEXT_H
#define DRIVELGENERATOR_SHAREDTEXT_H
#endif //DRIVELGENERATOR_SHAREDTEXT_H

class SharedTextARC;

//-----------------------------------------------------------------------------------
//! SharedText
//! realisation of shared text with swapable lines
//! is provided as a rust-like Arc to SharedText
//!
//! !Build with Shared::BuildSharedText
//!
//! @param [in] char* text - input text
//! @param [in] size_t length - length of text
//! @param [in] bool move - if true move text, else copy
//!
//! @return SharedTextARC
// ---------------------------------------------------------------------------------

class SharedText {
    friend class SharedTextARC;

public:
    SharedText() = delete;

    SharedText &operator=(SharedText &other) = delete;

    size_t GetSize();

    static SharedTextARC BuildSharedText(const char *text, size_t length, bool move);

private:
    explicit SharedText(const char *text, size_t length, bool move);

    void TextToStrings();

    void StringsToText();

    ~SharedText();

private:
    char *data;
    size_t size;
};

struct String {
    char *date;
    size_t size;
};

class SharedTextARC {
    friend class SharedText;

public:
    SharedTextARC() = delete;

    SharedTextARC(const SharedTextARC &obj);

    size_t GetTextSize();

    ~SharedTextARC();

    const char *GetText();

    void TextToStrings();

    void StringsToText();

private:
    explicit SharedTextARC(SharedText *text);

public:
    std::vector<String> strings;
    size_t strings_num;

private:
    SharedText *text;
    std::atomic<size_t> *counter;
};