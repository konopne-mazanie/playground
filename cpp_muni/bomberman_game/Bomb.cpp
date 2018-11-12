#include "Bomb.h"

Bomb::Bomb() {
}

void Bomb::visit(IObjectVisitor & /*visitor*/) {
	;
}

void Bomb::visit(IConstObjectVisitor & /*visitor*/) const {
	;
}

void Bomb::position(Position const &value) {
	position_ = value;
}

Position const &Bomb::position() const {
	return position_;
}

TextureRef const &Bomb::texture() const {
	return texture_;
}

void Bomb::texture(TextureRef const &texture) {
	texture_ = texture;
}
