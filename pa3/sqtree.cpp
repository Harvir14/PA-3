
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

  Node* currNode = new Node(s, ul, w, h);
  double variability = -1;
  double maxVar, maxVar2;
  double varNW, varNE, varSW, varSE;

  

  pair <int,int> splitPair = ul;

  // case where currNode has already achieved ideal variability
  // if (variability <= tol) {
  //   return currNode;
  //   }
  //case where currNode contains a 1x1 pixel, so no split is possible
  // if (w == 1 && h == 1) {
  //   return currNode;
  //   }

  for (int i = 0; i < w; i++) {
      for (int j = 0; j < h; j++) {
        // if there are no intersecting lines
        if(i == 0 && j == 0) {
          continue;
        } 

          //case where there would be two children (top and bottom)
          if (i == 0) {

            varNW = s.getVar(ul, w, j);
            varSW = s.getVar(make_pair(ul.first, ul.second + j), w, h-j );

            maxVar = max(varNW, varSW);

          } else if (j == 0){

            //case where there would be two children (left and right)
            varNW = s.getVar(ul, i, h);
            varNE = s.getVar(make_pair(ul.first + i, ul.second), w - i , h);

            maxVar = max(varNW, varNE);

          } else {

              varNW = s.getVar(ul, i, j);
              varNE = s.getVar(make_pair(ul.first + i, ul.second), w - i, j);
              varSW = s.getVar(make_pair(ul.first, ul.second + j), i, h - j);
              varSE = s.getVar(make_pair(ul.first + i, ul.second + j), w - i, h - j);

              maxVar = max(varNE, varNW);
              maxVar2 = max(varSE, varSW);
              maxVar = max(maxVar, maxVar2);

          }

            if( maxVar >= tol ) {
              if (maxVar < variability) {
                variability = maxVar;
                splitPair = make_pair(i, j);
              }
            }
            else {
              return currNode;
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
      currNode->SW = buildTree(s, SWpair, w, h - splity, tol);
      
    } else if (splity == 0){
        currNode->NW = buildTree(s, ul, splitx, h, tol);
        currNode->NE = buildTree(s, NEpair, w - splitx, h, tol);

    } else {
        currNode->NW = buildTree(s, ul, splitx, splity, tol);
        currNode->NE = buildTree(s, NEpair, w - splitx, splity, tol);
        currNode->SW = buildTree(s, SWpair, splitx, h - splity, tol);
        currNode->SE = buildTree(s, SEpair, w - splitx, h-splity, tol);
      }
    // printf("x: %d y: %d\n", splitx, splity);

    return currNode;
  }
  
  
  
/**
 * Render SQtree and return the resulting image.
 */
PNG SQtree::render() {

    // PNG renderimage = *(new PNG(root->width, root->height));
    // renderimage = render(root, renderimage);
    // return renderimage;

  PNG im = *(new PNG(root->width, root->height));

  renderHelper(root, im);

  return im;

  }
    // printf("r: %d g: %d b: %d \n", im.getPixel(5, 5)->r, renderImg.getPixel(5, 5)->b, renderImg.getPixel(5, 5)->g);
  
 


// helper for render()
void SQtree::renderHelper(Node * currNode, PNG &im) {

  // queue<Node *> toRender;
  // toRender.push(root);

  //  while(!toRender.empty()){
  //     Node *currNode = toRender.front();
  //     if ((currNode->NE==NULL && currNode->NW==NULL) && (currNode->SE==NULL && currNode->SW==NULL)) {

  //       for (int i = 0; i < currNode->width; i++) {
  //         for(int j = 0; j < currNode->height; j++) {
  //           *(im.getPixel(currNode->upLeft.first + i, currNode->upLeft.second + j)) = currNode->avg;
  //           }
  //         }
  //       }
  //       if (currNode->NW != NULL){
  //         toRender.push(currNode->NW);
  //       }
  //       if (currNode->NE != NULL){
  //         toRender.push(currNode->NE);
  //       }
  //       if (currNode->SW != NULL){
  //         toRender.push(currNode->SW);
  //       }
  //       if (currNode->SE != NULL){
  //         toRender.push(currNode->SE);
  //       }
  //       toRender.pop();
        
  //     }
   if ((currNode->NE==NULL && currNode->NW==NULL) && (currNode->SE==NULL && currNode->SW==NULL)) {

       for (int i = 0; i < currNode->width; i++) {
         for(int j = 0; j < currNode->height; j++) {
              int x = currNode->upLeft.first + i;
              int y = currNode->upLeft.second + j;
              RGBAPixel* currPixel = im.getPixel(x,y);
              *currPixel = currNode->avg;
       }
     }
   }
   if (currNode->NW != NULL){
     renderHelper(currNode->NW, im);
   }
   if (currNode->NE != NULL){
       renderHelper(currNode->NE, im);
   }
   if (currNode->SW != NULL){
       renderHelper(currNode->SW, im);
   }
   if (currNode->SE != NULL){
       renderHelper(currNode->SE, im);
   }
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