#include <iostream>

class TxRequestTracker {
    class Impl;
    const std::unique_ptr<Impl> m_impl;

public:
    TxRequestTracker(int i);
    ~TxRequestTracker();

    void Count(int peer_id) const;
};
