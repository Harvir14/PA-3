/**
 *
 * shifty quadtree (pa3)
 * sqtree.cpp
 * This file will be used for grading.
 *
 */

#include "sqtree.h"

// First Node constructor, given.
SQtree::Node::Node(pair<int,int> ul, int w, int h, RGBAPixel a, double v)
  :upLeft(ul),width(w),height(h),avg(a),var(v),NW(NULL),NE(NULL),SE(NULL),SW(NULL)
{}

// Second Node constructor, given
SQtree::Node::Node(stats & s, pair<int,int> ul, int w, int h)
  :upLeft(ul),width(w),height(h),NW(NULL),NE(NULL),SE(NULL),SW(NULL) {
  avg = s.getAvg(ul,w,h);
  var = s.getVar(ul,w,h);
}

// SQtree destructor, given.
SQtree::~SQtree() {
  clear();
}

// SQtree copy constructor, given.
SQtree::SQtree(const SQtree & other) {
  copy(other);
}

// SQtree assignment operator, given.
SQtree & SQtree::operator=(const SQtree & rhs) {
  if (this != &rhs) {
    clear();
    copy(rhs);
  }
  return *this;
}

/**
 * SQtree constructor given tolerance for variance.
 */
SQtree::SQtree(PNG & imIn, double tol) {
  // Your code here.
}

/**
 * Helper for the SQtree constructor.
 */
SQtree::Node * SQtree::buildTree(stats & s, pair<int,int> & ul,
				 int w, int h, double tol) {
  // Your code here.
}
  
/**
 * Render SQtree and return the resulting image.
 */
PNG SQtree::render() {
  // Your code here.
}

/**
 * Delete allocated memory.
 */
void SQtree::clear() {
  clear(root);
}
//helper for clear
void SQtree::clear((Node * & curr)) {
  if(curr == NULL) {
    return;
    } else {
      clear(curr->NE);
	    clear(curr->NW);
	    clear(curr->SE);
	    clear(curr->SW);
	    delete(curr);
	    curr = NULL;
      }
  }
		  
void SQtree::copy(const SQtree & other) {
  root = copy(other.root);
}

void SQtree::copy(const Node * other) {
  if(other == NULL){
		return NULL;
	}

	Node* newNode = new Node(other->upLeft, other->width, other->height, other->avg, other->var);
	newNode->NE = copy(other->NE);
	newNode->NW = copy(other->NW);
	newNode->SE = copy(other->SE);
	newNode->SW = copy(other->SW);
	return newNode;

}

int SQtree::size() {
  size(root);
}

void SQtree::size((Node * & curr)) {
  int val = 0;
  if(curr == NULL) {
    return val;
    } else {
      val ++;
      val += size(curr->NE);
	    val += size(curr->NW);
	    val += size(curr->SE);
	    val += size(curr->SW);
      }
    return val;
  }

