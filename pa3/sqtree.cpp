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
  int imWidth = imIn.width();
  int imHeight = imIn.height();
  pair <int,int> upperLeft = make_pair(0,0);
  stats *imStats = new stats(imIn);
  root = buildTree(*imStats, upperLeft, imWidth, imHeight, tol);
}

/**
 * Helper for the SQtree constructor.
 */
SQtree::Node * SQtree::buildTree(stats & s, pair<int,int> & ul,
				 int w, int h, double tol) {

  Node* currNode = new Node(ul, w, h, s.getAvg(ul, w, h), s.getVar(ul, w, h));
  double variability = s.getVar(ul, w, h);
  double maxVar;
  double maxVar2;
  

  pair <int,int> splitPair = ul;

  // case where currNode has already achieved ideal variability
  if (variability <= tol) {
    return currNode;
    }
  //case where currNode contains a 1x1 pixel, so no split is possible
  if (w == 1 && h == 1) {
    return currNode;
    }

  for (int i = 0; i < w; i++) {
      for (int j = 0; j < h; j++) {
        // if there are no intersecting lines
        if(i == 0 && j == 0) {
          continue;
        } else { 

          //case where there would be two children (top and bottom)
          if (i == 0) {

            double varN = s.getVar(ul, w, j);
            double varS = s.getVar(make_pair(ul.first+i, ul.second + j), w, h-j );

            maxVar = max(varN, varS);

            if( maxVar < variability ) {
              variability = maxVar;
              splitPair = make_pair(i, j);
            }

          } else {

            //case where there would be two children (left and right)
             if (j == 0) {
            double varW = s.getVar(ul, i, h);
            double varE = s.getVar(make_pair(ul.first + i, ul.second + j), w - i , h);

            maxVar = max(varW, varE);

            if( maxVar < variability ) {
              variability = maxVar;
              splitPair = make_pair(i, j);
              }
            } else {

              double varNW = s.getVar(ul, i, j);
              double varNE = s.getVar(make_pair(ul.first + i, ul.second), w - i, j);
              double varSW = s.getVar(make_pair(ul.first, ul.second + j), w, h - j);
              double varSE = s.getVar(make_pair(ul.first + i, ul.second + j), w - i, h - j);

              maxVar = max(varNE, varNW);
              maxVar2 = max(varSE, varSW);
              maxVar = max(maxVar, maxVar2);

              if( maxVar < variability ) {
                variability = maxVar;
                splitPair = make_pair(i, j);
              }
            }
          }
        }
      }
    }
    // recursion stuff

    int splitx = splitPair.first;
    int splity = splitPair.second;
    
    pair <int,int> NEpair = make_pair(ul.first + splitx, ul.second);
    pair <int,int> SWpair = make_pair(ul.first, ul.second + splity);
    pair <int,int> SEpair = make_pair(ul.first + splitx, ul.second + splity);

    if (splitx == 0 && splity == 0) {
      return currNode;
    }

    if (splitx == 0) {
      
      currNode->NW = buildTree(s, ul, w, splity, tol);
      currNode->SE = buildTree(s, SEpair, w, h - splity, tol);
      
    } else {
      if (splity == 0) {
        currNode->NW = buildTree(s, ul, splitx, h, tol);
        currNode->SE = buildTree(s, SEpair, w - splitx, h, tol);

      } else {
        currNode->NW = buildTree(s, ul, splitx, splity, tol);
        currNode->NE = buildTree(s, NEpair, w - splitx, h, tol);
        currNode->SW = buildTree(s, SWpair, w, h - splity, tol);
        currNode->SE = buildTree(s, SEpair, w - splitx, h-splity, tol);
      }
    }
    // printf("x: %d y: %d\n", splitx, splity);

    return currNode;
  }
  
  
  
/**
 * Render SQtree and return the resulting image.
 */
PNG SQtree::render() {
  
    PNG renderImg = *(new PNG(root->width, root->height));
    render(root, renderImg);
    // printf("r: %d g: %d b: %d \n", renderImg.getPixel(5, 5)->r, renderImg.getPixel(5, 5)->b, renderImg.getPixel(5, 5)->g);
  
    return renderImg;
}

// helper for render()
void SQtree::render(Node * currNode, PNG im) {
   
    if ((currNode->NE==NULL && currNode->NW==NULL) && (currNode->SE==NULL && currNode->SW==NULL)) {

      // printf("x: %d y: %d\n", currNode->upLeft.first, currNode->upLeft.second);

      for (int i = 0; i < currNode->width; i++) {
        for(int j = 0; j < currNode->height; j++) {
          RGBAPixel* p = im.getPixel(currNode->upLeft.first + i, currNode->upLeft.second + j);
          *p = currNode->avg;
          printf("r: %d g: %d b: %d \n", p->r, p->b, p->g);
      }
    }
  }
  if (currNode->NW != NULL){
      render(currNode->NW, im);
  }
  if (currNode->NE != NULL){
      render(currNode->NE, im);
  }
  if (currNode->SW != NULL){
      render(currNode->SW, im);
  }
  if (currNode->SE != NULL){
      render(currNode->SE, im);
  }
  // printf("r: %d g: %d b: %d \n", im.getPixel(5, 5)->r, im.getPixel(5, 5)->b, im.getPixel(5, 5)->g);
}

/**
 * Delete allocated memory.
 */
void SQtree::clear() {
  clear(root);
}
//helper for clear
void SQtree::clear(Node * & curr) {
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

SQtree::Node * SQtree::copy(const Node * other) {
  if(other == NULL){
		return NULL;
	}

	Node * newNode = new Node(other->upLeft, other->width, other->height, other->avg, other->var);
	if(other->NE != NULL) {
    newNode->NE = copy(other->NE); 
    }
  if(other->NW != NULL) {
    newNode->NW = copy(other->NW); 
    }
  if(other->SE != NULL) {
    newNode->SE = copy(other->SE); 
    }
  if(other->SW != NULL) {
    newNode->SW = copy(other->SW); 
    }

	return newNode;

}

int SQtree::size() {
  return size(root);
}

int SQtree::size(Node * & curr) {
  int val = 0;
  if(curr == NULL) {
    return val;
    } else {
      val ++;
      if (curr->NE != NULL) {
        val += size(curr->NE);
      }
      if (curr->NW != NULL) {
        val += size(curr->NW);
      }
      if (curr->SE != NULL) {
        val += size(curr->SE);
      }
      if (curr->SW != NULL) {
        val += size(curr->SW);
      }
    }
    return val;
  }

