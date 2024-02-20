#pragma once

#include "Core/SignalSlot/Signal.h"

namespace frost::core
{
    template<typename ...Args>
    inline void Signal<Args...>::Connect(Slot<Args...>& _Slot)
    {
        m_connectedSlots.push_back(&_Slot);
    }

    template<typename ...Args>
    inline void Signal<Args...>::Disconnect(Slot<Args...>& _Slot)
    {
        for (auto it = m_connectedSlots.begin(); it != m_connectedSlots.end(); )
        {
            if (*it == _Slot)
                it = m_connectedSlots.erase();
            else ++it;
        }
    }

    template<typename ...Args>
    inline void Signal<Args...>::Disconnect()
    {
        m_connectedSlots.clear();
    }

    template<typename ...Args>
    inline void Signal<Args...>::Emit(Args&&... _Parameters)
    {
        for (auto& element : m_connectedSlots)
            (*element)(std::forward<Args>(_Parameters)...);
    }

    template<typename ...Args>
    inline void Signal<Args...>::operator()(Args&&... _Parameters)
    {
        Emit(std::forward<Args>(_Parameters)...);
    }
}
