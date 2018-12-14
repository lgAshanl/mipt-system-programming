#ifndef TOPCOMP_DIEHARDSTACK_H
#define TOPCOMP_DIEHARDSTACK_H

#endif //TOPCOMP_DIEHARDSTACK_H

#include <cmath>
//#include "math.h"
#include <cstring>
#include <limits>
#include <openssl/md5.h>
#include <assert.h>
#include <algorithm>
#include <signal.h>
#include <iostream>

#ifndef DIEHARDSTACK_DIEHARDSTACK_H
#define DIEHARDSTACK_DIEHARDSTACK_H

#endif //DIEHARDSTACK_DIEHARDSTACK_H

#define INIT_CAPACITY 2

template<class D>
struct PoisonGuard {
    double nan = std::numeric_limits<double>::quiet_NaN();
    D data;

    PoisonGuard() {};

    explicit PoisonGuard(D data) : data(data) {};

    bool operator==(const PoisonGuard<D> &other) const {
        return data == other.data;
    }
};

template<class T>
class DieHardStack {
public:
    DieHardStack();

    ~DieHardStack();

    bool isValid();

    bool isEmpty();

    bool push(T element);

    T pop();

    T top();

    void print();

private:
    void validate();

private:
    PoisonGuard<T *> data;
    PoisonGuard<std::size_t> size;
    PoisonGuard<std::size_t> capacity;
    PoisonGuard<unsigned char[MD5_DIGEST_LENGTH]> hash;
    double poison_guard = std::numeric_limits<double>::signaling_NaN();
};

template<class T>
DieHardStack<T>::DieHardStack(): size(0), capacity(INIT_CAPACITY), hash(),
                                 data((T *) malloc(INIT_CAPACITY * sizeof(T))) {
    MD5((unsigned char *) this, sizeof(*this) - sizeof(double) - sizeof(hash), hash.data);
}

template<class T>
DieHardStack<T>::~DieHardStack() {
    free(data.data);
}

template<class T>
bool DieHardStack<T>::isValid() {
    unsigned char hash[MD5_DIGEST_LENGTH];
    MD5((unsigned char *) this, sizeof(*this) - sizeof(double) - sizeof(this->hash), hash);
    assert(this->data.nan != this->data.nan);
    assert(this->poison_guard != this->poison_guard);
    return std::equal(hash, hash + MD5_DIGEST_LENGTH, this->hash.data);
}

template<class T>
void DieHardStack<T>::validate() {
    MD5((unsigned char *) this, sizeof(*this) - sizeof(double) - sizeof(this->hash), hash.data);
}

template<class T>
bool DieHardStack<T>::isEmpty() {
    assert(isValid());
    return size.data == 0;
}

template<class T>
// return true, if it was resized
bool DieHardStack<T>::push(T element) {
    assert(isValid());
    bool is_resized = false;
    if (size == capacity) {
        data.data = (T *) realloc(data.data, capacity.data <<= 1);
        assert(data.data != nullptr);
        is_resized = true;
    }

    data.data[size.data++] = element;
    validate();
    return is_resized;
}

template<class T>
T DieHardStack<T>::pop() {
    assert(isValid());
    if (isEmpty()) {
        std::cerr << "pop of empty DieHardStack" << std::endl;
        raise(SIGSEGV);
    }

    --size.data;
    validate();

    return data.data[size.data];
}

template<class T>
T DieHardStack<T>::top() {
    assert(isValid());
    if (isEmpty()) {
        std::cerr << "top of empty DieHardStack" << std::endl;
        raise(SIGSEGV);
    }
    validate();

    return data.data[size.data-1];
}

template<class T>
void DieHardStack<T>::print() {
    printf(">DieHardStack debug output:\n"
           "--> size: %ld\n"
           "--> capacity: %ld\n"
           "--> data_ptr: %p\n",
           this->size.data, this->capacity.data, this->data.data);
    for (int i = 0; i < size.data; ++i) {
        printf("%lf ", data.data[i]);
    }
    printf("\n");
}
