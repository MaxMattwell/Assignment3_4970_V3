#include <vector>
#include "grnn.h"

class WebCrawler {
public:
    string root_url, current_url;
    int depth_limit, current_depth;
    stack<string> url_stack;
    stack<int> depth_stack;
    vector<string> expanded_urls;
    
    WebCrawler(string root_url_in, int depth_limit_in);
    string crawl();
    int find_children();
    void char_extractor();
};

