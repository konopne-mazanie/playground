#pragma once

#include <memory>
#include <string>
#include <sstream>

#include <iostream>
namespace pevs
{
class BinTree
{
private:
	class Node
	{
	private:
		std::string question;
		std::unique_ptr<Node> yes = nullptr;
		std::unique_ptr<Node> no = nullptr;
		Node* parent = nullptr;
		bool userDefined = false;
		friend class BinTree;

	public:
		Node() {}
		Node(const std::string& question, Node* parent, bool userDefined = false);
		Node(const std::string& question, Node* parent, std::unique_ptr<Node> yes, std::unique_ptr<Node> no);
	};

	std::unique_ptr<Node> root = nullptr;
	Node* actNode = nullptr;

	static void loadNode(std::istream &in, std::string& question, int& userDefined, int& hasYes, int& hasNo);

public:
	BinTree(){}
	BinTree(const std::string& question);
	bool move(bool answer);
	bool moveBack();
	void reset();
	bool onLeaf() const;
	void insertKnowledgeLeaf(const std::string& final_question, const std::string& pre_question, bool parentPath);
	void insertKnowledge(const std::string& final_question, bool answer, bool userDefined = false);
	const std::string& getActData() const;
	std::string printAct() const;

	void serialize(std::ostream &out, Node* node = nullptr);
	static std::unique_ptr<BinTree> deserialize(std::istream &in);
};
}
