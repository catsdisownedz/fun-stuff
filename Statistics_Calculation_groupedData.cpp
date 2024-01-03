//bismillah 
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unistd.h>
using namespace std;

// Function to calculate the mode
void calculateMode(vector<int>& frequency, vector<pair<double,double>>& classBoundaries) {
    double lower_boundary, mode, modal_one, modal_two;;
    int max = 0, mode_num = 0, width;
    vector <double> modes;

    for (size_t i = 0; i < frequency.size(); i++) {
        if (frequency[i] > max)  max = frequency[i];
    }
    for (size_t i = 0; i < frequency.size(); i++) {
        if(frequency[i]==max){
            mode_num++; 
            lower_boundary = classBoundaries[i].first;
            width = classBoundaries[i].second - classBoundaries[i].first;
            modal_one= frequency[i] - frequency[i-1];

            if(i< frequency.size()) modal_two= frequency[i] - frequency[i+1]; 

            mode = lower_boundary + ((modal_one * width) /(modal_one + modal_two));
            modes.push_back(mode);
            //cout<<lower_boundary<<endl;
        }
    }   
    if(mode_num > 1){
        for(size_t i; i< modes.size(); i++){
            cout<< "Mode number "<< i << " is "<< modes[i]<< "\n";
        }
    }
    else cout<< "Mode: "<< mode << "\n";
}

// Function to calculate the median
double calculateMedian(vector<int>& frequency, vector<pair<double, double>>& classBoundaries) {
    vector <double> cumulative_freq(frequency.size());
    double N = frequency[0];
    double lower_boundary, median;
    int freq, cum, width;
    cumulative_freq[0]= frequency[0];

    for (size_t i = 1; i < frequency.size(); i++) {
        cumulative_freq[i] = cumulative_freq[i-1] + frequency[i];
        N += frequency[i];
    }
     
    for(size_t i =0; i < frequency.size(); i++){
        if(cumulative_freq[i] > ((N + 1)/2) ){
            lower_boundary = classBoundaries[i].first;
            freq = frequency[i];
            cum = cumulative_freq[i-1];
            width = classBoundaries[i].second - classBoundaries[i].first;
            median = lower_boundary + width*((((N + 1)/2 )- cum)/freq);
            break;
        }
    } 
    return median;
}

// Function to calculate the mean
double calculateMean(vector<int>& frequency, vector<pair<double, double>>& classBoundaries) {
    int sum = 0;
    int cumulative_freq = 0;
    for (size_t i = 0; i < frequency.size(); i++) {
        double midpoint = (classBoundaries[i].first + classBoundaries[i].second)/2;
        sum += frequency[i] * midpoint;
        cumulative_freq += frequency[i];
    }
    return sum / cumulative_freq;
}
//Function to draw the Histogram
void drawHistogram(vector<int>& frequency,vector<pair<double, double>>& classBoundaries) {
   int maxFrequency;
   for (size_t i = 0; i < frequency.size(); i++) {
        if (frequency[i] > maxFrequency)  maxFrequency = frequency[i];
    }

    for (int i = maxFrequency; i > 0; --i) {
        cout.width(3); 
        cout << i << " | ";
        for (const auto& freq : frequency) {
            if (freq >= i) cout << "  *   "; 
             else cout << "      ";      
        }
        cout << "\n";
    }

    cout << "------";
    for (size_t i = 0; i < frequency.size(); ++i) {
        cout << "-------"; 
    }
    cout << "\n";
    cout << "      ";
    for (const auto& boundary : classBoundaries) {
        cout << boundary.first << "  "; 
    }
    cout << classBoundaries.back().second << "\n";
}
int main() {
    vector<pair<double, double>> classBoundaries;
    vector<int> frequency;
    int classNum, freq;
    double first, second;

    cout << "\033[36mHow many classes do you want to enter? \033[0m";
    cin >> classNum;

    cout << "\033[32mEnter the class intervals and the frequency of each :) \033[0m\n\n ";
    sleep(1.5);

    for(int i = 0; i < classNum; i++) {
        cout << "Enter interval number " << i + 1 << ": ";
        cin >> first >> second;
        first -= 0.5;
        second += 0.5;
        classBoundaries.emplace_back(first, second);
        cout << "and its frequency: ";
        cin >> freq;
        frequency.push_back(freq);
    }

    double mean = calculateMean(frequency, classBoundaries);
    cout << "\033[35mMean: " << mean << "\033[0m\n"; 
    calculateMode(frequency, classBoundaries); 
    double median = calculateMedian(frequency, classBoundaries);
    cout << "\033[95mMedian: " << median << "\033[0m\n"; 

    cout << "\n\n\033[31mHistogram:\033[0m\n";
    drawHistogram(frequency, classBoundaries);
}


