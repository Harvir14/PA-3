#include "stats.h"
#include "stats.h"

stats::stats(PNG & im){

    /* Your code here!! */

  sumRed = vector<vector<long>>(im.height(), vector<long> (im.width()));
  sumGreen = vector<vector<long>>(im.height(), vector<long> (im.width()));
  sumBlue = vector<vector<long>>(im.height(), vector<long> (im.width()));
  sumsqRed = vector<vector<long>>(im.height(), vector<long> (im.width()));
  sumsqGreen = vector<vector<long>>(im.height(), vector<long> (im.width()));
  sumsqBlue = vector<vector<long>>(im.height(), vector<long> (im.width()));

  long sumR, sumG, sumB, sumRsq, sumGsq, sumBsq;

for (unsigned int y = 0; y < im.height(); y++) {
    for (unsigned int x = 0; x < im.width(); x++) {
        if (x == 0 && y == 0) {
            sumR = (long)im.getPixel(x,y)->r;
            sumG = (long)im.getPixel(x,y)->g;
            sumB = (long)im.getPixel(x,y)->b;
            sumRsq = (long)im.getPixel(x,y)->r * (long)im.getPixel(x,y)->r;
            sumGsq = (long)im.getPixel(x,y)->g * (long)im.getPixel(x,y)->g;
            sumBsq = (long)im.getPixel(x,y)->b * (long)im.getPixel(x,y)->b;
        }
        else if (x == 0) {
            sumR = (long)im.getPixel(x,y)->r + sumRed[y-1][x];
            sumG = (long)im.getPixel(x,y)->g + sumGreen[y-1][x];
            sumB = (long)im.getPixel(x,y)->b + sumBlue[y-1][x];
            sumRsq = (long)im.getPixel(x,y)->r * (long)im.getPixel(x,y)->r + sumsqRed[y-1][x];
            sumGsq = (long)im.getPixel(x,y)->g * (long)im.getPixel(x,y)->g + sumsqGreen[y-1][x];
            sumBsq = (long)im.getPixel(x,y)->b * (long)im.getPixel(x,y)->b + sumsqBlue[y-1][x];

        }
        else if (y == 0) {
            sumR = (long)im.getPixel(x,y)->r + sumRed[y][x-1];
            sumG = (long)im.getPixel(x,y)->g + sumGreen[y][x-1];
            sumB = (long)im.getPixel(x,y)->b + sumBlue[y][x-1];
            sumRsq = (long)im.getPixel(x,y)->r * (long)im.getPixel(x,y)->r + sumsqRed[y][x-1];
            sumGsq = (long)im.getPixel(x,y)->g * (long)im.getPixel(x,y)->g + sumsqGreen[y][x-1];
            sumBsq = (long)im.getPixel(x,y)->b * (long)im.getPixel(x,y)->b + sumsqBlue[y][x-1];
        } 
        else {
            sumR = (long)im.getPixel(x,y)->r + sumRed[y][x-1] + sumRed[y-1][x] - sumRed[y-1][x-1];
            sumG = (long)im.getPixel(x,y)->g + sumGreen[y][x-1] + sumGreen[y-1][x] - sumGreen[y-1][x-1];
            sumB = (long)im.getPixel(x,y)->b + sumBlue[y][x-1] + sumBlue[y-1][x] - sumBlue[y-1][x-1];
            sumRsq = (long)im.getPixel(x,y)->r * (long)im.getPixel(x,y)->r + sumsqRed[y][x-1] + sumsqRed[y-1][x] - sumsqRed[y-1][x-1];
            sumGsq = (long)im.getPixel(x,y)->g * (long)im.getPixel(x,y)->g + sumsqGreen[y][x-1] + sumsqGreen[y-1][x] - sumsqGreen[y-1][x-1];
            sumBsq = (long)im.getPixel(x,y)->b * (long)im.getPixel(x,y)->b + sumsqBlue[y][x-1] + sumsqBlue[y-1][x] - sumsqBlue[y-1][x-1];

        }
        sumRed[y][x] = sumR;
        sumGreen[y][x] = sumG;
        sumBlue[y][x] = sumB;
        sumsqRed[y][x] = sumRsq;
        sumsqGreen[y][x] = sumGsq;
        sumsqBlue[y][x] = sumBsq;
    }
}

}


long stats::getSum(char channel, pair<int,int> ul, int w, int h){
/* Your code here!! */
    if (channel == 'r') {
        if (ul.first == 0 && ul.second == 0) {
            return sumRed[ul.second + h -1][ul.first + w -1];
        }
        else if (ul.first == 0) {
            return 0 - sumRed[ul.second-1][ul.first + w - 1] + sumRed[ul.second + h - 1][ul.first + w - 1];
        }
        else if (ul.second == 0) {
            return 0 - sumRed[ul.second + h - 1][ul.first - 1] + sumRed[ul.second + h - 1][ul.first + w - 1];
        }
        else {
            return sumRed[ul.second + h - 1][ul.first + w - 1] - sumRed[ul.second - 1][ul.first + w - 1] - sumRed[ul.second + h - 1][ul.first - 1] + sumRed[ul.second - 1][ul.first - 1];
        } 
    }
    else if (channel == 'g') {
        if (ul.first == 0 && ul.second == 0) {
            return sumGreen[ul.second + h -1][ul.first + w -1];
        }
        else if (ul.first == 0) {
            return 0 - sumGreen[ul.second-1][ul.first + w - 1] + sumGreen[ul.second + h - 1][ul.first + w - 1];
        }
        else if (ul.second == 0) {
            return 0 - sumGreen[ul.second + h - 1][ul.first - 1] + sumGreen[ul.second + h - 1][ul.first + w - 1];
        }
        else {
            return sumGreen[ul.second + h - 1][ul.first + w - 1] - sumGreen[ul.second - 1][ul.first + w - 1] - sumGreen[ul.second + h - 1][ul.first - 1] + sumGreen[ul.second - 1][ul.first - 1];
        } 
    }
    else {
        if (ul.first == 0 && ul.second == 0) {
            return sumBlue[ul.second + h -1][ul.first + w -1];
        }
        else if (ul.first == 0) {
            return 0 - sumBlue[ul.second-1][ul.first + w - 1] + sumBlue[ul.second + h - 1][ul.first + w - 1];
        }
        else if (ul.second == 0) {
            return 0 - sumBlue[ul.second + h - 1][ul.first - 1] + sumBlue[ul.second + h - 1][ul.first + w - 1];
        }
        else {
            return sumBlue[ul.second + h - 1][ul.first + w - 1] - sumBlue[ul.second - 1][ul.first + w - 1] - sumBlue[ul.second + h - 1][ul.first - 1] + sumBlue[ul.second - 1][ul.first - 1];
        } 
    }
}

long stats::getSumSq(char channel, pair<int,int> ul, int w, int h){
/* Your code here!! */
    if (channel == 'r') {
        if (ul.first == 0 && ul.second == 0) {
            return sumsqRed[ul.second + h -1][ul.first + w -1];
        }
        else if (ul.first == 0) {
            return 0 - sumsqRed[ul.second-1][ul.first + w - 1] + sumsqRed[ul.second + h - 1][ul.first + w - 1];
        }
        else if (ul.second == 0) {
            return 0 - sumsqRed[ul.second + h - 1][ul.first - 1] + sumsqRed[ul.second + h - 1][ul.first + w - 1];
        }
        else {
            return sumsqRed[ul.second + h - 1][ul.first + w - 1] - sumsqRed[ul.second - 1][ul.first + w - 1] - sumsqRed[ul.second + h - 1][ul.first - 1] + sumsqRed[ul.second - 1][ul.first - 1];
        } 
    }
    else if (channel == 'g') {
        if (ul.first == 0 && ul.second == 0) {
            return sumsqGreen[ul.second + h -1][ul.first + w -1];
        }
        else if (ul.first == 0) {
            return 0 - sumsqGreen[ul.second-1][ul.first + w - 1] + sumsqGreen[ul.second + h - 1][ul.first + w - 1];
        }
        else if (ul.second == 0) {
            return 0 - sumsqGreen[ul.second + h - 1][ul.first - 1] + sumsqGreen[ul.second + h - 1][ul.first + w - 1];
        }
        else {
            return sumsqGreen[ul.second + h - 1][ul.first + w - 1] - sumsqGreen[ul.second - 1][ul.first + w - 1] - sumsqGreen[ul.second + h - 1][ul.first - 1] + sumsqGreen[ul.second - 1][ul.first - 1];
        } 
    }
    else {
        if (ul.first == 0 && ul.second == 0) {
            return sumsqBlue[ul.second + h -1][ul.first + w -1];
        }
        else if (ul.first == 0) {
            return 0 - sumsqBlue[ul.second-1][ul.first + w - 1] + sumsqBlue[ul.second + h - 1][ul.first + w - 1];
        }
        else if (ul.second == 0) {
            return 0 - sumsqBlue[ul.second + h - 1][ul.first - 1] + sumsqBlue[ul.second + h - 1][ul.first + w - 1];
        }
        else {
            return sumsqBlue[ul.second + h - 1][ul.first + w - 1] - sumsqBlue[ul.second - 1][ul.first + w - 1] - sumsqBlue[ul.second + h - 1][ul.first - 1] + sumsqBlue[ul.second - 1][ul.first - 1];
        } 
    }
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int,int> ul, int w, int h){
/* Your code here!! */
    long varR = getSumSq('r', ul, w, h) - ((getSum('r', ul, w, h) * getSum('r', ul, w, h)) / (double)(w * h)); 
    long varG = getSumSq('g', ul, w, h) - ((getSum('g', ul, w, h) * getSum('g', ul, w, h)) / (double)(w * h)); 
    long varB = getSumSq('b', ul, w, h) - ((getSum('b', ul, w, h) * getSum('b', ul, w, h)) / (double)(w * h)); 
    return (double)(varR + varG + varB);


}
		
RGBAPixel stats::getAvg(pair<int,int> ul, int w, int h){
/* Your code here!! */

  long avgR = getSum('r', ul, w, h)/ (double)(w * h);
  long avgG = getSum('g', ul, w, h)/ (double)(w * h);
  long avgB = getSum('b', ul, w, h)/ (double)(w * h);

  RGBAPixel pixel = RGBAPixel((int)avgR, (int)avgG, (int)avgB);

  return pixel;

}
