#include "BonusItem.h"

BonusItem::BonusItem() {
	;
}

void BonusItem::visit(IObjectVisitor & /*visitor*/) {
	;
}

void BonusItem::visit(IConstObjectVisitor & /*visitor*/) const {
	;
}

void BonusItem::position(Position const &value) {
	position_ = value;
}

Position const &BonusItem::position() const {
	return position_;
}

TextureRef const &BonusItem::texture() const {
	return texture_;
}

void BonusItem::texture(TextureRef const &texture) {
	texture_ = texture;
}

void BonusItem::bonus(Bonus bon) {
	bonus_ = bon;
}

Bonus BonusItem::hasbonus() {
	return bonus_;
}
