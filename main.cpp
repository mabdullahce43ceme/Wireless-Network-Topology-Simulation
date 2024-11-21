#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Round_Button.H>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <iostream>

using namespace std;

int n = 500;
float sz = 10;
bool trueInput = false;

struct InputData {
    Fl_Input * nodesInput;
    Fl_Input * sizeInput;
    Fl_Round_Button * UDR;
    Fl_Round_Button * XTC;
    Fl_Box * Box;
    InputData (Fl_Input * nodesInput, Fl_Input * sizeInput, Fl_Round_Button * UDR, Fl_Round_Button * XTC, Fl_Box * box) : nodesInput(nodesInput), sizeInput(sizeInput), UDR(UDR), XTC(XTC), Box(box) {}
};


struct Node {
    float pos_x, pos_y;
    vector<Node*> neighbors;
    Node(float x, float y) : pos_x(x), pos_y(y) {}
};

class MyBox : public Fl_Box
{
    vector<pair<float, float>> nodes;
    vector<vector<float>> adjacencyMatrix;
    float Size;
public:
    MyBox(int x, int y, int w, int h, const vector <pair<float, float>> & nodes, const vector<vector<float>> &adjacencyMatrix, float Size) : Fl_Box(x, y, w, h), nodes(nodes), Size(Size), adjacencyMatrix(adjacencyMatrix) {}

    void draw() override
    {
        Fl_Box::draw();  // Call base class draw() first
        // Draw a rectangle within the box
        fl_rectf(x() + 10, y() + 10, w() - 2, h() - 2, FL_WHITE);
        for (auto iter = nodes.begin(); iter != nodes.end(); ++iter) {
            fl_rectf (
                static_cast<int>(x() + (*iter).first * w() / Size + 8), 
                static_cast<int>(y() + (*iter).second * h() / Size + 8), 
                4, 4, FL_BLUE
            ); 
            for (unsigned i = 0; i < nodes.size(); ++i)
            for (unsigned j = i + 1; j < nodes.size(); ++j)
            if (adjacencyMatrix[i][j] != -1) 
            fl_line(
                static_cast<int>(x() + nodes[i].first * w() / Size + 10), 
                static_cast<int>(y() + nodes[i].second * h() / Size + 10), 
                static_cast<int>(x() + nodes[j].first * w() / Size + 10), 
                static_cast<int>(y() + nodes[j].second * h() / Size + 10)
            );
        }
    }
};

class MyGraph {
    int N;
    float size;
    vector<pair<float, float>> vertices;
    vector<vector<float>> adjacencyMatrix;

    float distance (pair<float, float> &a, pair<float, float> &b) {
        return sqrt((a.first - b.first)*(a.first - b.first) + (a.second - b.second)*(a.second - b.second));
    }

    public:
    MyGraph (int n, float sz) : N(n), size(sz), adjacencyMatrix(n, vector<float>(n, -1)) {
        generateUDG ();
        // topologyControl ();
    }

    void generateUDG () {
        default_random_engine randomly;
        uniform_real_distribution<float> distribute(0, size);

        for (unsigned i = 0; i < N; ++i) 
        vertices.push_back(make_pair(distribute(randomly), distribute(randomly)));

        for (unsigned i = 0; i < N; ++i)
        for (unsigned j = i + 1; j < N; j++)
        if (distance(vertices[i], vertices[j]) <= 1) {
            adjacencyMatrix[i][j] = adjacencyMatrix[j][i] = distance(vertices[i], vertices[j]);
        }
    }
    pair<int, float> degrees () {
        int maxDegree = 0;
        float avgDegree = 0;
        for (unsigned i = 0; i < N; ++i) {
            int degree = 0;
            for (unsigned j = 0; j < N; ++j)
            if (adjacencyMatrix[i][j] != -1) ++degree;
            if (maxDegree < degree) maxDegree = degree;
            avgDegree += degree;
        }
        avgDegree /= N;
        return make_pair(maxDegree, avgDegree);
    }
    void topologyControl () {
        vector<vector<float>> _adjacencyMatrix = adjacencyMatrix;
        for (unsigned i = 0; i < N; ++i)
        for (unsigned j = i + 1; j < N; ++j)
        if (adjacencyMatrix[i][j] != -1) {
            for (unsigned k = 0; k < N; ++k) 
            if (adjacencyMatrix[i][k] != -1 && adjacencyMatrix[j][k] != -1) {
                if (adjacencyMatrix[j][k] < adjacencyMatrix[i][j] && adjacencyMatrix[i][k] < adjacencyMatrix[j][i]) {
                    _adjacencyMatrix[j][i] = _adjacencyMatrix[i][j] = -1;
                    break;
                }
            }
        }
        adjacencyMatrix = _adjacencyMatrix;
    }

    void draw () {

        MyBox* box = new MyBox(0, 0, 782, 782, vertices, adjacencyMatrix, size);
        box->draw();
    }
};

// class WirelessNetwork {};

void generateButtonCallback(Fl_Widget* widget, void* data) {
    InputData* inputData = static_cast<InputData*>(data);

    string x = inputData->nodesInput->value();
    string y = inputData->sizeInput->value();

    if (x == "" || y == "") {
        inputData->Box->copy_label("Input not provided");
        return;
    }

    if (!inputData->UDR->value() && !inputData->XTC->value()) {
        inputData->Box->copy_label("No topology control selected");
        return;
    }

    if (inputData->Box->is_label_copied()) inputData->Box->label("");

    cout << "Node: " << x << "\nSize: " << y << "\nGraph: " << ((inputData->UDR->value()) ? " UDR" : " XTC") << endl;
    int n = stoi(x);
    float sz = stof(y);
    bool trueInput = true;
    if (trueInput) {
        ostringstream oss;
        oss << y << "x" << y << ((inputData->UDR->value()) ? " UDR" : " XTC") << " Graph | " << x << " Nodes";
        std::string windowName = oss.str();
        // Create a new window to display the graph
        Fl_Window * graphWindow = new Fl_Window(1000, 800, windowName.c_str());
        Fl_Box box1(850, 350, 100, 40);
        Fl_Box box2(850, 400, 100, 40);
        MyGraph net (n, sz);
        if (inputData->XTC->value()) net.topologyControl();
        net.draw();
        string max_degree_message = "Max Degree: " + to_string(net.degrees().first);
        string avg_degree_message = "Avg Degree: " + to_string(net.degrees().second);
        box1.label(max_degree_message.c_str());
        box2.label(avg_degree_message.c_str());
        // Display the graph in the window

        graphWindow->end();
        graphWindow->show();
        while (graphWindow->shown()) Fl::wait();
    }
}

void round_button_callback(Fl_Widget* widget, void* data) {
  Fl_Round_Button* btn = (Fl_Round_Button*) widget;
  Fl_Round_Button* otherBtn = (Fl_Round_Button*)data;
  if (btn->value()) {
    otherBtn->value(0);
  }
}

int main () {
    Fl_Window window (400, 300, "Wireless Network Generator");

    Fl_Input nodesInput (125, 50, 150, 30, "Nodes:");
    Fl_Input sizeInput (125, 90, 150, 30, "Size:");
    Fl_Round_Button roundBtn_0 (50, 150, 100, 30, "UDR Graph");
    Fl_Round_Button roundBtn_1 (250, 150, 100, 30, "XTC Graph");
    Fl_Box errorBox (90, 190, 200, 30, "");
    errorBox.labelcolor(FL_RED);
    Fl_Return_Button generateButton (140, 225, 100, 30, "Generate");
    generateButton.color2(fl_rgb_color(32, 119, 215));
    generateButton.color(fl_rgb_color(45, 140, 220));
    generateButton.labelcolor(FL_WHITE);

    roundBtn_0.callback(round_button_callback, &roundBtn_1);
    roundBtn_1.callback(round_button_callback, &roundBtn_0);
    generateButton.callback(generateButtonCallback, new InputData (&nodesInput, &sizeInput, &roundBtn_0, &roundBtn_1, &errorBox));

    window.end();
    window.show();
    return Fl::run();
}

