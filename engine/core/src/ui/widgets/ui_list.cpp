#include "ui/widgets/ui_list.h"
#include "ui/ui_style.h"
#include "ui/widgets/ui_label.h"

using namespace Halley;

UIList::UIList(const String& id, std::shared_ptr<UIStyle> style)
	: UIWidget(id, {}, UISizer(UISizerType::Vertical))
	, style(style)
{
	sprite = style->listBackground;
}

void UIList::setSelectedOption(int option)
{
	curOption = option;
}

int UIList::getSelectedOption() const
{
	return curOption;
}

void UIList::addTextItem(const String& id, const String& label)
{
	addItem(id, std::make_unique<UILabel>(style->label.clone().setText(label)));
}

void UIList::addItem(const String& id, std::shared_ptr<UIWidget> widget)
{
	add(std::make_shared<UIListItem>(id, *this, style, widget));
}

void UIList::draw(UIPainter& painter) const
{
	if (sprite.hasMaterial()) {
		painter.draw(sprite);
	}
}

void UIList::update(Time t, bool moved)
{
	if (moved) {
		if (sprite.hasMaterial()) {
			sprite.scaleTo(getSize()).setPos(getPosition());
		}
	}
}

void UIList::onItemClicked(UIListItem& item)
{
	sendEvent(UIEvent(UIEventType::ListSelectionChanged, getId(), item.getId()));
}

UIListItem::UIListItem(const String& id, UIList& parent, std::shared_ptr<UIStyle> style, std::shared_ptr<UIWidget> widget)
	: UIClickable(id, {}, UISizer(UISizerType::Vertical))
	, parent(parent)
	, style(style)
{
	sprite = style->listItemNormal;
	UIWidget::add(widget, 0, Vector4f(3, 0, 3, 0));
}

void UIListItem::onClicked(Vector2f mousePos)
{
	parent.onItemClicked(*this);
}

void UIListItem::draw(UIPainter& painter) const
{
	if (sprite.hasMaterial()) {
		painter.draw(sprite);
	}
}

void UIListItem::update(Time t, bool moved)
{
	if (moved) {
		if (sprite.hasMaterial()) {
			sprite.scaleTo(getSize()).setPos(getPosition());
		}
	}
}

void UIListItem::doSetState(State state)
{
	switch (state) {
	case State::Up:
		sprite = style->listItemNormal;
		break;
	case State::Down:
		sprite = style->listItemSelected;
		break;
	case State::Hover:
		sprite = style->listItemHover;
		break;
	}
}