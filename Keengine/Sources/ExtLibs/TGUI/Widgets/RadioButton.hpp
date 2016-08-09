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


#ifndef TGUI_RADIO_BUTTON_HPP
#define TGUI_RADIO_BUTTON_HPP


#include "Label.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    class RadioButtonRenderer;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Radio button widget
    ///
    /// Signals:
    ///     - Checked
    ///         * Optional parameter bool: always contains true
    ///         * Uses Callback member 'checked'
    ///
    ///     - Unchecked
    ///         * Optional parameter bool: always contains false
    ///         * Uses Callback member 'checked'
    ///
    ///     - Inherited signals from ClickableWidget
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API RadioButton : public ClickableWidget
    {
    public:

        typedef std::shared_ptr<RadioButton> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const RadioButton> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        RadioButton();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another radio button
        ///
        /// @param radioButton  The other radio button
        ///
        /// @return The new radio button
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static RadioButton::Ptr copy(RadioButton::ConstPtr radioButton);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        ///
        /// @return Reference to the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::shared_ptr<RadioButtonRenderer> getRenderer() const
        {
            return std::static_pointer_cast<RadioButtonRenderer>(m_renderer);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the position of the widget
        ///
        /// This function completely overwrites the previous position.
        /// See the move function to apply an offset based on the previous position instead.
        /// The default position of a transformable widget is (0, 0).
        ///
        /// @param position  New position
        ///
        /// @see move, getPosition
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setPosition(const Layout2d& position) override;
        using Transformable::setPosition;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the radio button.
        ///
        /// @param size  The new size of the radio button
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(const Layout2d& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the full size of the radio button.
        ///
        /// @return Full size of the radio button
        ///
        /// The returned size includes the text next to the radio button.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getFullSize() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the font of the text in the widget.
        ///
        /// @param font  The new font.
        ///
        /// When you don't call this function then the font from the parent widget will be used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setFont(const Font& font) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Checks the radio button.
        ///
        /// It will tell its parent to uncheck all the other radio buttons.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void check();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Unchecks the radio button
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void uncheck();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the radio button is checked or not.
        ///
        /// @return Is the radio button checked?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isChecked() const
        {
            return m_checked;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text of the radio button.
        ///
        /// @param text  The new text to draw next to the radio button.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setText(const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the text of the radio button.
        ///
        /// @return The text that is drawn next to the radio button.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getText() const
        {
            return m_text.getText();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the character size of the text.
        ///
        /// @param size  The new text size.
        ///              When the size is set to 0 then the text is auto-sized.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int size);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the character size of the text.
        ///
        /// @return Character size of the text
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTextSize() const
        {
            return m_text.getTextSize();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Allow (or disallow) the radio button to be checked/unchecked by clicking on the text next to the radio button.
        ///
        /// @param acceptTextClick  Will clicking on the text trigger a checked/unchecked event?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void allowTextClick(bool acceptTextClick = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the opacity of the widget.
        ///
        /// @param opacity  The opacity of the widget. 0 means completely transparent, while 1 (default) means fully opaque.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setOpacity(float opacity) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(float x, float y) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMouseReleased(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void keyPressed(const sf::Event::KeyEvent& event) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void widgetFocused() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Reload the widget
        ///
        /// @param primary    Primary parameter for the loader
        /// @param secondary  Secondary parameter for the loader
        /// @param force      Try to only change the looks of the widget and not alter the widget itself when false
        ///
        /// @throw Exception when the connected theme could not create the widget
        ///
        /// When primary is an empty string the built-in white theme will be used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void reload(const std::string& primary = "", const std::string& secondary = "", bool force = false) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr clone() const override
        {
            return std::make_shared<RadioButton>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when the mouse enters the widget. If requested, a callback will be send.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseEnteredWidget() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when the mouse leaves the widget. If requested, a callback will be send.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseLeftWidget() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        // This is the checked flag. When the radio button is checked then this variable will be true.
        bool m_checked = false;

        // When this boolean is true (default) then the radio button will also be checked by clicking on the text.
        bool m_allowTextClick = true;

        // This will contain the text that is written next to radio button.
        Label m_text;

        // This will store the size of the text ( 0 to auto size )
        unsigned int m_textSize = 0;

        friend class RadioButtonRenderer;
        friend class CheckBoxRenderer;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API RadioButtonRenderer : public WidgetRenderer, public WidgetPadding
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructor
        ///
        /// @param radioButton  The radio button that is connected to the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        RadioButtonRenderer(RadioButton* radioButton) : m_radioButton{radioButton} {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Change a property of the renderer
        ///
        /// @param property  The property that you would like to change
        /// @param value     The new serialized value that you like to assign to the property
        ///
        /// @throw Exception when deserialization fails or when the widget does not have this property.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setProperty(std::string property, const std::string& value) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Change a property of the renderer
        ///
        /// @param property  The property that you would like to change
        /// @param value     The new value that you like to assign to the property.
        ///                  The ObjectConverter is implicitly constructed from the possible value types.
        ///
        /// @throw Exception for unknown properties or when value was of a wrong type.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setProperty(std::string property, ObjectConverter&& value) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve the value of a certain property
        ///
        /// @param property  The property that you would like to retrieve
        ///
        /// @return The value inside a ObjectConverter object which you can extract with the correct get function or
        ///         an ObjectConverter object with type ObjectConverter::Type::None when the property did not exist.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ObjectConverter getProperty(std::string property) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Get a map with all properties and their values
        ///
        /// @return Property-value pairs of the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::map<std::string, ObjectConverter> getPropertyValuePairs() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the text.
        ///
        /// @param color  New text color
        ///
        /// This color will overwrite the color for both the normal and hover state.
        ///
        /// @see setTextColorNormal
        /// @see setTextColorHover
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextColor(const Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the text in normal state (mouse not on top of the radio button).
        ///
        /// @param color  New text color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextColorNormal(const Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the text in hover state (mouse is standing on top of the radio button).
        ///
        /// @param color  New text color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextColorHover(const Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the background color.
        ///
        /// This color is ignored when checked and unchecked images are set.
        ///
        /// @param color  New background color
        ///
        /// This color can be seen as the border color. It is only visible when there is some padding.
        ///
        /// This color will overwrite the color for both the normal and hover state.
        ///
        /// @see setBackgroundColorNormal
        /// @see setBackgroundColorHover
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBackgroundColor(const Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the background color in normal state (mouse is not on top of the radio button).
        ///
        /// This color is ignored when checked and unchecked images are set.
        ///
        /// @param color  New background color
        ///
        /// This color can be seen as the border color. It is only visible when there is some padding.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBackgroundColorNormal(const Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the background color in hover state (mouse is standing on top of the radio button).
        ///
        /// This color is ignored when checked and unchecked images are set.
        ///
        /// @param color  New background color
        ///
        /// This color can be seen as the border color. It is only visible when there is some padding.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBackgroundColorHover(const Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the foreground color.
        ///
        /// This color is ignored when checked and unchecked images are set.
        ///
        /// @param color  New foreground color
        ///
        /// This color is drawn on top of the background color, but it does not overdraw it completely when padding is set.
        /// When there is padding, the background color will thus serve as the border color.
        ///
        /// This color will overwrite the color for both the normal and hover state.
        ///
        /// @see setForegroundColorNormal
        /// @see setForegroundColorHover
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setForegroundColor(const Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the foreground color in normal state (mouse is not on top of the radio button).
        ///
        /// This color is ignored when checked and unchecked images are set.
        ///
        /// @param color  New foreground color
        ///
        /// This color is drawn on top of the background color, but it does not overdraw it completely when padding is set.
        /// When there is padding, the background color will thus serve as the border color.
        ///
        /// This color will overwrite the color for both the normal and hover state.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setForegroundColorNormal(const Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the foreground color in hover state (mouse is standing on top of the radio button).
        ///
        /// This color is ignored when checked and unchecked images are set.
        ///
        /// @param color  New foreground color
        ///
        /// This color is drawn on top of the background color, but it does not overdraw it completely when padding is set.
        /// When there is padding, the background color will thus serve as the border color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setForegroundColorHover(const Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color that is used to fill the radio button when it is checked.
        ///
        /// This color is ignored when checked and unchecked images are set.
        ///
        /// @param color  New check color
        ///
        /// This color will overwrite the color for both the normal and hover state.
        ///
        /// @see setCheckColorNormal
        /// @see setCheckColorHover
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCheckColor(const Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color that is used to fill the radio button when it is checked (mouse is not on radio button).
        ///
        /// This color is ignored when checked and unchecked images are set.
        ///
        /// @param color  New check color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCheckColorNormal(const Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color that is used to fill the radio button when it is checked (mouse is on top of radio button).
        ///
        /// This color is ignored when checked and unchecked images are set.
        ///
        /// @param color  New check color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCheckColorHover(const Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Change the image that is displayed when the checkbox is not checked.
        ///
        /// @param texture  The new unchecked texture
        ///
        /// When checked and unchecked images are set, the background and foreground color properties will be ignored.
        /// Pass an empty string to unset the image.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setUncheckedTexture(const Texture& texture);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Change the image that is displayed when the checkbox is checked.
        ///
        /// @param texture  The new checked texture
        ///
        /// When checked and unchecked images are set, the background and foreground color properties will be ignored.
        /// Pass an empty string to unset the image.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCheckedTexture(const Texture& texture);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Change the image that is displayed when the checkbox is not checked and the mouse is on top of the checkbox.
        ///
        /// @param texture  The new unchecked hover texture
        ///
        /// This only has effect when the normal checked and unchecked images are also set.
        /// Pass an empty string to unset the image.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setUncheckedHoverTexture(const Texture& texture);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Change the image that is displayed when the checkbox is checked and the mouse is on top of the checkbox.
        ///
        /// @param texture  The new checked hover texture
        ///
        /// This only has effect when the normal checked and unchecked images are also set.
        /// Pass an empty string to unset the image.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCheckedHoverTexture(const Texture& texture);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Change the image that is displayed on top of the checkbox when it is focused.
        ///
        /// @param texture  The new checked hover texture
        ///
        /// This only has effect when the normal checked and unchecked images are also set.
        /// Pass an empty string to unset the image.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setFocusedTexture(const Texture& texture);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::shared_ptr<WidgetRenderer> clone(Widget* widget) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        RadioButton* m_radioButton;

        Texture m_textureUnchecked;
        Texture m_textureChecked;
        Texture m_textureUncheckedHover;
        Texture m_textureCheckedHover;
        Texture m_textureFocused;

        sf::Color m_textColorNormal;
        sf::Color m_textColorHover;

        sf::Color m_backgroundColorNormal;
        sf::Color m_backgroundColorHover;

        sf::Color m_foregroundColorNormal;
        sf::Color m_foregroundColorHover;

        sf::Color m_checkColorNormal;
        sf::Color m_checkColorHover;

        friend class RadioButton;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_RADIO_BUTTON_HPP
