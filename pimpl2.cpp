#include <iostream>
#include "pimpl2.h"

class PeerManagerImpl final : public PeerManager {
    int m_best_height;

public:
    PeerManagerImpl(int ctor_int);
    // why doesn't dtor need to be defined? parent class says virtual

    void SetBestHeight(int height) override {
        m_best_height = height;
        std::cout << "setting m_best_height to " << height << std::endl;
    };
};

std::unique_ptr<PeerManager> PeerManager::make(int caller_int)
{
    return std::make_unique<PeerManagerImpl>(caller_int);
}

PeerManagerImpl::PeerManagerImpl(int ctor_int)
    : m_best_height(ctor_int)
{
    std::cout << "impl ctor, m_best_height: " << ctor_int << std::endl;
}

int main() {
    auto peerman = PeerManager::make(3);
    peerman->SetBestHeight(4);

    return 0;
}
