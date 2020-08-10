#include "BinTree.h"

namespace pevs {
    BinTree::Node::Node(const std::string& question, Node* parent, bool userDefined) {
		this->question = question;
		this->parent = parent;
		this->userDefined = userDefined; // nodes defined outside game should be treated differently
	}
	
    BinTree::Node::Node(const std::string& question, Node* parent, std::unique_ptr<Node> yes, std::unique_ptr<Node> no) {
		this->question = question;
		this->parent = parent;
		this->yes = std::move(yes);
		this->no = std::move(no);
        this->yes->parent = this;
        this->no->parent = this;
	}

    BinTree::BinTree(const std::string& question) {
		root = std::make_unique<Node>(question, nullptr);
		reset();
	}

	bool BinTree::move(bool answer) {
		if (answer) {
			if (actNode->yes) actNode = actNode->yes.get();
			else return false;
		} else {
			if (actNode->no) actNode = actNode->no.get();
			else return false;
		}
		return true;
	}

	bool BinTree::moveBack() {
		if (actNode->parent) {
			actNode = actNode->parent;
			return true;
		}
		return false;
	}

	void BinTree::reset() {
		actNode = root.get();
	}

	bool BinTree::onLeaf() const {
		return (!actNode->yes && !actNode->no && !actNode->userDefined);
	}

	void BinTree::insertKnowledgeLeaf(const std::string& final_question, const std::string& pre_question, bool parentPath) {
		auto parent = actNode->parent;
		auto replacing = std::move(parentPath ? parent->yes : parent->no);
		auto newNode = std::make_unique<Node>(pre_question, parent, std::make_unique<Node>(final_question, nullptr), std::move(replacing));
		(parentPath ? parent->yes : parent->no) = std::move(newNode);
	}

	void BinTree::insertKnowledge(const std::string& final_question, bool answer, bool userDefined) {
		if (answer) actNode->yes = std::make_unique<Node>(final_question, actNode, userDefined);
		else actNode->no = std::make_unique<Node>(final_question, actNode, userDefined);
	}

	const std::string& BinTree::getActData() const {
		return actNode->question;
	}

	std::string BinTree::printAct() const {
		std::stringstream ret;
		ret << "----------" << std::endl;
		ret << "Active node: " << actNode->question << std::endl;
		if (actNode->yes) ret << "Yes child: " << actNode->yes->question << std::endl;
		if (actNode->no) ret << "No child: " << actNode->no->question << std::endl;
		ret << "----------" << std::endl;
		return ret.str();
	}

	void BinTree::serialize(std::ostream &out, Node* node) {
		Node* current = node ? node : root.get();
		if (current->yes) serialize(out, current->yes.get());
		if (current->no) serialize(out, current->no.get());
		out << current->question << '\n' << (current->userDefined ? 1 : 0) << ' ' << (current->yes ? 1 : 0) << ' ' << (current->no ? 1 : 0) << '\n';
	}

	std::unique_ptr<BinTree> BinTree::deserialize(std::istream &in) {
		std::unique_ptr<Node> child1 = nullptr;
		std::unique_ptr<Node> child2 = nullptr;
		std::unique_ptr<Node> parent = nullptr;
		std::string question;
		int userDefined, hasYes, hasNo;

		try {
			loadNode(in, question, userDefined, hasYes, hasNo);
			child1 = std::make_unique<Node>(question, nullptr, (userDefined == 1));
			while (!in.eof() && !in.fail()) {
				loadNode(in, question, userDefined, hasYes, hasNo);
				if (question == "#END#") break; //neccessary end tag because of possible \n at file end
				if (hasYes && !hasNo) {
					parent = std::make_unique<Node>(question, nullptr, userDefined);
					parent->yes = std::move(child1);
					parent->yes->parent = parent.get();
				} else if (hasNo && !hasYes) {
					parent = std::make_unique<Node>(question, nullptr, userDefined);
					parent->no = std::move(child1);
					parent->no->parent = parent.get();
				} else {
					child2 = std::make_unique<Node>(question, nullptr, userDefined);
					loadNode(in, question, userDefined, hasYes, hasNo);

					parent = std::make_unique<Node>(question, nullptr, userDefined);
					parent->yes = std::move(child1);
					parent->yes->parent = parent.get();
					parent->no = std::move(child2);
					parent->no->parent = parent.get();
				}
				child1 = std::move(parent);
				child2 = nullptr;
				parent = nullptr;
			}
		} catch (std::exception& e) {
			return nullptr;
		}
		if (!child1) return nullptr;
		auto ret = std::make_unique<BinTree>();
		ret->root = std::move(child1);
		ret->reset();
		return ret;
	}

	void BinTree::loadNode(std::istream &in, std::string& question, int& userDefined, int& hasYes, int& hasNo) {
		char q[30];
		in.getline(q, 30);
		question = q;
		in >> userDefined;
		in >> hasYes;
		in >> hasNo;
		in.getline(q, 30);
	}
}