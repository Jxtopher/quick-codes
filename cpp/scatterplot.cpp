//
// @Author: Jxtopher
// @License: Apache License 2.0
// @Date: 2018-06-25
// @Version: v1
// @Purpose: scatterPlot data in svg
//

#include <iostream>

using namespace std;

class ScatterPlot {
public:
  ScatterPlot() {
    origin_x = 100;
    origin_y = 1100;
  }

  virtual ~ScatterPlot() {
  }

  // Fonction principal
  void run(int *x, int *y, int size) {
    cout<<"<?xml version=\"1.0\" standalone=\"no\"?>";
    cout<<"<svg width=\"10cm\" height=\"10cm\" viewBox=\"0 0 1300 1300\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">";

    point(x, y, size);
    axis();
    label("x", "y");

    cout<<"</svg>";
  }

protected:
  // Dessiner les données
  void point(int *x, int *y, int size) {

    max_x = x[0], max_y = y[0], min_x = x[0], min_y = y[0];

    for (int i = 0 ; i < size ; i++) {
      if (max_x < x[i]) max_x = x[i];
      if (x[i] < min_x) min_x = x[i];
      if (max_y < y[i]) max_y = y[i];
      if (y[i] < min_y) min_y = y[i];
    }

    cout<<"<g fill=\"red\" stroke=\"blue\" stroke-width=\"1\">";
    for (int i = 0 ; i < size ; i++) {
      // Re-normalisation des points la nouvelle échelle [0; 1000]
      int xx = (1000 * (x[i] - min_x)) / (max_x - min_x);
      int yy = (1000 * (y[i] - min_y)) / (max_y - min_y);
      cout<<"<circle cx=\""<< origin_x + (origin_x + xx) <<"\" cy=\""<< (origin_y - yy) <<"\" r=\""<<8<<"\" />";
    }
    cout<<"</g>";
  }

  // Dessiner les axis
  void axis() {
    cout<<"<g stroke=\"black\" font-family=\"Verdana\" font-size=\"40\">";
    cout<<"<path id=\"axis\" d=\"M 180 80 L 180 1120 L 1220 1120\" fill=\"none\" />";
    for (unsigned int i = 0, j = 0 ; i < 1100 ; i += 100, j++ ) {
      // axis des abscisses
      cout<<"<path stroke-width=\"5\" id=\"axis\" d=\"M "<< 200 + i <<" 1120 L "<< 200 + i <<" 1130\" fill=\"none\" />";
      cout<<"<text text-anchor=\"middle\" x=\""<<200 + i<<"\" y=\"1170\" >"<< ((max_x - min_x) / 10) * j <<"</text>";
      // axis des coordonnés
      cout<<"<path stroke-width=\"5\" id=\"axis\" d=\"M 170 "<< 1100 - i <<" L 180 "<< 1100 - i <<" \" fill=\"none\" />";
      cout<<"<text text-anchor=\"end\" x=\"160\" y=\""<<1100 - i + 10<<"\" >"<< ((max_y - min_y) / 10) * j <<"</text>";
    }
    cout<<"</g>";
  }

  // Dessiner les légendes des axis
  void label(string xlabel, string ylabel) {
    cout<<"<g stroke=\"black\" font-family=\"Verdana\" font-size=\"55\">";
    cout<<"<text text-anchor=\"middle\" x=\"700\" y=\"1250\" >"<<xlabel<<"</text>";
    cout<<"<text text-anchor=\"middle\" x=\"50\" y=\"600\" style=\"writing-mode: tb;\">"<<ylabel<<"</text>";
    cout<<"</g>"<<endl;
  }


private:
  int origin_x, origin_y;
  int max_x, max_y, min_x, min_y;
};

int main() {
  ScatterPlot sp;

  //int x[] = {10, 100, 100, 10};
  int x[] = {0,1,321,92,95,116,293,348,316,401,187,189,168,139,142,371,443,444,393,208,446,223,260,155,162,432,340,95,436,222,154,358,309,125,386,174,414,57,294,275,445,309,307,450,427,46,395,89,113,99,337,486};

  //int y[] = {10, 10, 100, 100};
  int y[] = {0,1,107,160,279,156,155,484,433,493,290,198,487,447,470,42,208,322,349,227,136,160,382,390,110,240,83,76,192,172,483,13,464,135,73,109,52,339,27,181,496,19,422,230,180,384,324,398,200,416,316,252};

  sp.run(x, y, 50);

  return 0;
}
