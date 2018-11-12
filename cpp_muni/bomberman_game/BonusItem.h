#pragma once

#include "GameObjectBase.h"

enum class Bonus;

class BonusItem : public GameObjectBase {
public:
	BonusItem();

	/* < IGameObject > */
	void visit(IObjectVisitor &visitor) override;
	void visit(IConstObjectVisitor &visitor) const override;
	void position(Position const &value) override;
	Position const &position() const override;
	TextureRef const &texture() const override;
	void texture(TextureRef const &texture) override;
	/* </IGameObject > */

	/**
	 * @brief Sets the kind of bonus.
	 */
	void bonus(Bonus value);
	Bonus hasbonus();

private:
	Position position_{};
	TextureRef texture_;
	Bonus bonus_;
};
