#pragma once
#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iomanip>

template <typename T>
class Queue
{
public:
	struct Node
	{
		Node* previous = nullptr;
		Node* next = nullptr;

		Node(T item) : data(item), previous(nullptr), next(nullptr) {}

		T data;
	};

protected:
	Node* begin_;
	Node* end_;

public:
	Queue() : begin_(nullptr), end_(nullptr) {}

	Node* begin() { return begin_; }
	Node* end() { return end_; }
	constexpr bool is_empty() const { return begin_ == nullptr; }

	void insert_with_priority(const T& item) {					//TODO : FIXME BUGGY AF
		//iterate through the queue, compare based on priority, change pointers accordingly
		Node* newNode = new Node(item);
		if (is_empty())
		{
			newNode->next = nullptr;
			end_ = newNode;
			begin_ = newNode;
			newNode->previous = nullptr;
			std::cout << "List was empty, first item has been inserted.)" << std::endl;
		}
		else
		{
			Node* itr = begin_;
			
			while (itr) {
				if (itr->data < newNode->data) {
					if (begin_ == itr) // if the node is going to be inserted at the beginning
					{
						itr->previous = newNode;
						newNode->next = itr;
						begin_ = newNode;
						break;
					}
					else
					{
						Node* temp = itr->previous;
						temp->next = newNode;
						itr->previous = newNode;
						newNode->next = itr;
						newNode->previous = temp;
						break;
					}
				}
				else if (itr->next == nullptr) {
					itr->next = newNode;
					newNode->previous = itr;
					end_ = newNode;
					break;
				}
				itr = itr->next;
			}			
		}
	}

	void insert_to_front(const T& item) {
	//iterate through the queue, compare based on priority, change pointers accordingly
		Node* newNode = new Node(item);
		if (is_empty())
		{
			newNode->next = nullptr;
			end_ = newNode;
			begin_ = newNode;
			newNode->previous = nullptr;
			std::cout << "List was empty, first item has been inserted." << std::endl;
		}
		else
		{
			begin_->previous = newNode;
			newNode->next = begin_;
			begin_ = newNode;
		}
	}

	constexpr void displayQueue()
	{
		Node* idx = begin_;
		if(idx == nullptr)
		{
			std::cout << "list empty" << std::endl;
			return;
		}
		else
		{
			std::cout << std::setw(20) << "Patient Name" << std::setw(20) << "Ailment" << std::setw(11) << "Severity" << std::setw(19) << "Time Criticality" << std::setw(17) << "Contagiousness" << std::setw(11) << "Priority" << std::endl;
			while (idx)
			{
				std::cout << idx->data.to_string();
				idx = idx->next;
			}

			std::cout << std::endl;
			return;
		}
	}

	T pull_highest_priority() {
		if (begin_ == nullptr)
			throw "";

		Node* node = begin_;
		const T value = node->data;
		begin_ = node->next;

		return value;
	}

	T peek() {
		if (begin_ == nullptr)
			throw "";

		Node* node = begin_;
		const T value = node->data;

		return value;
	}
};