#include "DrivelGenerators.h"

void generate_dict(const char *filename, SharedTextARC &text_arc) {
    assert(&text_arc);
    std::sort(text_arc.strings.begin(), text_arc.strings.end(), [](const char *one, const char *other) {
        return strcmp(one, other) < 0;
    });

    write_file(filename, text_arc);
}

bool pass_sym(const char *str, long long *ind, std::vector<char> &extra_symbols) {
    assert(&extra_symbols);
    if (std::find(extra_symbols.begin(),
                  extra_symbols.end(),
                  str[*ind]) != extra_symbols.end()) {
        --*ind;
        return true;
    };
    return false;
}

void generate_rhyme(const char *filename, SharedTextARC &text_arc) {
    std::sort(text_arc.strings.begin(), text_arc.strings.end(), [](const char *one, const char *other) {
        size_t one_len = strlen(one);
        size_t other_len = strlen(other);
        const char *rev_one = &one[one_len == 0 ? 0 : one_len - 1];
        const char *rev_other = &other[other_len == 0 ? 0 : other_len - 1];

        if (rev_other == other) {
            return false;
        };
        if (rev_one == one) {
            return true;
        }

        std::vector<char> extra_characters = {',', '.', '-', '!', '?', '+'};

        for (long long i = 0, k = 0;; --i, --k) {
            if (pass_sym(rev_other, &k, extra_characters)) {
                if (&rev_other[k] == other) {
                    return false;
                }
                continue;
            }
            if (pass_sym(rev_one, &i, extra_characters)) {
                if (&rev_one[i] == one) {
                    return true;
                }
                continue;
            }

            if (rev_one[i] < rev_other[k]) {
                return true;
            } else if (rev_one[i] > rev_other[k]) {
                return false;
            };

            if (&rev_one[i] == one) {
                return true;
            }
            if (&rev_other[k] == other) {
                return false;
            }
        }
    });

    write_file(filename, text_arc);
}

void generate_origin(const char *filename, SharedTextARC &text_arc) {
    assert(&text_arc);
    write_file(filename, text_arc);
}