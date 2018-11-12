#include "Player.h"

class Flame;

Player::Player() {
	remain_ticks=0;
}

void Player::visit(IObjectVisitor & visitor) {
	visitor(*this);
}

void Player::visit(IConstObjectVisitor & visitor) const {
	visitor(*this);
}

void Player::position(Position const &value) {
	position_ = value;
}

Position const &Player::position() const {
	return position_;
}

TextureRef const &Player::texture() const {
	return texture_;
}

void Player::texture(TextureRef const &texture) {
	texture_ = texture;
}

void Player::move(Direction dir, int ticks) {
	// The function `Vector toVector(Direction direction);`
	// from `Geometry.h` could be helpful.
	position(next(position_,toVector(dir)));
	remain_ticks=ticks-1;
	direction = dir;
}

bool Player::isMoving() const {
	if (remain_ticks == 0) {
		return false;
	}
	return true;
}

void Player::bomb() {
}

bool Player::isDead() const {
	return false;
}

void Player::gameTick() {
	if (isMoving()) {
		position(next(position_,toVector(direction)));
		remain_ticks-=1;
	}
}
