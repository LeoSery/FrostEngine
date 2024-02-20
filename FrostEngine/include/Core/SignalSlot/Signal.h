#pragma once

#include "Core/SignalSlot/Slot.h"

#include <vector>

namespace frost::core
{
    template <typename ...Args>
    class Signal
    {
    public:

        //Disabling default constructors
        Signal(const Signal&) = delete;
        Signal(Signal&&) = delete;
        Signal& operator=(const Signal&) = delete;

        //Constructor and Destructors
        Signal() = default;
        ~Signal() = default;

        //Methods
        void Connect(Slot<Args...>& _Slot);
        void Disconnect(Slot<Args...>& _Slot);
        void Disconnect();
        void Emit(Args&&... _Parameters);

        //Operators
        void operator()(Args&&... _Parameters);

    private:
        std::vector<Slot<Args...>*> m_connectedSlots;
    };
}

#include "Core/SignalSlot/Signal.hxx"