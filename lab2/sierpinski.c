#include <stdio.h>
#include <stdlib.h>

int sort_get_index(float tab[], int top, float val){
  for (int i=0; i< top; i++) {
    if (val < tab[i]){ return i; 
    }
  }
  return top;
}

int sort_insert_at(float tab[], int insertion, int top, float val){
  while(top>insertion){
    tab[top]=tab[top-1];
    top--;
  }
  tab[top]=val;
  return 0;
}

int sort_insert(float tab[], int top, float val){
  int insertion = sort_get_index( tab,  top,  val);
  sort_insert_at(tab,  insertion,  top,  val);
  return 0;
}


int nb_columns(){
  return 32;
}

int nb_lines() {
  return 16;
}

void grid_init(char grid[], char pixel){
  int size= nb_columns() * nb_lines();
  for(int i=0; i<size; i++){
    grid[i] = pixel;
  }
}

void plot_point(char grid[], int x, int y, char pixel){
  if (x> nb_columns() || y > nb_lines()){
    printf("Out of bound");
    exit(EXIT_FAILURE);
  }
  grid[(nb_lines() - y - 1)* nb_columns() + x] = pixel;
}

void plot_vline(char grid[], int x, float fy0, float fy1, char pixel){
  int y0 = fy0+0.5;
  if (fy0 == y0 - 0.5){
    y0--;
  }
  int y1= fy1+0.5;
  if (fy1 == y1 - 0.5){
    y1--;
  }

  for(int i = y0; i<y1+1; i++){
    plot_point( grid,  x,  i,  pixel);
  }
}

struct point{
  float x;
  float y;
};

void plot_poly_sweep(char grid[], struct point p[], int top, int x, char pixel){
    float vline[ 4*top ];
    int vline_top=0;
    for(int i=0; i< top; i++){
      int j=( top - 1 +i )% top;
      if( (p[i].x <= x && p[j].x > x) || (p[i].x > x && p[j].x <= x)){
        float y0 = p[i].y + (x - p[i].x) * (p[j].y - p[i].y) / (p[j].x - p[i].x);
        sort_insert( vline,  vline_top, y0);
        vline_top++;
      }
      
    }
    int i=0; 
    while( i<vline_top){
      plot_vline( grid,  x,  vline[i],  vline[i+1],  pixel);
      i+=2;
    }
    
}

void plot_poly(char grid[], struct point points[], int top, char pixel){
  for(int x = 0; x < nb_columns(); x++){
      plot_poly_sweep( grid,  points,  top,  x,  pixel);
    }
}



int main(int argc, char* argv[]) {
  printf("%d %d\n", nb_columns(), nb_lines());
  int size= nb_columns() * nb_lines();
  char grid[size];
  grid_init( grid, ' ');
  struct point p[]= {{ 2, 13 }, { 10, 13 }, { 30, 7 }, { 10, 1 }, { 2, 1 }, { 18, 7 }};
  plot_poly(grid,  p, 6, '-');

  
  for(int i =0; i < size; i++){
    if (i%nb_columns() == 0){
      printf("\n");
    }
    printf("%c", grid[i]);
  }
  return 0;
}         