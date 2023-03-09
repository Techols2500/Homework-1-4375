// Tyler Echols
// 6 / 2 / 2022




#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

double Sum(vector<double> a)
{
    // the sum starts out as 0.0
    double sum = 0.0;

    // this loops over all the vector values then adds each value to sum
    for (int x = 0; x < a.size(); x++)
    {
        sum += a[x];
    }
    // return sum
    return sum;
}

// compute the mean of a vector
double Mean(vector<double> a) {
    // vector 
    double sum = Sum(a);

    // vector length
    double size = a.size();

    // mean is sum/length
    double mean = sum / size;

    // return mean
    return mean;
}

double Median(vector<double> a) {
    // vector size
    int size = a.size();

    // median variable
    double median;

    // arranges in ascending order
    sort(a.begin(), a.end());

    // if size of vector is even, average of middle two elements is going to be set as the medium 
    if (size % 2 == 0) {
        median = (a[size / 2 - 1] + a[size / 2]) / 2;
    }
    // if size of vector is odd, it's the middle element
    else {
        median = a[size / 2];
    }
    return median;
}

// function to compute the range of a vector
double Range(vector<double> a) {
    // maximum and minimum value are set to high and low values
    double max = -1e10;
    double min = 1e10;

    // initialize range
    double range;

    // loop over the vector
    for (int x = 0; x < a.size(); x++) {
        // current value is greater than max, reinitialize max as value
        if (a[x] > max) {
            max = a[x];
        }

        // reinitialize min as current value if value is less than the min, 
        if (a[x] < min) {
            min = a[x];
        }
    }
    //  maximum value - minimum value = range 
    range = max - min;
    return range;
}

// compute covariance between two vectors
double covar(vector<double> a, vector<double> b) {
    // mean of a and b
    double mean_x = Mean(a);
    double mean_y = Mean(b);

    // numerator
    double numerator = 0.0;
    for (int x = 0; x < a.size(); x++) {
        numerator += (a[x] - mean_x) * (b[x] - mean_y);
    }

    // calculate
    double denominator = a.size() - 1;

    // covariance as numerator divided by denominator
    double covariance = numerator / denominator;

    return covariance;

}

// compute correlation between the two vectors
double cor(vector<double> a, vector<double> b)
{

    double variance_x = covar(a, a);
    double sigma_x = sqrt(variance_x);


    double variance_y = covar(b, b);
    double sigma_y = sqrt(variance_y);


    double covariance_xy = covar(a, b);

    // calculate correlation
    double correlation = covariance_xy / (sigma_x * sigma_y);
    return correlation;
}

void print_stats(vector <double> input)
{
    vector <double> rm;
    vector <double> medv;
    string filename = "Boston.csv";

    cout << "rm sum is : " << Sum(rm) << "\n";
    cout << "medv sum is : " << Sum(medv) << "\n";


    cout << "rm mean : " << Mean(rm) << "\n";
    cout << "medv mean : " << Mean(medv) << "\n";


    cout << "rm median : " << Median(rm) << "\n";
    cout << "medv median : " << Median(medv) << "\n";

    cout << "rm range : " << Range(rm) << "\n";
    cout << "medv range : " << Range(medv) << "\n";

    cout << "Covariance of rm and medv : " << covar(rm, medv) << "\n";
    cout << "Correlation of rm and medv : " << cor(rm, medv) << "\n";
}


int main(int argc, char** argv)
{

    ifstream inFS;
    string line;
    string rm_in, medv_in;
    int numObservations = 0;
    const int MAX_LEN = 1000;
    vector <double> rm;
    vector <double> medv;
    // vector <double> rm(MAX_LEN);
     //vector <double>medv(MAX_LEN);


    cout << "Opening Boston.csv " << endl;

    inFS.open("Boston.csv");
    if (!inFS.is_open())
    {
        cout << "Could not open file" << endl;
        return 1;

    }
    cout << "Reding 1st line " << endl;
    getline(inFS, line);

    cout << " heading " << line << endl;

    int numObervations = 0;
    while (inFS.good())
    {
        getline(inFS, rm_in, ',');
        getline(inFS, medv_in, '\n');
        rm.at(numObervations) = stof(rm_in);
        medv.at(numObervations) = stof(medv_in);

        numObervations++;

    }

    rm.resize(numObervations);
    medv.resize(numObervations);

    cout << "new length" << rm.size() << endl;

    cout << "Clopsing file" << endl;
    inFS.close();

    cout << "Number of records is: " << numObervations << endl;

    cout << "\n Stats for rm" << endl;
    print_stats(rm);

    cout << "\n Stats for medv" << endl;
    print_stats(medv);

    cout << "\n Covariance = " << covar(rm, medv) << endl;

    cout << "\n Correlation = " << cor(rm, medv) << endl;

    cout << "\nProgram terminated ";

    return 0;
}
