#pragma once

#include "GameObjectBase.h"

class Bomb : public GameObjectBase {
public:
	Bomb();

	/* < IGameObject > */
	void visit(IObjectVisitor &visitor) override;
	void visit(IConstObjectVisitor &visitor) const override;
	void position(Position const &value) override;
	Position const &position() const override;
	TextureRef const &texture() const override;
	void texture(TextureRef const &texture) override;
	/* </IGameObject > */

private:
	Position position_{};
	TextureRef texture_;
};
