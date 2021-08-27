#include <iostream>
#include "pimpl.h"

class TxRequestTracker::Impl {
    int my_i;

public:
    Impl(int i) : my_i(i) {}
    ~Impl() {}

    void Count(int peer_id) const {
        auto val = (peer_id == my_i) ? "yup" : "nope";
        std::cout << val << std::endl;
    }

};

TxRequestTracker::TxRequestTracker(int i)
    : m_impl(std::make_unique<TxRequestTracker::Impl>(i)) {}

TxRequestTracker::~TxRequestTracker() = default;

void TxRequestTracker::Count(int peer_id) const { return m_impl->Count(peer_id); }

int main() {
    TxRequestTracker m_txrequest{3};
    m_txrequest.Count(8);
    m_txrequest.Count(3);

    return 0;
}
