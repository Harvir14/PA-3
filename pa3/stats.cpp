#include "stats.h"
#include "stats.h"

stats::stats(PNG & im){

/* Your code here!! */

for (unsigned int x = 0; x < im.width(); x++) {
    for (unsigned int y = 0; y < im.height(); y++) {
        int sumR = 0;
        int sumG = 0;
        int sumB = 0;
        int sumRsq = 0;
        int sumGsq = 0;
        int sumBsq = 0;    
        for (unsigned int i = 0; i <= x; i++) {
            for (unsigned int j = 0; j <= y; j++) {
                sumR += im.getPixel(i,j)->r;
                sumG += im.getPixel(i,j)->g;
                sumB += im.getPixel(i,j)->b;
                sumRsq += im.getPixel(i,j)->r * im.getPixel(i,j)->r;
                sumGsq += im.getPixel(i,j)->g * im.getPixel(i,j)->g;
                sumBsq += im.getPixel(i,j)->b * im.getPixel(i,j)->b;
            }
        }
        sumRed[x][y] = sumR;
        sumGreen[x][y] = sumG;
        sumBlue[x][y] = sumB;
        sumsqRed[x][y] = sumRsq;
        sumsqGreen[x][y] = sumGsq;
        sumsqBlue[x][y] = sumBsq;
    }
}

}


long stats::getSum(char channel, pair<int,int> ul, int w, int h){
/* Your code here!! */
    if (channel == 'r') {
        return sumRed[ul.first + w - 1][ul.second + h - 1] - sumRed[ul.first + w - 1][ul.second] - sumRed[ul.first][ul.second + h - 1] + sumRed[ul.first][ul.second]; 
    }
    else if (channel == 'g') {
        return sumGreen[ul.first + w - 1][ul.second + h - 1] - sumGreen[ul.first + w - 1][ul.second] - sumGreen[ul.first][ul.second + h - 1] + sumGreen[ul.first][ul.second]; 
    }
    else {
        return sumBlue[ul.first + w - 1][ul.second + h - 1] - sumBlue[ul.first + w - 1][ul.second] - sumBlue[ul.first][ul.second + h - 1] + sumBlue[ul.first][ul.second];
    }

}

long stats::getSumSq(char channel, pair<int,int> ul, int w, int h){
/* Your code here!! */
    if (channel == 'r') {
        return sumsqRed[ul.first + w - 1][ul.second + h - 1] - sumsqRed[ul.first + w - 1][ul.second] - sumsqRed[ul.first][ul.second + h - 1] + sumsqRed[ul.first][ul.second]; 
    }
    else if (channel == 'g') {
        return sumsqGreen[ul.first + w - 1][ul.second + h - 1] - sumsqGreen[ul.first + w - 1][ul.second] - sumsqGreen[ul.first][ul.second + h - 1] + sumsqGreen[ul.first][ul.second]; 
    }
    else {
        return sumsqBlue[ul.first + w - 1][ul.second + h - 1] - sumsqBlue[ul.first + w - 1][ul.second] - sumsqBlue[ul.first][ul.second + h - 1] + sumsqBlue[ul.first][ul.second];
    }

}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int,int> ul, int w, int h){
/* Your code here!! */
    long varR = getSumSq('r', ul, w, h) - (getSumSq('r', ul, w, h) / (w * h)); 
    long varG = getSumSq('g', ul, w, h) - (getSumSq('g', ul, w, h) / (w * h)); 
    long varB = getSumSq('b', ul, w, h) - (getSumSq('b', ul, w, h) / (w * h)); 
    return (double)(varR + varG + varB);


}
		
RGBAPixel stats::getAvg(pair<int,int> ul, int w, int h){
/* Your code here!! */

  long avgR = getSum('r', ul, w, h)/ (w * h);
  long avgG = getSum('g', ul, w, h)/ (w * h);
  long avgB = getSum('b', ul, w, h)/ (w * h);

  return RGBAPixel(avgR, avgG, avgB);

}
