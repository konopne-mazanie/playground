#pragma once

#include <memory>

// This is my attempt of multiplatform Queue implementation in modern C++
// I tried to achieve at least same effectivity of operations.

namespace pevs
{
template <class T>
class Queue
{
private:
	template <class X>
	class QueueElement
	{
	private:
		X data;
		std::unique_ptr<QueueElement<X>> next = nullptr;
		friend class Queue;

	public:
		QueueElement(X data)
		{
			this->data = std::move(data);
		}
	};

	std::unique_ptr<QueueElement<T>> first = nullptr;
	QueueElement<T> *last;
	int lenght_ = 0;

public:
	Queue() {}

	Queue(T data) {
		push(std::move(data));
	}

	void push(T data)
	{
		if (!first)
		{
			first = std::make_unique<QueueElement<T>>(std::move(data));
			last = first.get();
			lenght_++;
			return;
		}
		last->next = std::make_unique<QueueElement<T>>(std::move(data));
		last = last->next.get();
		lenght_++;
	}
	T pop()
	{
		T data = first->data;
		first = std::move(first->next);
		lenght_--;
		return data;
	}
	T *get(int pos) const
	{
		QueueElement<T> *current = first.get();
		int i = 0;
		for (; i < pos; i++)
		{
			if (current->next)
				current = current->next.get();
			else
				break;
		}
		if (i == pos)
			return &(current->data);
		else
			return nullptr;
	}

	int lenght() const {
		return lenght_;
	}
};
}