#include "Wall.h"

Wall::Wall() {
	;
}

void Wall::visit(IObjectVisitor & /*visitor*/) {
}

void Wall::visit(IConstObjectVisitor & /*visitor*/) const {
}

void Wall::position(Position const &value) {
	position_ = value;
}

Position const &Wall::position() const {
	return position_;
}

TextureRef const &Wall::texture() const {
	return texture_;
}

void Wall::texture(TextureRef const &texture) {
	texture_ = texture;
}

void Wall::bonus(Bonus bon) {
	bonus_=bon;
}

void Wall::destroyable(bool isd) {
	destroyable_=isd;
}

bool Wall::isDestroyable() {
	return destroyable_;
}

Bonus Wall::hasbonus() {
	return bonus_;
}