#include "Flame.h"

Flame::Flame() {
	tickstilldie = Config::fireTime;
}

void Flame::visit(IObjectVisitor & /*visitor*/) {
}

void Flame::visit(IConstObjectVisitor & /*visitor*/) const {
	;
}

void Flame::position(Position const &value) {
	position_ = value;
}

Position const &Flame::position() const {
	return position_;
}

TextureRef const &Flame::texture() const {
	return texture_;
}

void Flame::texture(TextureRef const &texture) {
	texture_ = texture;
}

void Flame::gameTick() {
	tickstilldie-=1;
}

int Flame::ticksRemain() {
	return tickstilldie;
}