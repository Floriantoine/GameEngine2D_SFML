#pragma once
#include "types.hpp"

namespace fa::behavior {

class Behavior {
  public:
    Behavior() = default;
    ~Behavior() = default;

    virtual void Start(fa::id_t entityId);
    virtual void Update(fa::id_t entityId);
    virtual void Destroy(fa::id_t entityId);
};

} // namespace fa::behavior