#ifndef MAP_HPP
#define MAP_HPP

#include"ft.hpp"
#include"pair.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include <exception>
#include <stdexcept>
#include <memory>
#include <cstddef>

namespace ft{
	template< class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<key_type, mapped_type> value_type;
			typedef std::less<key_type> key_compare;
			typedef Alloc allocator_type;
		private:
			struct Node {
				key_type key;
				T value;
				Node* left;
				Node* right;
				int height;
			};

			Node *node;

			Node *searched;

			Node *parent;

			key_compare _comp;

			int Height(Node* node) {
				if (node == nullptr)
					return 0;
				return node->height;
			}

			int Balance(Node* node) {
				if (node == nullptr) {
				return 0;
				}
				return Height(node->left) - Height(node->right);
			}

			Node *rotateRight(Node* toRotate){
				Node *tmp_root = toRotate->left;
				Node *tmp_left = tmp_root->right;
				tmp_root->right = toRotate;
				toRotate->left = tmp_left;
				toRotate->height = 1 + std::max(Height(toRotate->right), Height(toRotate->left));
				tmp_root->height = 1 + std::max(Height(tmp_root->right), Height(tmp_root->left));
				return tmp_root;
			}

			Node *rotateLeft(Node* toRotate){
				Node *tmp_root = toRotate->right;
				Node *tmp_left = tmp_root->left;
				tmp_root->left = toRotate;
				toRotate->right = tmp_left;
				toRotate->height = 1 + std::max(Height(toRotate->right), Height(toRotate->left));
				tmp_root->height = 1 + std::max(Height(tmp_root->right), Height(tmp_root->left));
				return tmp_root;
			}

			Node *insertAVL(Node *toAdd, key_type key, T value){
				if (toAdd == nullptr){
					Node *l = new Node;
					l->key = key;
					l->value = value;
					l->left = nullptr;
					l->right = nullptr;
					l->height = 1;
					return l;
				}
				if (_comp(key, toAdd->key))
					toAdd->left = insertAVL(toAdd->left, key, value); // insert smaller
				else if (_comp(toAdd->key, key))
					toAdd->right = insertAVL(toAdd->right, key, value); // insert larger
				else
					toAdd->value = value; // if he is adding value on the same key
				toAdd->height = std::max(Height(toAdd->right), Height(toAdd->left)) + 1;
				// rotation part to add
				int balance = Balance(toAdd);
				if (balance > 1 && _comp(key, toAdd->left->key)) // if the left side is bigger than the right side and the key that has been added is smaller than the left key so the left key can be root just rotate right
					return rotateRight(toAdd);
				if (balance < -1 && _comp(toAdd->right->key, key)) // if the right side is bigger than the left side and the key that has been added is smaller than the right key so the right key can be root just rotate left
					return rotateLeft(toAdd);
				if (balance > 1 && _comp(toAdd->left->key, key)){ // if the left side is bigger than the right side and the key that has been added is bigger than the left key so the left key can't be directly a root just rotate left for the left branch then right to the root
					toAdd->left = rotateLeft(toAdd->left);
					return rotateRight(toAdd);
				}
				if (balance < -1 && _comp(key, toAdd->right->key)){ // if the left side is bigger than the right side and the key that has been added is bigger than the right key so the right key can't be directly a root just rotate right for the right branch then left to the root
					toAdd->right = rotateRight(toAdd->right);
					return rotateLeft(toAdd);
				}
				return toAdd;
			}

			void search_N(Node *root, key_type key){
				if (root->key == key){
					searched = root;
					return ;
				}
				if (_comp(key, root->key)){
					if (root->left){
						if (root->left->key == key)
							parent = root;
						search_N(root->left, key);
					}
				}
				else{
					if (root->right){
						if (root->right->key == key)
							parent = root;
						search_N(root->right, key);
					}
				}
			}

			Node* Min(Node* node) {
				if (node == nullptr) {
					return nullptr;
				}
				if (node->left == nullptr) {
					return node;
				}
				return Min(node->left);
			}

			Node* Remove(Node* crnt, key_type key) {
				if (crnt == nullptr) {
					return nullptr;
				}
				if (key < crnt->key) {
					crnt->left = Remove(crnt->left, key);
				}
				else if (key > crnt->key) {
					crnt->right = Remove(crnt->right, key);
				}
				else {
					if (crnt->left == nullptr && crnt->right == nullptr) {
						delete crnt;
						return nullptr;
					}
					if (crnt->left != nullptr && crnt->right == nullptr) {
						Node* temp = crnt->left;
						delete crnt;
						return temp;
					}
					if (node->left == nullptr && node->right != nullptr) {
						Node* temp = node->right;
						delete crnt;
						return temp;
					}
					Node* successor = Min(crnt->right);
					crnt->key = successor->key;
					crnt->value = successor->value;
					crnt->right = Remove(crnt->right, successor->key);
				}
				crnt->height = std::max(Height(crnt->right), Height(crnt->left)) + 1;
				int balance = Balance(crnt);
				if (balance > 1 && Balance(node->left) == -1){
					crnt->left = rotateLeft(crnt->left);
					return rotateRight(crnt);
				}
				if (balance < -1 && Balance(node->right) == 1){
					crnt->right = rotateRight(crnt->right);
					return rotateLeft(crnt);
				}
				if (balance > 1 && Balance(node->left) == 1)
					return rotateRight(crnt);
				if (balance < -1 && Balance(node->right) == -1)
					return rotateLeft(crnt);
				return crnt;
			}

		public:
			map(): node(nullptr){}

			~map(){ deleteAll(); }

			void print2D() {
			  std::cout << "Tree:" << std::endl;
			  print2DUtil(node, 0);
			}

			 void print2DUtil(Node *root, int space) {
			  if (root == NULL) return;
			  space += 10;
			  print2DUtil(root->right, space);
			  std::cout << std::endl;
			  for (int i = 10; i < space; i++) std::cout << " ";
			  std::cout << root->value << "(" << Balance(root) << ")" << std::endl;
				for (int i = 10; i < space; i++) std::cout << " ";
			  print2DUtil(root->left, space);
			}

			void insert(key_type key, T value){
				node = insertAVL(node, key, value);
			}

			void search(key_type key){
				searched = nullptr;
				parent = nullptr;
				search_N(node, key);
				if (searched != nullptr){
					std::cout << "key: " << searched->key << std::endl << "value: " << searched->value << std::endl;
					if (parent != nullptr)
						std::cout << "key: " << parent->key << std::endl << "value: " << parent->value << std::endl;
				}
				else
					std::cout << "NOT FOUND" << std::endl;
			}

			void deleteit(key_type key){
				node = Remove(node, key);
			}

			void deleteAll(){
				delete_node(node);
				delete node;
			}

			void delete_node(Node *nodes){
				if (nodes->right){
					delete_node(nodes->right);
					delete nodes->right;
				}
				if (nodes->left){
					delete_node(nodes->left);
					delete nodes->left;
				}
			}
	};
}

#endif