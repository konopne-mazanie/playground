#ifndef TRIE_H
#define TRIE_H
#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

//nezabudni presunut do sk repozitara pred odovzd

template <typename Alphabet, typename Value>
class Trie {
public:
	using ItemList = std::vector<std::pair<std::string, const Value&>>;

	class Node {
		friend class Trie;
		Node* parent_;
		std::pair<char,std::unique_ptr<Node>> child_right;
		std::pair<char,std::unique_ptr<Node>> child_left;
		std::unique_ptr<Value> value_;
	public:
		Node(Node* par, Value* val)
		: parent_(par), child_right(std::make_pair<char, std::unique_ptr<Node>>('\0',nullptr)), child_left(std::make_pair<char, std::unique_ptr<Node>>('\0',nullptr)),value_(std::make_unique<Value>(*val)) {}
		const Node* child(char letter) const {
			if ((child_right.second) && (child_right.first == letter)) {
				return child_right.second.get();
			}
			if ((child_left.second) && (child_right.left == letter)) {
				return child_left.second.get();
			}
			return nullptr;
		}
		const Node* parent() const {
			return const_cast<const Node*>(parent_);
		}
		const Value* value() const {
			if (value_) {
				return value_.get();
			}
			return nullptr;
		}
	};
	/*
	Trie()
	: root(std::make_unique<Node>())
	*/
	// root()
	// empty()
	// search(key)
	// at(key)
	// remove(key)
	// operator[](key)
	// clear()

	// items()

	bool insert(const std::string& key, Value value) {
		bool setreturn = false;
		Node* current = root.get();
		for (char c : key) {
			if ((current->child_left.second.get()) && (current->child_left.first == c)) {
				current = current->child_left.second.get();
				continue;
			}
			
			if ((current->child_right.second.get()) && (current->child_right.first == c)) {
				current = current->child_right.second.get();
				continue;
			}

			if (!current->child_left.second.get()) {
				current->child_left.first = c;
				current->child_left.second = std::make_unique<Node>(current, nullptr);
				setreturn = true;
				current = current->child_left.second.get();
				continue;
			}
			if (!current->child_right.second.get()) {
				current->child_right.first = c;
				current->child_right.second = std::make_unique<Node>(current, nullptr);
				setreturn = true;
				current = current->child_right.second.get();
			}
		}
		if (setreturn) {
			current->value_ = std::make_unique<Value>(value);
		}
		return setreturn;
	}
	void draw(std::ostream& output) {
		counter = 0;
		draw_(output, *(root.get()));
	}
private:
	std::unique_ptr<Node> root;
	int counter;
	void draw_(std::ostream& output, const Node& node) {
		output << "\"" << counter << "\"[label=\"" << *(node.value()) << "\"]";
		if (node.child_left.second) {
			output << "\"" << counter << "\" -> \"" << counter+1 << "\" [label=\"" << node.child_left.first << "\"]";
			counter+=1;
			draw_(output, *(node.child_left.second.get()));
		}
		if (node.child_right.second) {
			output << "\"" << counter << "\" -> \"" << counter+1 << "\" [label=\"" << node.child_right.first << "\"]";
			counter+=1;
			draw_(output, *(node.child_right.second.get()));
		}
	}
public:
	Trie()
	: root(std::make_unique<Node>(nullptr, nullptr)), counter(0) {}
};

#endif
