#pragma once

#include <halley/maths/vector2.h>
#include <halley/maths/rect.h>
#include <halley/maths/colour.h>
#include <halley/maths/vector4.h>
#include "halley/data_structures/maybe.h"

namespace Halley
{
	class Resources;
	class SpriteSheetEntry;
	class SpriteSheet;
	class Material;
	class Texture;
	class MaterialDefinition;
	class Painter;

	struct SpriteVertexAttrib
	{
		// This structure must match the layout of the shader
		// See shared_assets/material/sprite_base.yaml for reference
		Vector4f vertPos;
		Vector2f pos;
		Vector2f pivot;
		Vector2f size;
		Vector2f scale;
		Colour4f colour;
		Rect4f texRect;
		float rotation = 0;
		float textureRotation = 0;
		char _padding[8];
	};

	class Sprite
	{
	public:
		Sprite();

		void draw(Painter& painter) const;
		void drawNormal(Painter& painter) const;
		void drawSliced(Painter& painter) const;
		void drawSliced(Painter& painter, Vector4s slices) const;
		static void draw(const Sprite* sprites, size_t n, Painter& painter);

		Sprite& setMaterial(Resources& resources, String materialName = "");
		Sprite& setMaterial(std::shared_ptr<Material> m);
		Material& getMaterial() const { return *material; }
		bool hasMaterial() const { return material != nullptr; }

		Sprite& setImage(Resources& resources, String imageName, String materialName = "");
		Sprite& setImage(std::shared_ptr<const Texture> image, std::shared_ptr<const MaterialDefinition> material);
		Sprite& setImageData(const Texture& image);

		Sprite& setSprite(Resources& resources, String spriteSheetName, String imageName, String materialName = "");
		Sprite& setSprite(const SpriteSheet& sheet, String name);
		Sprite& setSprite(const SpriteSheetEntry& entry, bool applyPivot = true);

		Sprite& setPos(Vector2f pos);
		Sprite& setPosition(Vector2f pos);
		Vector2f getPosition() const;

		Sprite& setPivot(Vector2f pivot);
		Sprite& setAbsolutePivot(Vector2f pivot);

		Sprite& setRotation(Angle1f angle);

		Sprite& setSize(Vector2f size);
		Sprite& setScale(Vector2f scale);
		Sprite& setScale(float scale);
		Sprite& scaleTo(Vector2f size);
		Vector2f getSize() const;
		Vector2f getScale() const;
		Vector2f getScaledSize() const;
		Vector2f getRawSize() const;

		Sprite& setFlip(bool flip);
		bool isFlipped() const;

		Sprite& setColour(Colour4f colour);
		Colour4f getColour() const;

		Sprite& setTexRect(Rect4f texRect);

		Sprite& setSliced(Vector4s slices);
		Sprite& setNotSliced();

		Sprite& setVisible(bool visible);
		bool isVisible() const;

		Sprite& setClip(Rect4f clip);
		Sprite& setClip();
		Maybe<Rect4f> getClip() const;

		Rect4f getAABB() const;
		bool isInView(Rect4f rect) const;

		Vector4s getOuterBorder() const;
		Sprite& setOuterBorder(Vector4s border);

		Sprite clone() const;

	private:
		std::shared_ptr<Material> material;
		SpriteVertexAttrib vertexAttrib;

		Vector2f size;
		Vector4s slices;
		Vector4s outerBorder;
		Maybe<Rect4f> clip;
		bool visible = true;
		bool flip = false;
		bool sliced = false;

		void computeSize();
	};
}
