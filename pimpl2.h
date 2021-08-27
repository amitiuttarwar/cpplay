#include <iostream>

class PeerManager
{
public:
    static std::unique_ptr<PeerManager> make(int ctor_int);
    virtual ~PeerManager() {}

    virtual void SetBestHeight(int height) = 0;
};
