#pragma once

#include "GameObjectBase.h"


class Player : public GameObjectBase {
public:
	Player();

	/* < IGameObject > */
	void visit(IObjectVisitor &visitor) override;
	void visit(IConstObjectVisitor &visitor) const override;
	void position(Position const &value) override;
	Position const &position() const override;
	TextureRef const &texture() const override;
	void texture(TextureRef const &texture) override;
	void gameTick() override;
	/* </IGameObject > */

	/**
	 * Player should start moving in the given direction.
	 * In every game tick (that is, in every call to gameTick() method),
	 * the player should move by an unit vector in the given direction.
	 * However, if there is an obstacle which can be avoided, during the
	 * game tick the player moves by an unit vector according to the
	 * obstacle avoiding algorithm. See the specification for more detail.
	 */
	void move(Direction direction, int ticks);

	/**
	 * @brief Returns true if player is moving.
	 * The player is moving since `Player::move` is called
	 * until the `ticks`-th call of gameTick().
	 */
	bool isMoving() const;

	/**
	 * @brief Drops a bomb on player's current position.
	 */
	void bomb();

	/**
	 * @brief Returns true if player is dead.
	 */
	bool isDead() const;

private:
	Position position_{};
	TextureRef texture_;
	int remain_ticks;
	Direction direction;
};
