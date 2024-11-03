#include <array>
#include <vector>
#include <array>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <Windows.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#define NUM_ELEMENTS 10
#define QSORT 0
#define BUBBLESORT 1

struct PlotData {
    sf::RectangleShape* rec_ary;
    sf::RenderWindow* window;
    float rec_max_height;
    float rec_max_width;
    float rec_width;
    int max_value; 
    float waiting_time_s;
};



void bubbleSort(int ary[], int ary_len, PlotData plot_data);
void selectionSort(int ary[], int ary_len, PlotData plot_data);

//callback-functions of travers
int ini_random(int* ary, int arr_len, void* arg);
int ini_constant(int* ary, int arr_len, void* arg);
int dump_ary(int* ary, int arr_len, void* arg);
int cumsum(int* ary, int arr_len, void* arg);
int travers_arr(int (*travers_fcn)(int*, int, void*),int* ary, int arr_len, void* arg);
int get_max_value(int *ary, int ary_len);
void plot_array(int *ary, int ary_len, int active_index, PlotData plot_data);

int get_min_value(int* ary, int ary_len);
int compare_ints(const void* a, const void* b);
void ini_rectangle_arry(int* ary, int ary_len, int max_value, sf::RectangleShape* rec_ary, float rec_max_height, float rec_width, float x_pos, float y_pos);
void update_rectangle_ary(const int* ary, int len, int active_index, PlotData plot_data);
void wait(float seconds);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window"); 
    //sf::View view(sf::FloatRect(0, 0, 800, -600)); // Notice the negative height
    //window.setView(view);   
  
    int ary[NUM_ELEMENTS];
    
    travers_arr(ini_random,ary,NUM_ELEMENTS, NULL);
    
    
    sf::RectangleShape rec_ary[NUM_ELEMENTS];

    int const_val = 5;
    float x_pos = 10;
    float y_pos = 100;
    float rec_width = 1;
    float rec_height = 100;
    float rec_max_height = 400;
    float rec_max_width = 400; 
    int ary_len = NUM_ELEMENTS;
    travers_arr(ini_random,ary, ary_len, NULL);  
    int max_value = get_max_value(ary,ary_len);
    ini_rectangle_arry(ary,ary_len, max_value ,rec_ary,rec_max_height,rec_max_width,x_pos, y_pos);
    struct PlotData plot_data;
    plot_data.max_value = max_value;
    plot_data.rec_ary = rec_ary;
    plot_data.rec_max_height = rec_max_height;
    plot_data.rec_max_width = rec_max_width;
    plot_data.rec_width = rec_width;
    plot_data.window = &window;
    plot_data.waiting_time_s = 0.4;
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Verstrichene Zeit überprüfen
       
            //bubbleSort(ary, NUM_ELEMENTS, plot_data);
            selectionSort(ary, NUM_ELEMENTS, plot_data);
            
        

    }
    //       LARGE_INTEGER frequency, start, end;
    // double elapsedTime;

    // // Abfrage der Timer-Frequenz
    // QueryPerformanceFrequency(&frequency);

    // // Startzeit messen
    
    
    
    //     //travers_arr(dump_ary,ary,NUM_ELEMENTS, NULL);
    // //int sum = travers_arr(cumsum,ary,NUM_ELEMENTS, NULL);
    // //printf("Sum of Elements: %d", sum);
    // //travers_arr(ini_constant,ary,NUM_ELEMENTS, &const_val);
    // //travers_arr(dump_ary,ary,NUM_ELEMENTS, NULL);
    
    // if (QSORT) {
    //     QueryPerformanceCounter(&start);
    //     qsort(ary,NUM_ELEMENTS,sizeof(int),compare_ints);
    //     QueryPerformanceCounter(&end);
    //     elapsedTime = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    //     printf("Die Funktion qsort hat %f Sekunden gebraucht\n", elapsedTime);
    // }
    // if (BUBBLESORT){
    //     QueryPerformanceCounter(&start);
    //     bubbleSort(ary,NUM_ELEMENTS);
    //     QueryPerformanceCounter(&end);
    //     elapsedTime = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    //     printf("Die Funktion bubbleSort hat %f Sekunden gebraucht\n", elapsedTime);
    //     travers_arr(dump_ary,ary,NUM_ELEMENTS, NULL);
    // }
    
        
    // }

    
    
    
  
    // //travers_arr(dump_ary,ary,NUM_ELEMENTS, NULL);

    return 0;
}


void ini_rectangle_arry(int* ary, int ary_len, int max_value, sf::RectangleShape* rec_ary, float rec_max_height, float rec_max_width, float x_pos, float y_pos)
{
    float rec_height;
    float rec_width = rec_max_width/ary_len;
    for (int i = 0; i< ary_len; i++)
    {
        
        rec_height = ((float)rec_max_height/max_value) * ary[i];
        rec_ary[i].setSize({rec_width,rec_height});
        rec_ary[i].setPosition({x_pos, y_pos});
        x_pos += rec_width;
        rec_ary[i].setFillColor(sf::Color::White);

    }
}

void plot_array(int *ary, int ary_len, int active_index,PlotData plot_data)
{
   
    //update_rectangle_ary(plot_data.rec_ary, ary, ary_len, plot_data.rec_max_height, plot_data.max_value, plot_data.rec_width);
    update_rectangle_ary(ary, ary_len, active_index, plot_data);
    wait(plot_data.waiting_time_s);
    plot_data.window->clear();
    for (int i = 0; i < ary_len; i++)
    {
            plot_data.window->draw(plot_data.rec_ary[i]);
    }
    plot_data.window->display();

}


int get_max_value(int* ary, int ary_len)
{
     /* Returns the maximum value of ary without modifying 
        the input array*/
     int* tmp = (int*) malloc(ary_len * sizeof(int));
     memcpy(tmp,ary,sizeof(int)*ary_len);
     qsort(tmp,ary_len,sizeof(int),compare_ints);
     return tmp[ary_len -1];
}

int get_min_value(int* ary, int ary_len)
{
     /* Returns the minimum value of ary without modifying 
        the input array*/
     int* tmp = (int*) malloc(ary_len * sizeof(int));
     memcpy(tmp,ary,sizeof(int)*ary_len);
     qsort(tmp,ary_len,sizeof(int),compare_ints);
     return tmp[0];

}

void selectionSort(int ary[], int ary_len, PlotData plot_data) {
    for (int i = 0; i < ary_len-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < ary_len; j++)
            if (ary[j] < ary[min_idx])
                min_idx = j;
        // Vertauschen
        int temp = ary[min_idx];
        ary[min_idx] = ary[i];
        ary[i] = temp;
        plot_array(ary, ary_len,i,plot_data);
    }
}

void bubbleSort(int ary[], int ary_len, PlotData plot_data)
{
    //printf("Start array \t \t \t");
    //dump_ary(ary, ary_len, NULL);
    
    for(int i = 0; i < ary_len - 1; i++) {
        for (int j = 0; j < ary_len-i-1; j++)
        {
            if (ary[j] > ary[j+1]) {
                // Vertauschen
                int temp = ary[j];
                ary[j] = ary[j+1];
                ary[j+1] = temp;
            }
            //printf("Substep Iteration %d \t \t",i);
            //dump_ary(ary, ary_len, NULL);
        }
        plot_array(ary, ary_len,i,plot_data);
        //printf("Iteration %d result \t \t",i);
        //dump_ary(ary, ary_len, NULL);
        
    }

}

//callback-functions of travers
int ini_random(int* ary, int arr_len, void* arg)
{
    srand(time(NULL));
    for (int i = 0; i < arr_len; i++){
        ary[i] = rand();
    }
    return 0;
}

int ini_constant(int* ary, int arr_len, void* arg)
{
    int val = *(int*)arg;
    for (int i = 0; i < arr_len; i++){
        ary[i] = val;
    }
    return 0;
}

int dump_ary(int* ary, int arr_len, void* arg)
{
    for (int i = 0; i < arr_len; i++){
        //printf("Index: %d \t Value: %d \n",i,ary[i]);
        printf("%d \t",ary[i]);
        
    }
    printf("\n");
    return 0;
}

int cumsum(int* ary, int arr_len, void* arg)
{
     int sum = 0;
     for (int i = 0; i < arr_len; i++){
        sum += ary[i];
    }
    return sum;

}

int travers_arr(int (*travers_fcn)(int*, int, void*),int* ary, int arr_len, void* arg)
{
        return travers_fcn(ary, arr_len, arg);
}


void update_rectangle_ary(const int* ary, int len, int active_index, PlotData plot_data)
{
    float rec_width = plot_data.rec_max_width / len; 
    for (int i = 0; i< len;i++)
    {
        
        int rec_height = ((float)plot_data.rec_max_height/plot_data.max_value) * ary[i];
        plot_data.rec_ary[i].setSize({rec_width,rec_height});
        plot_data.rec_ary[i].setFillColor(sf::Color::White);
        if (i==active_index)
            plot_data.rec_ary[i].setFillColor(sf::Color::Red);
        
    }
}




int compare_ints(const void* a, const void* b)
{
    int first = *(const int*)a;
    int second = *(const int*)b;

    if (first < second)
        return -1;
    if (first > second)
        return 1;
    return 0;
}

// Wartefunktion
void wait(float seconds) {
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < seconds) {
        // Hier kannst du optional andere Aufgaben erledigen
    }
}