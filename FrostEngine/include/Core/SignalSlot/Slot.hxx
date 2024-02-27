#pragma once

#include "Core/SignalSlot/Slot.h"

namespace frost::core
{
    template<typename ...Args>
    inline Slot<Args...>::Slot() : m_init(false)
    {

    }

    template<typename ...Args>
    inline Slot<Args...>::Slot(const std::function<void(Args...)>& _Callback) : m_init(true), m_callback(_Callback)
    {

    }

    template<typename ...Args>
    inline void Slot<Args...>::operator()(Args&&... _Parameters)
    {
        this->call(std::forward<Args>(_Parameters)...);
    }

    template<typename ...Args>
    inline void Slot<Args...>::call(Args&&... _Parameters)
    {
        if (m_init)
            m_callback(std::forward<Args>(_Parameters)...);
    }

    template<typename ...Args>
    inline void Slot<Args...>::setSlotFunction(std::function<void(Args...)> _Callback)
    {
        m_init = true;
        m_callback = _Callback;
    }
}
