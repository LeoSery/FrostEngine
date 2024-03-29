#pragma once

/*!
* \file Signal.hxx
* 
* \brief Templated implementation of the 'Signal' class.
*/

#include "Core/SignalSlot/Signal.h"

namespace frost::core
{
    /*!
    * \brief Connects a slot to the signal.
    * 
    * \param _Slot The slot to connect to the signal.
    * 
    * \fn void Signal::Connect(Slot& _Slot)
    * 
    * \details This method connects a slot to the signal passed as a parameter.
    */
    template<typename ...Args>
    inline void Signal<Args...>::Connect(Slot<Args...>& _Slot)
    {
        m_connectedSlots.push_back(&_Slot);
    }

    /*!
    * \brief Disconnects a slot from the signal.
    * 
    * \param _Slot The slot to disconnect from the signal.
    * 
    * \fn void Signal::Disconnect(Slot& _Slot)
    * 
    * \details This method disconnects a specific slot from the signal passed as a parameter.
    */
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

    /*!
    * \brief Disconnects all slots from the signal.
    * 
    * \fn void Signal::Disconnect()
    * 
    * \details This method disconnects all slots from the signal.
    */
    template<typename ...Args>
    inline void Signal<Args...>::Disconnect()
    {
        m_connectedSlots.clear();
    }

    /*!
    * \brief Emits the signal.
    * 
    * \param _Parameters The parameters to pass to the connected slots.
    * 
    * \fn void Signal::Emit(Args&&... _Parameters)
    * 
    * \details This method emits the signal, passing the parameters to the connected slots.
    */
    template<typename ...Args>
    inline void Signal<Args...>::Emit(Args&&... _Parameters)
    {
        for (auto& element : m_connectedSlots)
            (*element)(std::forward<Args>(_Parameters)...);
    }

    /*!
    * \brief Operator overload for emitting the signal.
    * 
    * \param _Parameters The parameters to pass to the connected slots.
    * 
    * \fn void Signal::operator()(Args&&... _Parameters)
    * 
    * \details This method overloads the '()' operator so that the slot can be called as a function.
    */
    template<typename ...Args>
    inline void Signal<Args...>::operator()(Args&&... _Parameters)
    {
        Emit(std::forward<Args>(_Parameters)...);
    }
}
