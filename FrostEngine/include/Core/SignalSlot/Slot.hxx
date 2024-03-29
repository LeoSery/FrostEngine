#pragma once

/*!
* \file Slot.hxx
* 
* \brief Templated implementation of the 'Slot' class.
*/

#include "Core/SignalSlot/Slot.h"

/*!
* \namespace frost::core
*
* \brief The namespace for the FrostEngine core functionalities.
*/
namespace frost::core
{
    /*!
    * \brief Default constructor for the 'Slot' class.
    * 
    * \fn Slot::Slot()
    */
    template<typename ...Args>
    inline Slot<Args...>::Slot() : m_init(false)
    {

    }

    /*!
    * \brief Constructor for the 'Slot' class.
    * 
    * \fn Slot::Slot(const std::function<void(Args...)>& _Callback)
    * 
    * \param _Callback The function to be called when the slot is triggered.
    */
    template<typename ...Args>
    inline Slot<Args...>::Slot(const std::function<void(Args...)>& _Callback) : m_init(true), m_callback(_Callback)
    {

    }

    /*!
    * \brief Operator overload for the '()' operator.
    *
    * \details This method overloads the '()' operator so that the slot can be called as a function.
    * 
    * \fn void Slot::operator()(Args&&... _Parameters)
    * 
    * \param _Parameters The parameters to be passed to the slot function.
    */
    template<typename ...Args>
    inline void Slot<Args...>::operator()(Args&&... _Parameters)
    {
        this->call(std::forward<Args>(_Parameters)...);
    }

    /*!
    * \brief Calls the slot function.
    * 
    * \fn void Slot::call(Args&&... _Parameters)
    * 
    * \param _Parameters The parameters to be passed to the slot function.
    */
    template<typename ...Args>
    inline void Slot<Args...>::call(Args&&... _Parameters)
    {
        if (m_init)
            m_callback(std::forward<Args>(_Parameters)...);
    }

    /*!
    * \brief Sets the slot function.
    * 
    * \fn void Slot::setSlotFunction(std::function<void(Args...)> _Callback)
    * 
    * \param _Callback The function to be called when the slot is triggered.
    */
    template<typename ...Args>
    inline void Slot<Args...>::setSlotFunction(std::function<void(Args...)> _Callback)
    {
        m_init = true;
        m_callback = _Callback;
    }
}
