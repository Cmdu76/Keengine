#ifndef KE_SHAPECOMPONENT_HPP
#define KE_SHAPECOMPONENT_HPP

#include "../Core/SceneComponent.hpp"

#include <SFML/Graphics/ConvexShape.hpp>

namespace ke
{

class ShapeComponent : public SceneComponent
{
	public:
		typedef std::shared_ptr<ShapeComponent> Ptr;

		TYPE(ShapeComponent)

		ShapeComponent(Actor& actor);

		void setPointCount(std::size_t points);
		std::size_t getPointCount() const;

		void setPoint(std::size_t index, sf::Vector2f const& point);
		sf::Vector2f getPoint(std::size_t index) const;

		void setOutlineThickness(float thickness);
		float getOutlineThickness() const;

		void setOutlineColor(sf::Color const& color);
		sf::Color getOutlineColor() const;

		void setFillColor(sf::Color const& color);
		sf::Color getFillColor() const;

		sf::FloatRect getLocalBounds();
		sf::FloatRect getGlobalBounds();

		virtual void serialize(Serializer& serializer);
		virtual bool deserialize(Serializer& serializer, const std::string& identifier);

	private:
		virtual void renderCurrent(sf::RenderTarget& target, sf::RenderStates states);

	private:
		sf::ConvexShape mShape;
};

} // namespace ke

#endif // KE_SHAPECOMPONENT_HPP
