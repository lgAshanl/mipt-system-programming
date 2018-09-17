#include "atomic"

#ifndef DRIVELGENERATOR_SHAREDTEXT_H
#define DRIVELGENERATOR_SHAREDTEXT_H
#endif //DRIVELGENERATOR_SHAREDTEXT_H
#define usize std::size_t

class SharedTextARC;

class SharedText {
    friend class SharedTextARC;

public:
    SharedText() = delete;

    SharedText &operator=(SharedText &other) = delete;

    static SharedTextARC BuildSharedText(const char *text, usize length, bool move);

private:
    explicit SharedText(const char *text, usize length, bool move);

    void TextToStrings();

    void StringsToText();

    ~SharedText();

private:
    char *data;
    usize size;
};

class SharedTextARC {
    friend class SharedText;

public:
    SharedTextARC() = delete;

    SharedTextARC(const SharedTextARC &obj);

    ~SharedTextARC();

private:
    explicit SharedTextARC(SharedText *text);

public:
    SharedText *text;
    std::atomic<usize> *counter;
    char **strings;
    usize strings_num;
};

