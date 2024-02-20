#pragma once

#include "Core/SignalSlot/Slot.h"

namespace frost::core
{
    template<typename ...Args>
    inline Slot<Args...>::Slot() : m_Init(false)
    {

    }

    template<typename ...Args>
    inline Slot<Args...>::Slot(const std::function<void(Args...)>& callback) : m_Init(true), m_Callback(callback)
    {

    }

    template<typename ...Args>
    inline void Slot<Args...>::operator()(Args&&... parameters)
    {
        this->call(std::forward<Args>(parameters)...);
    }

    template<typename ...Args>
    inline void Slot<Args...>::call(Args&&... parameters)
    {
        if (m_Init)
            m_Callback(std::forward<Args>(parameters)...);
    }

    template<typename ...Args>
    inline void Slot<Args...>::setSlotFunction(std::function<void(Args...)> callback)
    {
        m_Init = true;
        m_Callback = callback;
    }
}
