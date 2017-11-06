#include "grnn.h"
#include "webcrawler.h"

using namespace std;

int main(int argc, char* argv[]) {
    
    int i = 0;
    double classification, magnitude;
    int range1 = 0; // -1.0 to -0.5
    int range2 = 0; // -0.5 to 0.0
    int range3 = 0; // 0.0 to 0.5
    int range4 = 0; // 0.5 to 1.0
    int unknown_range = 0;
    
    // Feature weights for the grnn
    double weights[NUM_FEATURES];
    string weights_file = "weights.txt";
    init_weights(weights, weights_file);
    
    string root_url, current_url;
    int depth_limit = -1;
    
    /**
    filepath = argv[1];
    cout << "Command line argument 2: " << argv[2] << endl;
    depth_limit = (int) (argv[2][0] - '0');
    cout << "Depth limit: " << depth_limit << endl;
    */
    
    // Prompting input
    cout << "Please input a root URL: ";
    cin >> root_url;
    
    // Checking user input
    while (depth_limit < 0) {
        cout << "Please input a depth limit >= 0:  ";
        cin >> depth_limit;
    }
    
    // Initialize WebCrawler instance
    WebCrawler webcrawler(root_url, depth_limit);
    
    // Read in trng_set
    Data_Point trng_set[595];
    init_trng_set(trng_set);

    //stopping conditions
    while ((range1 < 10 || range2 < 10 || range3 < 10 || range4 < 10)) {
        //Provide webcrawler with a URL, which prints out
        //feature vectors to a file one by one

        current_url = webcrawler.crawl();
        
        //Create Data Point instance based on output file produced by webcrawler in unigrams directory
        Data_Point data;
        
        magnitude = init_trng_point(data, "output_" + to_string(i - 1) + "_unigrams.txt");
        cout << "Magnitude: " << magnitude << endl;
        
        classification = data.grnn_classify(trng_set, 0.1237, weights); //TODO: IS THIS FUNCTION CORRECT?
        cout << "Classification: " << classification << endl;
        cout << "Range 1: " << range1 << endl;
        cout << "Range 2: " << range2 << endl;
        cout << "Range 3: " << range3 << endl;
        cout << "Range 4: " << range4 << endl;
        
            // SAVES THE WRONG FILE
        if (classification >= -1 && classification <= -0.5) {
            if (range1 < 10) {
                data.save_url("range1_" + to_string(range1) + "_output.txt", current_url);
            }
            range1++;
        }
        else if (classification >= -0.5 && classification <= 0) {
            if (range2 < 10) {
                data.save_url("range2_" + to_string(range2) + "_output.txt", current_url);
            }
            range2++;
        }
        else if (classification >= 0 && classification <= 0.5) {
            if (range3 < 10) {
                data.save_url("range3_" + to_string(range3) + "_output.txt", current_url);
            }
            range3++;
        }
        else if (classification >= 0.5 && classification <= 1) {
            if (range4 < 10) {
                data.save_url("range4_" + to_string(range4) + "_output.txt", current_url);
            }
            range4++;
        }
        else {
            unknown_range++;
        }
        i++;
    }
    
    return 0;
}






