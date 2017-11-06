#include "grnn.h"
#include "webcrawler.h"

using namespace std;

WebCrawler::WebCrawler(string root_url_in, int depth_limit_in) {
    root_url = root_url_in;
    current_url = root_url;
    depth_limit = depth_limit_in;
    current_depth = 0;
    url_stack.push(root_url);
    depth_stack.push(current_depth);
}

string WebCrawler::crawl() {
    // Save current URL in temporary variable for return
    string return_url = current_url;
    // Print current URL and depth
    cout << "URL being expanded is " << current_url << endl;
    cout << "The depth of the current URL is " << current_depth << endl;
    
    // Find children of URL and store them into the stack. Also store their associated depths into a stack. Saves HTML of expanded URL in a .txt file
    find_children();
    cout << "It's not in find_children. Is it in next stack reference?" << endl;
    // Update current variables
    current_url = url_stack.top();
    current_depth = depth_stack.top();
    cout << "It's not there either." << endl;
    cout << "Is it in char_extractor?" << endl;
    // Extract normalized features from HTML soure and delete empty source files and their features
    char_extractor();
    cout << "It's not in char_extractor" << endl;
    
    // Return current URL
    return return_url;
}

int WebCrawler::find_children() {
    string hyperlink, child_url;
    int num_links = 0;
    
    // Build call to javaCall
    string javaCall = "java getWebPage " + current_url + " > html_source/output_" + to_string(expanded_urls.size()) + ".txt";

    // Extract HTML source by following URL via call to javaCall
    system(javaCall.c_str());
    
    // Add expanded URL to list and pop elements off the top of the stacks
    expanded_urls.push_back(current_url);
    url_stack.pop();
    depth_stack.pop();
    
    // Scan HTML source for hyperlinks
    ifstream html_source("html_source/output_" + to_string(expanded_urls.size()-1) + ".txt");
    while (!html_source.eof() && current_depth < depth_limit) {
        // Check if current line is a link
        getline(html_source, hyperlink);
        
        // Remove leading whitespace
        hyperlink.erase(hyperlink.begin(), find_if(hyperlink.begin(), hyperlink.end(), bind1st(not_equal_to<char>(), ' ')));
        if (strncmp("<a href", hyperlink.c_str(), 7) == 0) {
            
            // Esxtract URL from hyperlink line; use quotation marks as delimiters
            stringstream ss(hyperlink);
            ss.ignore(10, '"');
            getline(ss, child_url, '"');
            
            //IMPROVEMENT: prevents any URLS that do not begin with "http", that end with ".pdf", or that have already been expanded from being pushed onto the stack
            if (child_url.length() > 4 && strncmp(child_url.substr(child_url.length() - 3, child_url.length()).c_str(), "pdf", 3) != 0 && strncmp(child_url.substr(0, 4).c_str(), "http", 4) == 0 && find(expanded_urls.begin(), expanded_urls.end(), child_url) == expanded_urls.end()) {
                // Push URL and depth onto stack
                url_stack.push(child_url);
                cout << "URL pushed onto the stack: " << url_stack.top() << endl;
                depth_stack.push(current_depth + 1);
                cout << "At depth: " << depth_stack.top() << endl;
                
                // Iterate child count
                num_links++;
            }
        }
    }
    html_source.close();
    // Return number of children
    return num_links;
}


void WebCrawler::char_extractor() {
    string new_filepath;
    char c;
    double magnitude;
    int magnitude_squared = 0;
    double unigram_count[NUM_FEATURES];
    
    // build path to HTML source
    string filepath = "html_source/output_" + to_string(expanded_urls.size()-1) + ".txt";

    // Initialize count of each unigram to zero
    for (int i = 0; i < NUM_FEATURES; i++) {
        unigram_count[i] = 0;
    }
    
    // Count the frequency of each printable character in the HTML source
    ifstream in_text(filepath);
    while (in_text >> noskipws >> c) {
        if (isprint(c)) {
            int i = c - 32;
            unigram_count[i]++;
        }
    }
    in_text.close();
    
    // Find the magnitude of feature vector
    for (int i = 0; i < NUM_FEATURES; i++) {
        magnitude_squared += pow(unigram_count[i], 2);
    }
    cout << "Magnitude Squared: " << magnitude_squared << endl;
    // If feature vector is not zero vector, write to output file
    if (magnitude_squared > 0) {
        // Magnitude is square-root of sum of squares. Kept as int until after comparison
        magnitude = sqrt((double) magnitude_squared);
        
        // Create output stream to file containing normalized feature vector
        new_filepath = "unigrams/output_" + to_string(expanded_urls.size()-1) + "_unigrams.txt";
        ofstream out_text(new_filepath);
        
        // First write the index of the output file
        out_text << expanded_urls.size()-1;
        
        // Write normalized unigrams
        for (int i = 0; i < NUM_FEATURES; i++) {
            if (magnitude != 0) {
                out_text << " " << (unigram_count[i] / magnitude);
            }
            else {
                out_text << " " << unigram_count[i];
            }
        }
        out_text.close();
    }

    // Else delete associated source
    else {
        cout << "Deleting file" << endl;
        remove(("html_source/output_" + to_string(expanded_urls.size()-1) + ".txt").c_str());
    }
}


