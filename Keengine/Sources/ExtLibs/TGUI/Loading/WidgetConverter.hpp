/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2015 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_WIDGET_CONVERTER_HPP
#define TGUI_WIDGET_CONVERTER_HPP


#include "../Widget.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Implicit converter for widgets returned by the load function of the theme
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API WidgetConverter
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Construct the converter from the widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        explicit WidgetConverter(Widget::Ptr widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve the widget without casting when required
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        operator Widget::Ptr();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Cast the widget to the required type
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <class T>
        operator std::shared_ptr<T>()
        {
            std::shared_ptr<T> result = std::dynamic_pointer_cast<T>(m_widget);

            if (result == nullptr)
                throw Exception{"Value returned by Theme::load must match type of variable!"};

            return result;
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:
        Widget::Ptr m_widget;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_WIDGET_CONVERTER_HPP
