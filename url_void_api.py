import urllib2
import subprocess

def find_between( s, first, last ):
    try:
        start = s.index( first ) + len( first )
        end = s.index( last, start )
        return s[start:end]
    except ValueError:
        return ""

def run():
    root_url = raw_input("Please input url: ")
    depth = raw_input("Please input depth level: ")
        #try:
    print subprocess.check_call(['./a.out', root_url, depth])
    #except subprocess.CalledProcessError, e:
    #print e.output
    id = 595 #id of URL
    
    #read in URLs and corresponding feature vectors of 40 training instances from a .txt. file, using amazon.com as an example for now
    
    """
    
    hostnames = []
    feat_vecs = []
    for i in range(0,10):
        with open("new_urls/range1_" + str(i) + "_output.txt", "r") as range1:
            line = range1.readline()
            hostnames.append(line.split()[0])
            feat_vecs.append([])
            for j in range(0,95):
                feat_vecs[4*i].append(line.split()[j+1])
        with open("new_urls/range2_" + str(i) + "_output.txt", "r") as range2:
            line = range2.readline()
            hostnames.append(line.split()[0])
            feat_vecs.append([])
            for j in range(0,95):
                feat_vecs[4*i+1].append(line.split()[j+1])
        with open("new_urls/range3_" + str(i) + "_output.txt", "r") as range3:
            line = range3.readline()
            hostnames.append(line.split()[0])
            feat_vecs.append([])
            for j in range(0,95):
                feat_vecs[4*i+2].append(line.split()[j+1])
        with open("new_urls/range4_" + str(i) + "_output.txt", "r") as range4:
            line = range4.readline()
            hostnames.append(line.split()[0])
            feat_vecs.append([])
            for j in range(0,95):
                feat_vecs[4*i+3].append(line.split()[j+1])
    
    for hostname in hostnames:
        some_url = "http://api.urlvoid.com/api1000/af774a8d258f8c97e0595f90f62cf5b75d5e5b32/host/" + hostname + "/"
        content = urllib2.urlopen(some_url).read()
        count = content.find("<count>")
        if (count): #URL not benign
            classification = find_between(content, "<count>", "</count>")
            #URLVoid provides a classification from 0 to 34 out of 34, with 0 out of 34 equivalent to -1, or a benign
            #classification, and 34 out of 34 equivalent to 1, or a malignant classification. If the classification is
            #0 out of 34, then count is false, and we skip to the else statement. The code below alters the URLVoid
            #classification to fit our purposes.
            if (classification == 17):
                classification = 0
            elif (classification > 17):
                classification = -1
            elif (classification < 17):
                classification = 1
    
        #append the following content to our_dataset.txt: id, classification, feature vector


        with open("our_dataset.txt", "a") as dataset:
            dataset.write(str(id) + " " + str(classification))
            for j in range(0,95):
                dataset.write(" " + str(feat_vecs[id-595][j]))
            dataset.write("\n")
    
        #else: #URL benign
        #append the id, classification = -1, feature vector to our_dataset.txt

        id += 1
"""

#run a.out again to determine new accuracy (hopefully better!)


























if __name__ == '__main__':
    run()
