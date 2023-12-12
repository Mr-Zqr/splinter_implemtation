#include <fstream>
#include <random>
#include <Eigen/Dense>
#include <datatable.h>
#include <bspline.h>
#include <bsplinebuilder.h>

using namespace SPLINTER;

int main()
{
    // Create new DataTable to manage samples
    DataTable samples;

    // Sample the function
    DenseVector x(1);
    double y;
    std::vector<double> y_vec;

    // Random number generator
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0,30.0);
    std::normal_distribution<double> noise(0.0,1.0); // noise for y

    // Open output file
    std::ofstream outputFile;
    outputFile.open("output.csv");
    outputFile << "sample,output\n";

    // Generate 30 samples with increasing x(0)
    double step = 30.0 / 29; // We want 30 points in the range 0-30, so we divide the range by 29
    for(int i = 0; i < 30; i++)
    {
        x(0) = i * step;
        y = 2*x(0) + noise(generator); // y = x + noise

        // Store sample
        samples.addSample(x,y);

        // 将y存储在vector中。
        y_vec.push_back(y);
    }

    // Build B-spline that interpolates the samples
    BSpline bspline = BSpline::Builder(samples).degree(3).build();

    // Evaluate the B-spline at steps of 0.01 and write to file
    int counter = 0;
    for(double i = 0.0; i <= 30.0; i += 0.1)
    {

        x(0) = i;
        // Store sample

        outputFile << y_vec[static_cast<int>(floor(i))] << "," <<  bspline.eval(x) << "\n";


    }

    // Close output file
    outputFile.close();

    return 0;
}